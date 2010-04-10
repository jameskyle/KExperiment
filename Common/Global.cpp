#include "Global.h"

namespace kex
{
  /**
   * TODO
   */
  Config::Config() :
    ORGANIZATION_NAME("KSpace MRI"),
    DOMAIN_NAME("kspace-mri.com"),
    APPLICATION_NAME("KExperiment"),
    STORAGE_LOCATION(QString("%1/%2")
      .arg(QDesktopServices::storageLocation(QDesktopServices::DataLocation))
      .arg(APPLICATION_NAME))
  { 
  }
  
	const QString 
	Config::dataDirectoryPath(const Types::DataDirectoryType directoryType) const
	{
		QString path(STORAGE_LOCATION);
		
		switch (directoryType)
		{
			case Types::LogDirectoryType:
				path.append("/Log");
				break;
			case Types::ExperimentDirectoryType:
				path.append("/Experiments");
				break;
			case Types::TemplateDirectoryType:
				path.append("/Templates");
				break;
			case Types::ActionTemplateDirectoryType:
				path.append("/Templates/Actions");
				break;
			case Types::EventTemplateDirectoryType:
				path.append("/Templates/Events");
				break;
			case Types::TrialTemplateDirectoryType:
				path.append("/Templates/Trials");
				break;
			case Types::ExperimentTemplateDirectoryType:
				path.append("/Templates/Experiments");
				break;
			default:
				path.clear();
				break;
		}
		
		return path;
	}
	
	const QStringList Config::dataDirectoryList(Types::DataDirectoryType dt) const
	{
		QStringList directoryList;
		
		if ((dt & Types::LogDirectoryType))
		{
			directoryList << dataDirectoryPath(Types::LogDirectoryType);
		}
		if ((dt & Types::ExperimentDirectoryType))
		{
			directoryList << dataDirectoryPath(Types::ExperimentDirectoryType);
		}
		if ((dt & Types::TemplateDirectoryType))
		{
			directoryList << dataDirectoryPath(Types::TemplateDirectoryType);
		}
		if ((dt & Types::ActionTemplateDirectoryType))
		{
			directoryList << dataDirectoryPath(Types::ActionTemplateDirectoryType);
		}
		if ((dt & Types::EventTemplateDirectoryType))
		{
			directoryList << dataDirectoryPath(Types::EventTemplateDirectoryType);
		}
		if ((dt & Types::TrialTemplateDirectoryType))
		{
			directoryList << dataDirectoryPath(Types::TrialTemplateDirectoryType);
		}
		if ((dt & Types::ExperimentTemplateDirectoryType))
		{
			directoryList << dataDirectoryPath(
											 Types::ExperimentTemplateDirectoryType);
		}
		
		return directoryList;
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