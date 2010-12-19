#include "ComponentDomParser.h"

namespace kex
{
  ComponentDomParser::ComponentDomParser(const QString& fileName) :
    m_filename(fileName),
  m_globalList(ComponentDomParser::ComponentList())
  {
    setupParseMap();
  }

  const ComponentDomParser::ComponentList& ComponentDomParser::components() const
  {
    return m_globalList;
  }

  ComponentDomParser& ComponentDomParser::operator<<(QFile& file)
  {
    return readFile(file);
  }

  ComponentDomParser& ComponentDomParser::operator<<(const QString& fileName)
  {
    return readFile(fileName);
  }

  ComponentDomParser& ComponentDomParser::readFile(const QString& fileName)
  {
    m_filename = fileName;
    return readFile();
  }

  ComponentDomParser& ComponentDomParser::readFile()
  {
    QFile file(m_filename);
    return readFile(file);
  }

  ComponentDomParser& ComponentDomParser::readFile(QFile& file)
  {
    Logger *logger = &Logger::instance();

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
      QString msg("ComponentDomParser::readFile");
      QString info(QObject::tr("Error: Cannot read file : %1"));
      logger->displayMessage(msg, info.arg(file.errorString()),
                             QMessageBox::Ok, Logger::WarningLogLevel);
      return *this;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    QDomDocument doc;
    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
    {
      QString msg("ComponentDomParser::readFile");
      QString info(QObject::tr("Error: Parse error at line %1,%2: %3"));

      logger->displayMessage(msg, info.arg(errorLine)
                                  .arg(errorColumn).arg(errorStr),
                             QMessageBox::Ok, Logger::WarningLogLevel);

      file.close();
      return *this;
    }


    QDomElement root = doc.documentElement();
    if (!isValidElement(root))
    {
      QString msg("ComponentDomParser::readFile");
      QString info("Error: Not a component file: %1");
      logger->displayMessage(msg, info.arg(m_filename), QMessageBox::Ok,
                             Logger::WarningLogLevel);

      file.close();
      return *this;
    }

    Component::Pointer component = createComponent(root);

    parseElement(root, component);

    if (component)
    {
      Component::SharedPointer ptr(component);
      m_globalList.append(ptr);
    }

    file.close();

    resolveName(component);
    return *this;
  }

  void ComponentDomParser::setupParseMap()
  {
    // setup parsing function map
    parseFunc parse;
    parse = &ComponentDomParser::parseActionElement;
    m_parseMap[ActionTagName] = parse;

    parse = &ComponentDomParser::parseEventElement;
    m_parseMap[EventTagName] = parse;

    parse = &ComponentDomParser::parseTrialElement;
    m_parseMap[TrialTagName] = parse;

    parse = &ComponentDomParser::parseExperimentElement;
    m_parseMap[ExperimentTagName] = parse;

    parse = &ComponentDomParser::parseHeaderElement;
    m_parseMap[HeaderTagName] = parse;

    parse = &ComponentDomParser::parseCategoriesElement;
    m_parseMap[CategoriesTagName] = parse;

    parse = &ComponentDomParser::createChildComponent;
    m_parseMap[CreateChildParseAction] = parse;
  }

  void ComponentDomParser::resolveName(Component::Pointer component) const
  {
    QString name = component->name();
    if (name.isEmpty())
    {
      name = Utilities::componentNameFromFilePath(m_filename);
      component->setName(name);
    }
  }

  Component::SharedPointer
  ComponentDomParser::templateComponent(const QDomElement &root) const
  {
    Q_ASSERT(isValidElement(root));

    Component::SharedPointer c_template(0);
    QString name("");
    QDomNode child = root.firstChild();

    while (!child.isNull())
    {
      if (!name.isEmpty()) break;

      if (child.toElement().tagName() == HeaderTagName)
      {
        QDomNode c = child.firstChild();

        while (!c.isNull())
        {
          if (c.toElement().tagName() == NameTagName)
          {
            name = c.toElement().text();
            break;
          }
          c = c.nextSibling();
        }
      }

      child = child.nextSibling();
    }

    if(!name.isEmpty())
    {
      QListIterator<Component::SharedPointer> it(m_globalList);
      Component::SharedPointer temp(0);
      while(it.hasNext())
      {
        temp = it.next();
        if(temp->name() == name)
        {
          c_template = temp;
          break;
        }
      }
    }

    return c_template;
  }

  Component::Pointer
  ComponentDomParser::createComponent(const QDomElement& root) const
  {
    Q_ASSERT(isValidElement(root));

    Component::SharedPointer c_temp = templateComponent(root);

    // found template component
    if(c_temp)
      return c_temp->clone();

    // else create new component
    QString rootName = root.tagName();
    Component::ComponentTypes c_type;

    // assign type of component to create
    if (rootName == ActionTagName)
    {
      QString t = root.attribute("type").simplified();

      if (t == "rest")
        c_type = Component::RestActionType;

      else if (t == "text")
        c_type = Component::TextActionType;

      else if (t == "image")
        c_type = Component::ImageActionType;

      else if (t == "audio")
        c_type = Component::AudioActionType;

      else if (t == "video")
        c_type = Component::VideoActionType;

    } else if (rootName == "event")
    {
      c_type = Component::EventType;
    } else if (rootName == "trial")
    {
      c_type = Component::TrialType;

    } else if (rootName == "experiment")
    {
      c_type = Component::ExperimentType;
    }

    Component::Pointer comp = ComponentFactory::instance().create(c_type);
    Q_CHECK_PTR(comp);

    return comp;
  }

  bool ComponentDomParser::isValidElement(const QDomElement &element) const
  {
    bool isValid(false);

    if (element.tagName() == ActionTagName || element.tagName() == "event" ||
        element.tagName() == "trial"  || element.tagName() == "experiment" ||
        element.tagName() == "header")
    {
      isValid = true;
    }

    return isValid;
  }

  void
  ComponentDomParser::parseElement(const QDomElement &element,
                                   Component::Pointer component) const
  {
    // should only receive valid elements.
    Q_ASSERT(isValidElement(element));
    Q_CHECK_PTR(component);
    // this method should never be passed a header tag
    Q_ASSERT(element.tagName() != "header");

    // map created in ComponentDomParser::setupParseMap()
    m_parseMap[element.tagName()](this, element, component);
  }

  void
  ComponentDomParser::parseHeaderElement(const QDomElement &element,
                                         Component::Pointer component) const
  {
    Q_ASSERT(element.tagName() == HeaderTagName);
    Q_CHECK_PTR(component);

    QString tag;

    QDomNode child = element.firstChild();

    while (!child.isNull())
    {
      tag = child.toElement().tagName();

      if (tag != CategoriesTagName)
      {
        QVariant value(child.toElement().text());
        setComponentProperty(tag, value, component);

      } else {

        m_parseMap[tag](this, child.toElement(),component);
      }

      child = child.nextSibling();
    }
  }

  void
  ComponentDomParser::parseActionElement(const QDomElement &element,
                                         Component::Pointer component) const
  {
    Q_ASSERT(element.tagName() == ActionTagName);
    Q_CHECK_PTR(component);

    QDomNode child  = element.firstChild();

    while (!child.isNull())
    {
      QString tag = child.toElement().tagName();
      if(tag == HeaderTagName)
      {
        m_parseMap[tag](this, child.toElement(), component);
      } else {
        QVariant value(child.toElement().text());
        setComponentProperty(tag, value, component);
      }

      child = child.nextSibling();
    }
  }

  void ComponentDomParser::setComponentProperty(const QString  &property,
                                                const QVariant &value,
                                       Component::Pointer component) const
  {
    Q_CHECK_PTR(component);
    QVariant old_value(component->property(property.toAscii()));
    bool success = false;

    if(old_value != value)
      component->setProperty("hello", QVariant("goodbye"));
//      success = component->setProperty(qPrintable(property), value);
    else
      // we don't bother setting equal values
      success = true;

    if(!success)
    {
      Logger *logger = &Logger::instance();
      QString msg("ComponentDomParser::setComponentProperty");
      QString info(QObject::tr("Unhandled element: %1, for component: %2"));
      QString c_type;
      c_type = Component::componentTypeToString(component->componentType());

      logger->displayMessage(msg, info.arg(property, c_type));
    }
  }

  void
  ComponentDomParser::parseEventElement(const QDomElement &element,
                                        Component::Pointer component) const
  {
    Q_CHECK_PTR(component);
    QDomNode child = element.firstChild();
    QString tag;

    while (!child.isNull())
    {
      tag = child.toElement().tagName();

      if (tag == ActionTagName)
      {
        tag = CreateChildParseAction;
      }

      m_parseMap[tag](this, child.toElement(), component);

      child = child.nextSibling();
    }

  }

  void
  ComponentDomParser::parseTrialElement(const QDomElement &element,
                                        Component::Pointer component) const
  {
    Q_CHECK_PTR(component);
    Q_ASSERT(component->componentType() == Component::EventType ||
             component->componentType() == Component::ActionType);

    QDomNode child = element.firstChild();
    QString key;
    QString tagName;

    while (!child.isNull())
    {
      tagName = child.toElement().tagName();

      if (tagName == ActionTagName || tagName == EventTagName)
      {
        key = CreateChildParseAction;
      } else if ( tagName == HeaderTagName)
      {
        key = tagName;

      } else {
        Logger *logger = &Logger::instance();
        QString msg("ComponentDomParser::parseTrialElement");
        QString info(QObject::tr("Unrecognized element found in %1: %2"));
        logger->displayMessage(msg, info.arg(element.tagName())
                                        .arg(child.toElement().tagName()),
                               QMessageBox::Ok, Logger::WarningLogLevel);
      }

      m_parseMap[key](this, child.toElement(), component);

      child = child.nextSibling();
    }
  }

  void
  ComponentDomParser::parseExperimentElement(const QDomElement &element,
                                             Component::Pointer component) const
  {
    Q_CHECK_PTR(component);
    Q_ASSERT(component->componentType() == Component::TrialType);
    QDomNode child = element.firstChild();

    while (!child.isNull())
    {
      if (child.toElement().tagName() == TrialTagName ||
          child.toElement().tagName() == ActionTagName)
      {
        m_parseMap[CreateChildParseAction](this, child.toElement(), component);

      } else if (child.toElement().tagName() == HeaderTagName)
      {
        m_parseMap[HeaderTagName](this, child.toElement(), component);

      }
      child = child.nextSibling();
    }
  }

  void
  ComponentDomParser::parseCategoriesElement(const QDomElement &element,
                              Component::Pointer component) const
  {
    Q_CHECK_PTR(component);

    QDomNode item = element.firstChild();
    QString cat("");

    while (!item.isNull())
    {
      if (item.toElement().tagName() == ItemTagName)
      {
        cat = item.toElement().text();
        if (!cat.isEmpty())
        {
          component->addCategory(cat);
        }
      }
      item = item.nextSibling();
    }

  }

  void
  ComponentDomParser::createChildComponent(const QDomElement &element,
                                           Component::Pointer component) const
  {
    Q_CHECK_PTR(component);
    Q_ASSERT(isValidElement(element));
    Q_ASSERT(component->componentType() & ~Component::ActionType);

    Component::Pointer child = createComponent(element);

    Q_CHECK_PTR(child);
    // Only non Action components  can have children, we assert this here

    parseElement(element, child);
    // Since this is a child element, it could be a template. Templates must
    // Declare a specific name of a predefined item for lookup purposes.
    // This item could be a defined previously within the parent component
    // OR it could be defined at the top most level of components in an
    // xml file. Since templates work on an overloading principle, we start by
    // looking at the top most level and then work to the inner scope.
    QString name = component->name();

    if (child)
    {
      //component->appendComponent(child);
    } else
    {
      Logger *logger = &Logger::instance();
      // Just in case an unaccounted for release problem occurs
      QString msg("ComponentDomParser::createChild");
      QString info("Component '%1' can not have any child nodes!");

      logger->displayMessage(msg, info.arg(component->name()),
                             QMessageBox::Ok, Logger::WarningLogLevel);
    }
  }
}
