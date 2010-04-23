#include "Utilities.h"

namespace kex
{
  namespace Utilities
  {
    void setupAppStorageEnvironment()
    {
      QDir dir;
      Logger *logger;
      Config *config;
      QStringList dataDirectoryList;
      
      logger = &Logger::instance();
      config = &Config::instance();

      dataDirectoryList = config->dataDirectoryList((Config::LogDirectory | 
                                                    Config::ActionDirectory |
                                                    Config::ExperimentDirectory |
                                                    Config::EventDirectory |
                                                    Config::TrialDirectory));
      foreach(QString path, dataDirectoryList)
      {
        if (!dir.exists(path))
        {
          if (!dir.mkpath(path))
          {
            // On error, make a log entry and alert the user
            QString msg = QObject::tr("Could not create directory.");
            QString info = QObject::tr("There was an error creating user template "
                              "directories. Please ensure that %1 exists and "
                              "write permissions are enabled.");
            
            logger->log(qPrintable(msg.arg(path)), 0, Logger::CriticalLogLevel);
            logger->displayMessage(msg, info.arg(config->storageLocation()));
            // we don't continue attempting directory creation if something 
            // fails
            break;
          } else
          {
            QString msg("Created data directory: %1");
            logger->log(qPrintable(msg.arg(path)));
          }
        }
      }
    }
    
    void writeTemplateFiles()
    {
      QStringList componentList;
      Config *config;
      ComponentRegister *reg;
      Logger *logger;
      
      reg = &ComponentRegister::instance();
      config = &Config::instance();
      logger = &Logger::instance();
      componentList = reg->componentList();
      
      // create directories if they've been deleted 
      setupAppStorageEnvironment();

      foreach(QString component, componentList)
      {
        QMap<Config::MetaDataType, QVariant> map;
        QVariant resource;
        QFile outFile; // the file we're writing out to
        QFile inFile;  // the file we're reading from
        
        map = config->metaData(component);
        resource = map[Config::TemplateResourcePath];
        
        // we only perform the action for components with a template entry
        if (resource.isValid())
        {
          inFile.setFileName(resource.toString());
          outFile.setFileName(map[Config::ComponentTemplatePath].toString());
        } else 
        {
          QString msg("No template configured for: %1");
          logger->log(qPrintable(msg.arg(component)));
          continue;
        }
        
        // break the loop if file exists, we assume it's been overwritten or 
        // customized.
        if (outFile.exists())
        {
          continue;
        }
        
        // quit and display error message if error is encountered
        if (!outFile.open(QIODevice::ReadWrite))
        {
          QString msg = QObject::tr("Could not access file.");
          QString info = QObject::tr("There was an error accessing a file."
                                     "Please ensure the file exists and is "
                                     "accessible: %1");
          
          logger->log(qPrintable(msg));
          logger->displayMessage(msg, info.arg(outFile.fileName()));
          break;
        }
        
        bool noerr = inFile.open(QIODevice::ReadOnly);
        // we insist that all registered resources are present at
        Q_ASSERT(noerr); 
        
        //outFile.write(inFile.readAll(), inFile.size());
      }
      // iterate over template files, write them out if they don't exist.      
    }
    
    void registerComponents()
    {
      Config *config = &Config::instance();
      QString path;
      
      // Register the applications components and assign their metadata.
      // First the Action base class
      QMap<Config::MetaDataType, QVariant> metaDataMap;
      metaDataMap[Config::TemplateResourcePath] = ":/templates/actions.xml";
      path = config->dataDirectoryPath(Config::ActionDirectory);

      metaDataMap[Config::ComponentTemplatePath] = path.append("/")
                                                       .append("kactions.xml");
      REGISTER_COMPONENT("Action", Action, metaDataMap);
      
      // RestAction, a subclass of Action. It has no dedicated template, 
      // so we clear the metadata
      metaDataMap.clear();
      REGISTER_COMPONENT("RestAction", RestAction, metaDataMap);
        
      metaDataMap.clear();
      metaDataMap[Config::TemplateResourcePath] = ":/templates/events.xml";
      path = config->dataDirectoryPath(Config::EventDirectory);
      metaDataMap[Config::ComponentTemplatePath] = path.append("/")
                                                      .append("kevents.xml");
      REGISTER_COMPONENT("Event", Event, metaDataMap);
    }
    
    void configureApplication()
    {
      // initialize the Config instance
      QCoreApplication::setOrganizationDomain(
                        kex::Config::instance().domainName());
      QCoreApplication::setOrganizationName(
                        kex::Config::instance().organizationName());
      QCoreApplication::setApplicationName(
                        kex::Config::instance().applicationName());
      
      // register comoponents
      registerComponents();
      
      // set up the application data storage
      setupAppStorageEnvironment();
      
      // create template files if needed
      writeTemplateFiles();
    }

  }
}