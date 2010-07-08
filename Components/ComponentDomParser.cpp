#include "ComponentDomParser.h"

namespace kex
{

  ComponentDomParser::ComponentDomParser() :
  m_filename(),
  m_globalList(ComponentList())
  {
    setupParseMap();
  }
  
  ComponentList ComponentDomParser::components() const
  {
    return m_globalList;
  }

  ComponentDomParser::ComponentDomParser(const QString& fileName) :
    m_filename(fileName),
  m_globalList(ComponentList())
  {
    setupParseMap();
  }

  ComponentDomParser& ComponentDomParser::readFile(const QString& fileName)
  {
    m_filename = fileName;
    return readFile();
  }
  
  void ComponentDomParser::setupParseMap()
  {
    // setup parsing function map
    parseFunc parse;
    parse = &ComponentDomParser::parseActionElement;
    m_parseMap["action"] = parse;
    
    parse = &ComponentDomParser::parseEventElement;
    m_parseMap["event"] = parse;
    
    parse = &ComponentDomParser::parseTrialElement;
    m_parseMap["trial"] = parse;
    
    parse = &ComponentDomParser::parseExperimentElement;
    m_parseMap["experiment"] = parse;
    
    parse = &ComponentDomParser::parseHeaderElement;
    m_parseMap["header"] = parse;
    
    parse = &ComponentDomParser::parseCategoriesElement;
    m_parseMap["categories"] = parse;
    
    parse = &ComponentDomParser::parseDurationElement;
    m_parseMap["duration"] = parse;
    
    parse = &ComponentDomParser::createChildComponent;
    m_parseMap["create_child"] = parse;
    
    // setup OutputComponent attribute map
    setComponentValue setValue;
    setValue = &OutputComponent::setName;
    m_setValueMap["name"] = setValue;
    
    setValue = &OutputComponent::setLabel;
    m_setValueMap["label"] = setValue;
    
    setValue = &OutputComponent::setDescription;
    m_setValueMap["description"] = setValue;
    
    setValue = &OutputComponent::addCategory;
    m_setValueMap["categories"] = setValue;
  }
  
  ComponentDomParser& ComponentDomParser::readFile()
  {
    QFile file(m_filename);

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

    ComponentList::Node::Pointer node = createComponentNode(root);

    m_globalList.push_back(node);
    parseElement(root, node);

    file.close();

    resolveName(node);
    return *this;
  }

  void ComponentDomParser::resolveName(ComponentList::Node::Pointer node) const
  {
    QString name = node->component()->name();
    if (name.isEmpty())
    {
      name = Utilities::componentNameFromFilePath(m_filename);
      node->component()->setName(name);
    }
  }

  ComponentList::Node::Pointer
  ComponentDomParser::createComponentNode(const QDomElement& root) const
  {
    Q_ASSERT(isValidElement(root));

    QString rootName = root.tagName();
    OutputComponent::ComponentTypes c_type;

    // assign type of component to create
    if (rootName == "action")
    {
      QString t = root.attribute("type").simplified();

      if (t == "rest")
      {
        c_type = OutputComponent::RestActionType;
      } else if (t == "text")
      {
        c_type = OutputComponent::TextActionType;
      } else if (t == "image")
      {
        c_type = OutputComponent::ImageActionType;
      } else if (t == "audio")
      {
        c_type = OutputComponent::AudioActionType;
      } else if (t == "video")
      {
        c_type = OutputComponent::VideoActionType;
      }
      } else if (rootName == "event")
      {
        c_type = OutputComponent::EventType;

      } else if (rootName == "trial")
      {
        c_type = OutputComponent::TrialType;

      } else if (rootName == "experiment")
      {
        c_type = OutputComponent::ExperimentType;
      }

    OutputComponent::Pointer comp = ComponentFactory::instance().create(c_type);
    Q_CHECK_PTR(comp);

    ComponentList::Node::Pointer node = new ComponentList::Node(comp);
    Q_CHECK_PTR(node);

    return node;
  }

  bool ComponentDomParser::isValidElement(const QDomElement &element) const
  {
    bool isValid(false);

    if (element.tagName() == "action" || element.tagName() == "event" ||
        element.tagName() == "trial"  || element.tagName() == "experiment" ||
        element.tagName() == "header")
    {
      isValid = true;
    }

    return isValid;
  }

  void 
  ComponentDomParser::parseElement(const QDomElement &element,
                                   ComponentList::Node::Pointer node) const
  {
    // should only receive valid elements.
    Q_ASSERT(isValidElement(element));
    Q_CHECK_PTR(node);
    // this method should never be passed a header tag
    Q_ASSERT(element.tagName() != "header");

    setMainCategory(element, node);
    
    QString c_type = element.tagName();
    // map created in ComponentDomParser::setupParseMap()
    m_parseMap[c_type](this, element, node);
  }

  void
  ComponentDomParser::parseHeaderElement(const QDomElement &element,
                                         ComponentList::Node::Pointer node) const
  {
    Q_ASSERT(element.tagName() == "header");
    Q_CHECK_PTR(node);

    QString value_type;
    QString value;
    OutputComponent::Pointer comp;
    
    QDomNode child = element.firstChild();
    comp = node->component().data();
    
    while (!child.isNull())
    {
      value_type = child.toElement().tagName();
      
      if (value_type != "categories")
      {
        value = child.toElement().text();
        m_setValueMap[value_type](comp, value);
      } else {
        m_parseMap[value_type](this, child.toElement(),node);
      }

      child = child.nextSibling();
    }
  }

  void
  ComponentDomParser::parseActionElement(const QDomElement &element,
                                         ComponentList::Node::Pointer node) const
  {
    Q_ASSERT(element.tagName() == "action");
    Q_CHECK_PTR(node);

    QDomNode child  = element.firstChild();

    while (!child.isNull())
    {
      if (child.toElement().tagName() == "file")
      {
        node->component()->setProperty("file", child.toElement().text());

      } else if (child.toElement().tagName() == "text")
      {
        node->component()->setProperty("text", child.toElement().text());
      } else if (child.isElement())
      {
        m_parseMap[child.toElement().tagName()](this, child.toElement(),node);
      }

      // TODO add checks for other action types

      child = child.nextSibling();
    }
  }

  void 
  ComponentDomParser::parseEventElement(const QDomElement &element,
                                        ComponentList::Node::Pointer node) const
  {
    QDomNode child = element.firstChild();
    QString value_type;
    
    while (!child.isNull())
    {
      value_type = child.toElement().tagName();
      
      if (value_type == "action")
      {
        value_type = "create_child";
      }
      
      m_parseMap[value_type](this, child.toElement(), node);

      child = child.nextSibling();
    }

  }

  void 
  ComponentDomParser::parseTrialElement(const QDomElement &element,
                                        ComponentList::Node::Pointer node) const
  {
    QDomNode child = element.firstChild();
    QString key;
    QString tagName;
    
    while (!child.isNull())
    {
      tagName = child.toElement().tagName();
      
      if (tagName == "action" || tagName == "event")
      {
        key = "create_child";
        
      } else if ( tagName == "header")
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
      
      m_parseMap[key](this, child.toElement(), node);

      child = child.nextSibling();
    }
  }

  void
  ComponentDomParser::parseExperimentElement(const QDomElement &element,
                                             ComponentList::Node::Pointer node) const
  {
    QDomNode child = element.firstChild();

    while (!child.isNull())
    {
      if (child.toElement().tagName() == "trial" ||
          child.toElement().tagName() == "action")
      {
        m_parseMap["create_child"](this, child.toElement(), node);

      } else if (child.toElement().tagName() == "header")
      {
        m_parseMap["header"](this, child.toElement(), node);

      } else if (child.toElement().tagName() == "instructions")
      {
        QString v(child.toElement().text());
        bool isProperty(false);

        isProperty = node->component()->setProperty("instructions", v);

        // if false is returned, 'instructions' is not a predefined property
        // of the component poionter. Since we *should* be dealing with
        // Experiment pointers in this block, this state is considered a
        // logic/programmer error
        Q_ASSERT(isProperty);
      }
      child = child.nextSibling();
    }
  }
  
  void 
  ComponentDomParser::parseCategoriesElement(const QDomElement &element,
                              ComponentList::Node::Pointer node) const
  {
    QDomNode item = element.firstChild();
    QString cat("");
    OutputComponent::Pointer comp = node->component().data();
    
    while (!item.isNull())
    {
      if (item.toElement().tagName() == "item")
      {
        cat = item.toElement().text();
        if (!cat.isEmpty())
        {
          m_setValueMap["categories"](comp,cat);
        }
      }
      item = item.nextSibling();
    }
    
  }
  void 
  ComponentDomParser::parseDurationElement(const QDomElement &element,
                                           ComponentList::Node::Pointer node) const
  {
    // Only ActionType components have a duration field; enforced by the
    // xml schema. Other components duration is determined by the sume of
    // its member actions
    
    // we must check the unit specification to do conversions
    // default: milliseconds
    QString units(element.attribute("unit", "msecs"));
    
    QVariant value(element.text());
    quint32 duration = value.toInt();
    
    // msecs is the default value.
    if (units == "secs")
    {
      node->component()->setProperty("units", Action::SecondType);
      duration = duration * 1000;
      
    } else if (units == "ksecs")
    {
      node->component()->setProperty("units", Action::KiloSecondType);
      duration = duration * 1000 * 1000;
    } else // default msecs
    {
      node->component()->setProperty("units", Action::MilliSecondType);
    }
    
    node->component()->setProperty("durationMSecs", duration);
  }

  void ComponentDomParser::setMainCategory(const QDomElement &element,
                                           ComponentList::Node::Pointer node) const
  {
    QString cat;
    Logger *logger = &Logger::instance();

    if (element.tagName() == "action")
    {
      // every action has a sub type specified by a type attribute.
      // enforced by xml schema
      cat = element.attribute("type").simplified();

      // in development, an empty subtype is a logic error
      Q_ASSERT(!cat.isEmpty());

      // but if it sneaks by, or a user comes up with an angle we didnt' think
      // of, we want to notify them of an invalid action
      if (cat.isEmpty())
      {
        QString msg("ComponentDomParser::setMainCategory");
        QString info(QObject::tr("Error: Action element contains no type "
                                 "attribute: %1"));

        logger->displayMessage(msg, info.arg(m_filename),
                               QMessageBox::Ok, Logger::WarningLogLevel);
      }

      // Main categories are determined by appending "Action" to it.
      cat.append(" Action");
    } else
    {
      cat = element.tagName();
    }

    // we upper case the category name for display purposes
    QChar ch = cat[0];
    cat[0] = ch.toUpper();
    node->component()->setMainCategory(cat);

  }

  void ComponentDomParser::createChildComponent(const QDomElement &element,
                                                ComponentList::Node::Pointer node) const
  {
    Q_CHECK_PTR(node);
    Q_ASSERT(isValidElement(element));
    Q_ASSERT(node->component()->componentType() & ~OutputComponent::ActionType);

    ComponentList::Node::Pointer child = createComponentNode(element);
    
    Q_CHECK_PTR(child);
    // Only non Action components  can have children, we assert this here

    parseElement(element, child);
    // Since this is a child element, it could be a template. Templates must
    // Declare a specific name of a predefined item for lookup purposes.
    // This item could be a defined previously within the parent component
    // OR it could be defined at the top most level of components in an
    // xml file. Since templates work on an overloading principle, we start by
    // looking at the top most level and then work to the inner scope.
    QString name = child->component()->name();
    ComponentList::iterator it(m_globalList.findByName(name));
    

    if (it != m_globalList.end())
    {
      child->component()->updateFromTemplate((*it)->component());
      child->children() = (*it)->children();
    }

    if (child)
    {
      node->children().push_back(child);
    } else
    {
      Logger *logger = &Logger::instance();
      // Just in case an unaccounted for release problem occurs
      QString msg("ComponentDomParser::createChild");
      QString info("Component '%1' can not have any child nodes!");

      logger->displayMessage(msg, info.arg(node->component()->name()),
                             QMessageBox::Ok, Logger::WarningLogLevel);
    }
  }
}
