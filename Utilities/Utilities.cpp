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

      // FIXME http://tinyurl.com/2ga3sdx
      Config::ApplicationDataDirectoryTypes dt(Config::LogDirectory |
                                               Config::ActionDirectory |
                                               Config::ExperimentDirectory |
                                               Config::EventDirectory |
                                               Config::TrialDirectory);

      dataDirectoryList = config->dataDirectoryList(dt);
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
      QStringList templates;
      QList<Config::ApplicationDataDirectoryTypes> dirs;
      Logger *logger = &Logger::instance();
      Config *config = &Config::instance();

      dirs << Config::ActionDirectory << Config::ExperimentDirectory
           << Config::EventDirectory << Config::TrialDirectory;

      // create directories if they've been deleted
      setupAppStorageEnvironment();

      foreach(Config::ApplicationDataDirectoryTypes t, dirs)
      {
        // retrieve all stored templates for data directory t
        templates = config->templates(t);

        foreach(QString f, templates)
        {
          QFile outFile;
          QFile inFile;
          QFileInfo fi(f);

          inFile.setFileName(f);

          outFile.setFileName((config->dataDirectoryPath(t) +
                               "/" + fi.fileName()));

          if (outFile.exists()) {continue;}

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

            outFile.write(inFile.readAll(), inFile.size());
        }
      }
    }

    void registerComponents()
    {
      Config *config = &Config::instance();
      QMap<QString, Config::ApplicationDataDirectoryTypes> resource_roots;
      QMap<QString, Config::ApplicationDataDirectoryTypes>::iterator it;
      QDir templates;
      QString path = ":templates/%1";

      // First we add all the component templates to our config::templates
      // list
      resource_roots["actions"]     = Config::ActionDirectory;
      resource_roots["events"]      = Config::EventDirectory;
      resource_roots["trials"]      = Config::TrialDirectory;
      resource_roots["experiments"] = Config::ExperimentDirectory;

      for (it = resource_roots.begin(); it != resource_roots.end(); ++it)
      {
        QString full_path = path.arg(it.key());

        if (templates.exists(full_path))
        {
          templates.setPath(full_path);

          foreach(QString st, templates.entryList())
          {
            QString resource_path = full_path;
            resource_path.append("/").append(st);
            config->addTemplate(it.value(), resource_path);
          }
        }
      }
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

    bool isValidXml(QFile *file, const QXmlSchemaValidator *validator)
    {
      bool valid = false;
      Logger *logger = &Logger::instance();

      if (validator->validate(file))
      {
        valid = true;
      } else
      {
        QString msg("Utilities::validateXml");
        QString info("The component file is invalid xml: %1");
        logger->displayMessage(msg, info.arg(file->fileName()), QMessageBox::Ok);
      }
      // reset the file to the zero position
      file->seek(0);

      return valid;
    }

    QStringList xmlFileComponentList(Config::ApplicationDataDirectoryTypes t)
    {
      QStringList         dirList;
      QStringList         xmlList;
      Config              *config = &Config::instance();

      dirList = config->dataDirectoryList(t);

      foreach(QString path, dirList)
      {
        QDir dir(path);
        QStringList filters;
        QStringList fileList;

        filters << "*.xml";
        dir.setNameFilters(filters);
        fileList = dir.entryList(QDir::Files);

        foreach(QString file, fileList)
        {
          QString fullPath("%1/%2");
          xmlList << fullPath.arg(path).arg(file);
        }
      }
      return xmlList;
    }

    QString componentNameFromBaseName(const QString& baseName)
    {
      QString componentName(baseName);
      QString output;
      // remove .xml extenstion and replace '_' with a space
      componentName.replace("_", " ");

      // insert a space before each camelcase, the size and character position
      // of fileName and componentName before the loop are the same, so we can
      // iterate over fileName for the char values.
      for(int i = 0;i < componentName.count(); ++i)
      {
        if (baseName[i].isUpper())
        {
          output.append(" ").append(componentName[i]);
        } else
        {
          output.append(componentName[i]);
        }

      }
      return output.simplified();
    }
    
    QString componentNameFromFilePath(const QString& path)
    {
      QFileInfo info(path);
      return componentNameFromBaseName(info.baseName());
    }


  } // END_UTILITIES
} // END_KEX_NAMESPACE