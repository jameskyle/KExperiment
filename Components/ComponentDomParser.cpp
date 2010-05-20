#include "ComponentDomParser.h"

namespace kex
{

  ComponentDomParser::ComponentDomParser()
  {

  }

  ComponentDomParser::ComponentDomParser(const QString& fileName) :
    _fileName(fileName)
  {

  }

  OutputComponent* ComponentDomParser::readFile(const QString& fileName)
  {
    _fileName = fileName;
     return readFile();
  }

  OutputComponent* ComponentDomParser::readFile()
  {
    QFile file(_fileName);
    OutputComponent *rootComponent(0);
    
    Logger *logger = &Logger::instance();

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
      QString msg("ComponentDomParser::readFile");
      QString info(QObject::tr("Error: Cannot read file : %1"));
      logger->displayMessage(msg, info.arg(file.errorString()),
                             QMessageBox::Ok, Logger::WarningLogLevel);

      return false;
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
      return false;
    }


    QDomElement root = doc.documentElement();
    if (!isValidElement(root))
    {
      QString msg("ComponentDomParser::readFile");
      QString info("Error: Not a component file: %1");
      logger->displayMessage(msg, info.arg(_fileName), QMessageBox::Ok,
                             Logger::WarningLogLevel);
      
      file.close();
      return false;
    }
    
    rootComponent = createComponent(root);
    Q_CHECK_PTR(rootComponent);
    parseElement(root, rootComponent);
    
    file.close();
    
    resolveName(rootComponent);
    
    qDebug() << rootComponent->durationMSecs();

    return rootComponent;
  }
  
  void ComponentDomParser::resolveName(OutputComponent* comp) const
  {
    QString name = comp->name();
    if (name.isEmpty())
    {
      QFileInfo info(_fileName);
      name = Utilities::componentNameFromBaseName(info.baseName());
      comp->setName(name);
    }
  }
  
  OutputComponent* 
  ComponentDomParser::createComponent(const QDomElement& root) const
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
    
    return ComponentFactory::instance().create(c_type);
  }
  
  bool ComponentDomParser::isValidElement(const QDomElement &element) const
  {
    bool isValid(false);
    
//    if (element.tagName() == "action" || element.tagName() == "event" ||
//        element.tagName() == "trial")
//    {
//      if (element.attribute("template", "false") == "false" )
//      {
//        
//      }
//    }
    
    if (element.tagName() == "action" || element.tagName() == "event" ||
        element.tagName() == "trial"  || element.tagName() == "experiment" ||
        element.tagName() == "header")
    {
      isValid = true;
    }

    return isValid;
  }

  void ComponentDomParser::parseElement(const QDomElement &element,
                                        OutputComponent* component) const
  {
    // should only receive valid elements.
    Q_ASSERT(isValidElement(element));
    Q_CHECK_PTR(component);
    // this method should never be passed a header tag
    Q_ASSERT(element.tagName() != "header");
    setMainCategory(element, component);
    
    if (element.tagName() == "action")
    {
      parseActionElement(element, component);

    } else if (element.tagName() == "event")
    {
      parseEventElement(element, component);
      
    } else if (element.tagName() == "trial")
    {
      parseTrialElement(element, component);
      
    } else if (element.tagName() == "experiment")
    {
      parseExperimentElement(element, component);
    }
  }
  
  void 
  ComponentDomParser::parseHeaderElement(const QDomElement &element,
                                         OutputComponent* component) const
  {
    Q_ASSERT(element.tagName() == "header");
    Q_CHECK_PTR(component);

    QDomNode child = element.firstChild();

    while (!child.isNull())
    {
      if (child.toElement().tagName() == "name")
      {
        component->setName(child.toElement().text());

      } else if (child.toElement().tagName() == "label")
      {
        component->setLabel(child.toElement().text());

      } else if (child.toElement().tagName() == "description")
      {
        component->setDescription(child.toElement().text());
      } else if (child.toElement().tagName() == "categories")
      {
        QDomNode item = child.toElement().firstChild();
        QString cat("");

        while (!item.isNull())
        {
          if (item.toElement().tagName() == "item")
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

      child = child.nextSibling();
    }
  }

  void 
  ComponentDomParser::parseActionElement(const QDomElement &element,
                                         OutputComponent* component) const
  {
    Q_ASSERT(element.tagName() == "action");
    Q_CHECK_PTR(component);

    QDomNode child  = element.firstChild();
    bool propertySetSuccess(false);
    
    while (!child.isNull())
    {
      // Actions have no children components, so we don't check for them
      if (child.toElement().tagName() == "header")
      {
        parseHeaderElement(child.toElement(), component);

      } else if (child.toElement().tagName() == "duration")
      {
        // Only ActionType components have a duration field; enforced by the
        // xml schema. Other components duration is determined by the sume of
        // its member actions

        // we must check the unit specification to do conversions
        // default: milliseconds
        QString units(child.toElement().attribute("unit", "msecs"));

        QVariant value(child.toElement().text());
        quint32 duration = value.toInt();
        
        // msecs is the default value.
        if (units == "secs")
        {
          component->setProperty("units", Action::SecondType);
          duration = duration * 1000;

        } else if (units == "ksecs")
        {
          component->setProperty("units", Action::KiloSecondType);
          duration = duration * 1000 * 1000;
        } else // default msecs
        {
          component->setProperty("units", Action::MilliSecondType);
        }

        component->setProperty("durationMSecs", duration);

      } else if (child.toElement().tagName() == "file")
      {
        component->setProperty("file", child.toElement().text());

      } else if (child.toElement().tagName() == "text")
      {
        component->setProperty("text", child.toElement().text());
      }
      // TODO add checks for other action types

      child = child.nextSibling();
    }
  }
  
  void ComponentDomParser::parseEventElement(const QDomElement &element,
                                             OutputComponent* component) const
  {
    QDomNode child = element.firstChild();
    
    while (!child.isNull())
    {
      if (child.toElement().tagName() == "action")
      {
        
        createChildComponent(child.toElement(), component);

        
      } else if (child.toElement().tagName() == "header")
      {
        parseHeaderElement(child.toElement(), component);
      }
      child = child.nextSibling();
    }
    
  }
  
  void ComponentDomParser::parseTrialElement(const QDomElement &element,
                                             OutputComponent* component) const
  {
    QDomNode child = element.firstChild();
    
    while (!child.isNull())
    {
      if (child.toElement().tagName() == "action" ||
          child.toElement().tagName() == "event")
      {
        createChildComponent(child.toElement(), component);
//        AggregateComponent *g = dynamic_cast<AggregateComponent *>(component);
//        qDebug() << "parent node: " << g->name();
//        qDebug() << "num children: " << (g->childComponents()).count();
//        ComponentList::ComponentQListIterator it(dynamic_cast<AggregateComponent *>(component)->childComponents());
//        OutputComponent *f;
//        while (it.hasNext())
//        {
//          f = it.next();
//          qDebug() << "name: " << f->name();
//          qDebug() << "duration: " << f->durationMSecs();
//        }
//        qDebug() << "total duration: " << component->durationMSecs();
        
      } else if (child.toElement().tagName() == "header")
      {
        parseHeaderElement(child.toElement(), component);
      } else
      {
        Logger *logger = &Logger::instance();
        QString msg("ComponentDomParser::parseTrialElement");
        QString info(QObject::tr("Unrecognized element found in %1: %2"));
        logger->displayMessage(msg, info.arg(element.tagName())
                                        .arg(child.toElement().tagName()), 
                               QMessageBox::Ok, Logger::WarningLogLevel);
      }

      child = child.nextSibling();
    }
  }
  
  void 
  ComponentDomParser::parseExperimentElement(const QDomElement &element,
                                             OutputComponent* component) const
  {
    QDomNode child = element.firstChild();
    
    while (!child.isNull())
    {
      if (child.toElement().tagName() == "trial" ||
          child.toElement().tagName() == "action")
      {
        createChildComponent(child.toElement(), component);
        
      } else if (child.toElement().tagName() == "header")
      {
        parseHeaderElement(child.toElement(), component);
        
      } else if (child.toElement().tagName() == "instructions")
      {
        QString v(child.toElement().text());
        bool isProperty(false);
        
        isProperty = component->setProperty("instructions", v);
        
        // if false is returned, 'instructions' is not a predefined property
        // of the component poionter. Since we *should* be dealing with 
        // Experiment pointers in this block, this state is considered a 
        // logic/programmer error
        Q_ASSERT(isProperty);
      }
      child = child.nextSibling();
    }
  }
  
  void ComponentDomParser::setMainCategory(const QDomElement &element,
                                           OutputComponent* component) const
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

        logger->displayMessage(msg, info.arg(_fileName),
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
    component->setMainCategory(cat);

  }
  
  void ComponentDomParser::createChildComponent(const QDomElement &element, 
                                                OutputComponent *comp) const
  {
    Q_CHECK_PTR(comp);
    Q_ASSERT(isValidElement(element));
    
    OutputComponent::SharedPointer child(createComponent(element));
    parseElement(element, child.data());
    // Since this is a child element, it could be a template. Templates must
    // Declare a specific name of a predefined item for lookup purposes.
    // This item could be a defined previously within the parent component
    // OR it could be defined at the top most level of components in an 
    // xml file. Since templates work on an overloading principle, we start by
    // looking at the top most level and then work to the inner scope.
    
    ComponentList *c_list = &ComponentList::instance();
    OutputComponent::SharedPointer templ = c_list->find(child->name());
    
    // ComponentList::find() returns 0 if component not found.
    
    if (templ)
    {
      child->updateFromTemplate(templ);
    }
    // Only AggregateComponents can have children, so we must downcast
    AggregateComponent *c = qobject_cast<AggregateComponent *>(comp);
    
    Q_CHECK_PTR(c); // logic error if passed the wrong component 

    if (c)
    {
      c->appendChild(child);
      
    } else
    {
      Logger *logger = &Logger::instance();
      // Just in case an unaccounted for release problem occurs
      QString msg("ComponentDomParser::createChild");
      QString info("Component '%1' can not have any child nodes!");
      
      logger->displayMessage(msg, info.arg(comp->name()), 
                             QMessageBox::Ok, Logger::WarningLogLevel);
    }
  }
}
