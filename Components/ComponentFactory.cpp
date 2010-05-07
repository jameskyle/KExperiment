#include "ComponentFactory.h"

namespace kex
{
  ComponentInterface* ComponentFactory::create(QString key)
  {
    QMap<QString, Creator>::const_iterator it;
    ComponentInterface *component = 0;

    it = _componentCreatorMap.find(key);

    if(it != _componentCreatorMap.end() && (*it))
    {
      component = (*it)();
    }

    return component;
  }

  ComponentInterface* ComponentFactory::createFromXml(QFile& xml)
  {
    // we store component templates for delayed processing when parsing xml
    // files here
    ComponentInterface    *component = 0;
    ComponentInterface    *rootComponent = 0;
    QXmlStreamReader      reader;
    QXmlSchemaValidator   validator;
    QXmlSchema            schema;
    bool                  parseFile(true);

    Config                *config = &Config::instance();
    Logger                *logger = &Logger::instance();
    QFile                 sch(config->componentSchemaFile());
    QStringList           xmlFiles(Utilities::xmlFileComponentList());
    QFileInfo             xmlFileInfo(xml);

    sch.open((QFile::ReadOnly | QIODevice::Text));
    schema.load(&sch);

    if (!schema.isValid())
    {
      QString msg(QObject::tr("MainWindow::populateComponents"));
      QString info(QObject::tr("DataTypes.xsd schema is invalid! "
                   "Cannot verify template files"));
      logger->displayMessage(msg, info, QMessageBox::Ok);
    }
    validator.setSchema(schema);

    if (!xml.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QString msg("MainWindow::populateComponentList");
      QString info(QObject::tr("Couldn't open %1"));
      logger->displayMessage(msg, info.arg(xml.fileName()), QMessageBox::Ok,
                             Logger::WarningLogLevel);

      // don't try to process this file
      parseFile = false;
    }

    if (!Utilities::isValidXml(&xml, &validator))
    {
      parseFile = false;
    }

    if (parseFile)
    {
      // set source for the xml file
      reader.setDevice(&xml);
      bool rootElement(true);

      while (!reader.atEnd() && !reader.hasError())
      {
        QXmlStreamReader::TokenType token = reader.readNext();

        if (token == QXmlStreamReader::StartDocument)
        {
          continue;
        }

        if (token == QXmlStreamReader::StartElement)
        {
          if (reader.name().toString().toLower() == "action")
          {
            QXmlStreamAttributes attr(reader.attributes());

            // xsd schema ensures types are present and valid.
            QString type(attr.value(QString(""), QString("type")).toString());
            
            Action::ActionType actionType(Action::getActionType(type));
            
            component = parseAction(&reader, actionType);
            
            // if an invalid component is returned, we break the loop since 
            // parsing has failed. 
            if (!component)
            {
              break;
            }
          }
        }
        
        // If the element is a root element, we enter it into our list.
        if (rootElement && component)
        {
          rootComponent = component;
        }
        
        if (rootElement) rootElement = false;
      }
      
      if (rootComponent)
      {
        // If no override name of the rootComponent was specified, 
        // use the file name
        if (rootComponent->name().isEmpty())
        {
          rootComponent->setName(Utilities::componentNameFromBaseName(
                                                                      xmlFileInfo.baseName()));
        }
        
        // debug output of class string for each created component.
        logger->log(rootComponent->toString());
        
        // Add the component to the component list
        ComponentList *componentList = &ComponentList::instance();
        componentList->append(rootComponent);
      }
    }

    return rootComponent;
  }

  ComponentInterface* ComponentFactory::parseAction(QXmlStreamReader *reader,
                                                    Action::ActionType type)
  {
    // this method should never be passed a non-action element
    Q_ASSERT(reader->name().toString() == "action");
    
    ComponentInterface *component(0);
    QString            componentKey;
    Logger *logger = &Logger::instance();
    QFile     *file         = qobject_cast<QFile *>(reader->device());
    Q_CHECK_PTR(file);

    QString   name;
    QString   label;
    QString   description;
    quint32   duration;
    QXmlStreamAttributes attr(reader->attributes());
    QString   isTemplate(attr.value(QString(""),
                                    QString("template")).toString());
    QString mainCategory;
    QStringList categories;

    switch (type)
    {
      case Action::RestType:
        componentKey = "RestAction";
        mainCategory = "Rest Action";
        break;
      default:
        componentKey = "";
        break;
    }

    while (!reader->atEnd() && !reader->hasError() && 
           !(reader->isEndElement() && reader->name() == "action"))
    {
      QXmlStreamReader::TokenType token = reader->readNext();

      if (token == QXmlStreamReader::StartElement)
      {
        if (reader->name()        == "name")
        {
          name = reader->readElementText();

        } else if (reader->name() == "label")
        {
          label = reader->readElementText();

        } else if (reader->name() == "description")
        {
          description = reader->readElementText();

        } else if (reader->name() == "duration")
        {
          // Only ActionType components have a duration field enforced by the
          // xml schema

          // we must check the unit specification to do conversions
          // default: milliseconds
          QVariant value(reader->readElementText());
          QString unit(attr.value(QString(""), QString("unit")).toString());

          // isEmpty() == default of milliseconds
          if (unit.isEmpty() || unit == "msecs")
          {
            duration = value.toInt();
          } else if (unit == "secs")
          {
            duration = value.toInt() * 1000;

          } else if (unit == "ksecs")
          {
            duration = value.toInt() * 1000 * 1000;
          }
        } else if (reader->name().toString() == "categories")
        {
          reader->readNext();
          while (reader->name().toString() == "item")
          {
            // ignore empty category item tags
            QString cat = reader->readElementText();
            if (!cat.isEmpty())
            {
              categories << cat;
            }
          }
        }
      }
    }
    
    // Check for an invalid component. an empty key means the class has 
    // not been registered.
    if (!componentKey.isEmpty())
    {
      if (!name.isEmpty())
      {
        // If the name contains a string, we do a lookup in the 
        // ComponentList as this denotes a template style action
        ComponentList *componentList = &ComponentList::instance();

        component = componentList->find(name);
      }
      
      // if the component is not found, 0 is returned. We check for this and
      // create a default component if necessary
      if (!component)
      {
        component = create(componentKey);
      }
      
      // if we don't have a valid pointer by now, it is likely a logic error
      Q_CHECK_PTR(component);
      // Components are Copy-on-Write (CoW). We check each for a non-empty
      // value and assign it if necessary
      if (!name.isEmpty())
      {
        component->setName(name);
      }
      if (!label.isEmpty())
      {
        component->setLabel(label);
      }
      if (!description.isEmpty())
      {
        component->setDescription(description);
      }
      
      // default for duration is 0, the CoW checks to make sure the values are
      //  not equal which is sufficient in this case
      component->setDurationMSecs(duration);
      
      if (!mainCategory.isEmpty())
      {
        component->setMainCategory(mainCategory);
      }

      // add categories
      foreach(QString cat, categories)
      {
        component->addCategory(cat);
      }
    } else
    {
      QString msg("ComponentFactory::parseAction: Action"
                  "type '%1' not implemented for xml creation");

      logger->log(msg.arg(Action::getActionString(type)));
    }


    return component;
  }

  ComponentFactory& ComponentFactory::instance()
  {
    static ComponentFactory factory;
    return factory;
  }

  const QStringList ComponentFactory::componentList()
  {
    return _componentCreatorMap.keys();
  }

  bool ComponentFactory::registerComponent(const QString& name,
                                            Creator creator)
  {
    bool found = _componentCreatorMap.contains(name);

    if(!found)
    {
      _componentCreatorMap[name] = creator;
    }

    return found;
  }
}
