#include "ComponentDomParser.h"

namespace kex
{
  const QString kex::ComponentDomParser::ActionTagName          = "action";
  const QString kex::ComponentDomParser::EventTagName           = "event";
  const QString kex::ComponentDomParser::TrialTagName           = "trial";
  const QString kex::ComponentDomParser::ExperimentTagName      = "experiment";
  const QString kex::ComponentDomParser::HeaderTagName          = "header";
  const QString kex::ComponentDomParser::CategoriesTagName      = "categories";
  const QString kex::ComponentDomParser::ItemTagName            = "item";
  const QString kex::ComponentDomParser::NameTagName            = "name";
  const QString kex::ComponentDomParser::DurationTagName        = "duration";
  const QString kex::ComponentDomParser::CreateChildParseAction = "create_child";
  const QString kex::ComponentDomParser::AudioTagName           = "audio";
  const QString kex::ComponentDomParser::ImageTagName           = "image";
  const QString kex::ComponentDomParser::VideoTagName           = "video";
  const QString kex::ComponentDomParser::SourcePropertyName     = "source";
  const QString kex::ComponentDomParser::RestTagName            = "rest";
  const QString kex::ComponentDomParser::TextTagName            = "text";

  ComponentDomParser::ComponentDomParser(const QString& fileName) :
    m_filename(fileName),
  m_globalList(Component::globalList())
  {
    setupParseMap();
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
    QDomElement child = root.firstChildElement();

    while (!child.isNull())
    {
      if (!name.isEmpty()) break;

      if (child.tagName() == HeaderTagName)
      {
        QDomElement c = child.firstChildElement();

        while (!c.isNull())
        {
          if (c.tagName() == NameTagName)
          {
            name = cleanText(c.text());
            break;
          }
          c = c.nextSiblingElement();
        }
      }

      child = child.nextSiblingElement();
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

      if (t == RestTagName)
        c_type = Component::RestActionType;

      else if (t == TextTagName)
        c_type = Component::TextActionType;

      else if (t == ImageTagName)
        c_type = Component::ImageActionType;

      else if (t == AudioTagName || t == VideoTagName)
        c_type = Component::MediaActionType;

    } else if (rootName == EventTagName)
    {
      c_type = Component::EventType;
    } else if (rootName == TrialTagName)
    {
      c_type = Component::TrialType;

    } else if (rootName == ExperimentTagName)
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

    if (element.tagName() == ActionTagName     ||
        element.tagName() == EventTagName      ||
        element.tagName() == TrialTagName      ||
        element.tagName() == ExperimentTagName ||
        element.tagName() == HeaderTagName)
    {
      isValid = true;
    }

    return isValid;
  }

  void
  ComponentDomParser::parseElement(const QDomElement &element,
                                   Component::Pointer component) const
  {
    QString tag = element.tagName();
    // should only receive valid elements.
    Q_ASSERT(isValidElement(element));
    Q_CHECK_PTR(component);
    // this method should never be passed a header tag
    Q_ASSERT(element.tagName() != HeaderTagName);
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

    QDomElement child = element.firstChildElement();

    while (!child.isNull())
    {
      tag = child.tagName();

      if (tag != CategoriesTagName)
      {
        QVariant value(cleanText(child.text()));
        setComponentProperty(tag, value, component);

      } else {

        m_parseMap[tag](this, child, component);
      }

      child = child.nextSiblingElement();
    }
  }

  void
  ComponentDomParser::parseActionElement(const QDomElement &element,
                                         Component::Pointer component) const
  {
    Q_CHECK_PTR(component);
    Q_ASSERT(element.tagName() == ActionTagName);
    Q_ASSERT(component->componentType() & Component::ActionType);

    QDomElement child  = element.firstChildElement();

    while (!child.isNull())
    {
      QString tag = child.tagName();

      if(tag == HeaderTagName)
      {
        m_parseMap[tag](this, child, component);

      } else if(tag == AudioTagName || tag == VideoTagName)
      {
        QVariant value(cleanText(child.text().trimmed()));
        setComponentProperty(SourcePropertyName, value, component);

      } else {
        QVariant value(cleanText(child.text().trimmed()));
        setComponentProperty(tag, value, component);
      }

      child = child.nextSiblingElement();
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
      success = component->setProperty(qPrintable(property), value);
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
    Q_ASSERT(component->componentType() & Component::EventType);
    QDomElement child = element.firstChildElement();
    QString tag;

    while (!child.isNull())
    {
      tag = child.tagName();

      if (tag == ActionTagName)
      {
        tag = CreateChildParseAction;
      }
      m_parseMap[tag](this, child, component);

      child = child.nextSiblingElement();
    }

  }

  void
  ComponentDomParser::parseTrialElement(const QDomElement &element,
                                        Component::Pointer component) const
  {
    Q_CHECK_PTR(component);
    Q_ASSERT(component->componentType() & Component::TrialType);

    QDomElement child = element.firstChildElement();
    QString key;
    QString tagName;

    while (!child.isNull())
    {
      tagName = child.tagName();

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

      m_parseMap[key](this, child, component);

      child = child.nextSiblingElement();
    }
  }

  void
  ComponentDomParser::parseExperimentElement(const QDomElement &element,
                                             Component::Pointer component) const
  {
    Q_CHECK_PTR(component);
    Q_ASSERT(component->componentType() & Component::ExperimentType);
    QDomElement child = element.firstChildElement();

    while (!child.isNull())
    {
      if (child.tagName() == TrialTagName ||
          child.tagName() == ActionTagName)
      {
        m_parseMap[CreateChildParseAction](this, child, component);

      } else if (child.tagName() == HeaderTagName)
      {
        m_parseMap[HeaderTagName](this, child, component);

      }
      child = child.nextSiblingElement();
    }
  }

  void
  ComponentDomParser::parseCategoriesElement(const QDomElement &element,
                              Component::Pointer component) const
  {
    Q_CHECK_PTR(component);

    QDomElement item = element.firstChildElement();
    QString cat("");

    while (!item.isNull())
    {
      if (item.tagName() == ItemTagName)
      {
        cat = cleanText(item.text());
        if (!cat.isEmpty())
        {
          component->addCategory(cat);
        }
      }
      item = item.nextSiblingElement();
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
    parseElement(element, child);

    if (child)
    {
      ComponentCollection::Pointer cp;
      cp = qobject_cast<ComponentCollection::Pointer>(component);
      Q_CHECK_PTR(cp);
      cp->appendComponent(child);
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

  QString ComponentDomParser::cleanText(const QString& text) const
  {
    QString new_text;
    QStringList lines = text.split("\n", QString::SkipEmptyParts);

    if(lines.size() < 2)
    {
      new_text = text.trimmed();

    } else {
      for(int i = 0;i < lines.size();++i)
      {
        new_text.append(lines[i].trimmed());
        new_text.append("\n");
      }
    }

    return new_text;
  }
}
