#include "Config.h"

namespace kex
{
  /**
   * TODO
   */
  Config::Config() :
    m_organizationName("KSpace MRI"),
    m_domainName("kspacemri.com"),
    m_applicationName("KExperiment"),
    m_storageLocation(QString("%1/%2")
      .arg(QDesktopServices::storageLocation(QDesktopServices::DataLocation))
      .arg(m_applicationName)),
    m_componentSchemaFile(":/schemas/DataTypes.xsd")
  {
    // populate the directory type list
    m_directoryTypeList[LogDirectory]        = "Log";
    m_directoryTypeList[ActionDirectory]      = "Actions";
    m_directoryTypeList[ExperimentDirectory] = "Experiments";
    m_directoryTypeList[EventDirectory]      = "Events";
    m_directoryTypeList[TrialDirectory]      = "Trials";

  }

  const QString
  Config::dataDirectoryPath(const ApplicationDataDirectoryTypes
                            directoryType) const
  {
    QString path(storageLocation());

    path.append("/").append(m_directoryTypeList[directoryType]);

    return path;
  }

  const QStringList
  Config::dataDirectoryList(Config::ApplicationDataDirectoryTypes dt) const
  {
    QStringList directoryList;
    QMap<MetaDataType, QVariant> map;

    // add the core lists
    foreach(ApplicationDataDirectoryTypes directoryType,
            m_directoryTypeList.keys())
    {
      if ((dt & directoryType))
      {
          directoryList << dataDirectoryPath(directoryType);
      }
    }

    return directoryList;
  }

  QStringList Config::xmlFileComponentList(Config::ApplicationDataDirectoryTypes t)
  {
    QStringList         dirList;
    QStringList         xmlList;

    dirList = dataDirectoryList(t);

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


//  bool Config::registerComponentMetaData(const QString& classid,
//                                         QMap<Config::MetaDataType,
//                                          QVariant> metadata)
//  {
//    ComponentFactory *reg = &ComponentFactory::instance();
//
//    bool found = reg->componentList().contains(classid);
//
//    if (found)
//    {
//      _componentMetaDataMap[classid] = metadata;
//    }
//    return found;
//  }

//  const
//  QMap<Config::MetaDataType, QVariant> Config::metaData(QString& key) const
//  {
//    return _componentMetaDataMap[key];
//  }

  void Config::addTemplate(ApplicationDataDirectoryTypes storagePath,
                           QString temp)
  {
    m_templates.insert(storagePath, temp);
  }

  const QStringList Config::templates(ApplicationDataDirectoryTypes t) const
  {
    return m_templates.values(t);
  }


  /**
   * TODO
   */
  Config& Config::instance()
  {
    static Config _instance;
    return _instance;
  }
}
