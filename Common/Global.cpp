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
      .arg(_applicationName))
  {
    // populate the directory type list
    _directoryTypeList[LogDirectory]        = "Log";
    _directoryTypeList[ActionDirectory]      = "Actions";
    _directoryTypeList[ExperimentDirectory] = "Experiments";
    _directoryTypeList[EventDirectory]      = "Events";
    _directoryTypeList[TrialDirectory]      = "Trials";
  }
  
  const QString 
  Config::dataDirectoryPath(const ApplicationDataDirectoryType 
                            directoryType) const
  {
    QString path(storageLocation());
    
    path.append("/").append(_directoryTypeList[directoryType]);
    
    return path;
  }
    
  const QStringList
  Config::dataDirectoryList(const int dt) const
  {
    QStringList directoryList;
    QMap<MetaDataType, QVariant> map;
    
    // add the core lists
    foreach(ApplicationDataDirectoryType directoryType, 
            _directoryTypeList.keys())
    {
      if ((dt & directoryType))
      {
          directoryList << dataDirectoryPath(directoryType);
      }
    }
    
    return directoryList;
  }
  
  bool Config::registerComponentMetaData(const QString& classid, 
                                         QMap<Config::MetaDataType, 
                                          QVariant> metadata) 
  {
    ComponentRegister *reg = &ComponentRegister::instance();

    bool found = reg->componentList().contains(classid);
    
    if (found)
    {
      _componentMetaDataMap[classid] = metadata;
    }
    return found;
  }
  
  const 
  QMap<Config::MetaDataType, QVariant> Config::metaData(QString& key) const
  {
    return _componentMetaDataMap[key];
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