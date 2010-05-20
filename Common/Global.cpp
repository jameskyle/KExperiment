#include "Global.h"

namespace kex
{
  /**
   * TODO
   */
  Config::Config() :
    _organizationName("KSpace MRI"),
    _domainName("kspace-mri.com"),
    _applicationName("KExperiment"),
    _storageLocation(QString("%1/%2")
      .arg(QDesktopServices::storageLocation(QDesktopServices::DataLocation))
      .arg(_applicationName)),
    _componentSchemaFile(":/schemas/DataTypes.xsd")
  {
    // populate the directory type list
    _directoryTypeList[LogDirectory]        = "Log";
    _directoryTypeList[ActionDirectory]      = "Actions";
    _directoryTypeList[ExperimentDirectory] = "Experiments";
    _directoryTypeList[EventDirectory]      = "Events";
    _directoryTypeList[TrialDirectory]      = "Trials";
  }

  const QString
  Config::dataDirectoryPath(const ApplicationDataDirectoryTypes
                            directoryType) const
  {
    QString path(storageLocation());

    path.append("/").append(_directoryTypeList[directoryType]);

    return path;
  }

  const QStringList
  Config::dataDirectoryList(Config::ApplicationDataDirectoryTypes dt) const
  {
    QStringList directoryList;
    QMap<MetaDataType, QVariant> map;

    // add the core lists
    foreach(ApplicationDataDirectoryTypes directoryType,
            _directoryTypeList.keys())
    {
      if ((dt & directoryType))
      {
          directoryList << dataDirectoryPath(directoryType);
      }
    }

    return directoryList;
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
    _templates.insert(storagePath, temp);
  }

  const QStringList Config::templates(ApplicationDataDirectoryTypes t) const
  {
    return _templates.values(t);
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
