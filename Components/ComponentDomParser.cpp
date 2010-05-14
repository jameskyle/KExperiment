#include "ComponentDomParser.h"

namespace kex
{

  ComponentDomParser::ComponentDomParser() :
    _rootComponent(0)

  {

  }

  ComponentDomParser::ComponentDomParser(const QString& fileName) :
    _rootComponent(0),
    _fileName(fileName)
  {

  }

  bool ComponentDomParser::readFile(const QString& fileName)
  {
    _fileName = fileName;
     return readFile();
  }

  bool ComponentDomParser::readFile()
  {
    QFile file(_fileName);
    
    _rootComponent = AbstractComponent::Pointer(new AbstractComponent);
    
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

    parseElement(root, _rootComponent.data());
    
    file.close();
    return true;
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
                                        AbstractComponent* component) const
  {
    // should only receive valid elements.
    Q_ASSERT(isValidElement(element));
    Q_CHECK_PTR(component);

    setMainCategory(element, component);

    if (element.tagName() == "action")
    {
      component->setComponentType(ComponentInterface::ActionType);
      parseActionElement(element, component);

    } else if (element.tagName() == "header")
    {
      parseHeaderElement(element, component);
    }
    else if (element.tagName() == "event")
    {
      QDomNode child = element.firstChild();

      component->setComponentType(ComponentInterface::EventType);

      while (!child.isNull())
      {
        if (child.toElement().tagName() == "action")
        {
          createChildComponent(element, component);
          
        } else if (child.toElement().tagName() == "header")
        {
          parseHeaderElement(child.toElement(), component);
        }
        child = child.nextSibling();
      }
    } else if (element.tagName() == "trial")
    {
      QDomNode child = element.firstChild();

      component->setComponentType(ComponentInterface::TrialType);

      while (!child.isNull())
      {
        if (child.toElement().tagName() == "action" ||
            child.toElement().tagName() == "event")
        {
          createChildComponent(element, component);
          
        } else if (child.toElement().tagName() == "header")
        {
          parseHeaderElement(child.toElement(), component);
        }
        child = child.nextSibling();
      }

    } else if (element.tagName() == "experiment")
    {
      QDomNode child = element.firstChild();

      component->setComponentType(ComponentInterface::ExperimentType);

      while (!child.isNull())
      {
        if (child.toElement().tagName() == "trial" ||
            child.toElement().tagName() == "action")
        {
          createChildComponent(element, component);
          
        } else if (child.toElement().tagName() == "header")
        {
          parseHeaderElement(child.toElement(), component);
        } else if (child.toElement().tagName() == "instructions")
        {
          QVariant v(child.toElement().text());
          component->setValue("instructions", v);
        }
        child = child.nextSibling();
      }
    }
  }

  void 
  ComponentDomParser::parseHeaderElement(const QDomElement &element,
                                         AbstractComponent* component) const
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
                                         AbstractComponent* component) const
  {
    Q_ASSERT(element.tagName() == "action");
    Q_CHECK_PTR(component);

    QDomNode child  = element.firstChild();

    while (!child.isNull())
    {
      // Actions have no children components, so we don't check for them
      if (child.toElement().tagName() == "header")
      {
        parseElement(child.toElement(), component);

      } else if (child.toElement().tagName() == "duration")
      {
        // Only ActionType components have a duration field; enforced by the
        // xml schema. Other components duration is determined by the sume of
        // its member actions

        // we must check the unit specification to do conversions
        // default: milliseconds
        QString units(child.toElement().attribute("unit", "msecs"));

        component->setAttribute("units", units);
        QVariant value(child.toElement().text());
        quint32 duration = value.toInt();

        // msecs is the default value.
        if (units == "secs")
        {
          duration = duration * 1000;

        } else if (units == "ksecs")
        {
          duration = duration * 1000 * 1000;
        }
      
        value.setValue(duration);
        component->setValue("duration", value);

      } else if (child.toElement().tagName() == "file")
      {
        QVariant fileName(child.toElement().text());
        component->setValue("file", fileName);

      } else if (child.toElement().tagName() == "text")
      {
        QVariant text(child.toElement().text());
        component->setValue("text", text);
      }
      // TODO add checks for other action types

      child = child.nextSibling();
    }
  }

  void ComponentDomParser::setMainCategory(const QDomElement &element,
                                           AbstractComponent* component) const
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
        QString info("Error: Action element contains no type attribute: %1");

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
                                           AbstractComponent *comp) const
  {
    Q_CHECK_PTR(comp);
    Q_ASSERT(isValidElement(element));
    
    AbstractComponent::Pointer c(new AbstractComponent);
    parseElement(element, c.data());
    comp->appendChild(c);
  }
}
