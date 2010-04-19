#ifndef GLOBAL_H
#define GLOBAL_H
#include <vector>

#include <QString>
#include <QDesktopServices>
#include <QMessageBox>

#include <Common/Types.h>
#include <Utilities/Utilities.h>
#include <Common/Uncopyable.h>
#include <Common/Logger.h>
#include <Components/ComponentRegister.h>

namespace kex
{
		/** \brief  Holds common configuration valus for application
	 * 
	 * Copyright 2010 KSpace MRI. All Rights Reserved.
	 *
	 * \author James Kyle
	 * \author $LastChangedBy$
	 * \date 2010-4-8
	 * \date $LastChangedDate$
	 * \version $Rev$  \sa Types.h Global.h
	 **/
	class Config : private Uncopyable
	{
	public:
		static Config& instance();
		
		
		enum MetaDataType {
			TemplateResourcePath			= 0x1,
			ComponentTemplatePath			= 0x2,
			CustomDirectoryPath				= 0x4,
		};
		
		enum ApplicationDataDirectoryType {
			LogDirectory								= 0x1,
			ActionDirectory					    = 0x2,
			ExperimentDirectory					= 0x4,
			EventDirectory							= 0x8,
			TrialDirectory						  = 0x10,
			TemplateDirectory						= 0x20,
		};
		
		/** \brief  Returns the storage location path for this application
		 * 
		 * Copyright 2010 KSpace MRI. All Rights Reserved.
		 * 
		 * \author James Kyle
		 * \author $LastChangedBy$
		 * \date 2010-4-10
		 * \date $LastChangedDate$
		 * \param directoryType the type of directory 
		 * \return QString holds the path tot he directory
		 * \version $Rev$  \sa Types::DataDirectoryType
		 **/
		const QString 
		dataDirectoryPath(const ApplicationDataDirectoryType directoryType) const;
			
		/** \brief  Returns a list of all data directories
		 * 
		 * Copyright 2010 KSpace MRI. All Rights Reserved.
		 *
		 * The application uses several data directories for holding templates, 
		 * user defined components, and cache data. This method returns a list of all
		 * these directories.
		 * 
		 * \author James Kyle
		 * \author $LastChangedBy$
		 * \date 2010-4-10
		 * \date $LastChangedDate$
		 * \version $Rev$  
		 * \sa Types::DataDirectoryType 
		 * \sa Utilities::setupAppStorageEnvironment
		 **/
		const QStringList dataDirectoryList(const int dt) const;
		
		/** \brief  Registers metadata associated with the requested class.
		 * 
		 * Copyright 2010 KSpace MRI. All Rights Reserved.
		 *
		 * Each class has an associated set of metadata such as the lcoation of its 
		 * xml template file. This registers that metadata and allows lookups based 
		 * on the registered classes identifier. 
		 * 
		 * \author James Kyle
		 * \author $LastChangedBy$
		 * \date 2010-4-13
		 * \date $LastChangedDate$
		 * \param classid id of the class to set the metadata for
		 * \prarm metadata a map of metadata values for this class
		 * \return bool true if the class is found in the register list, false if not
		 * \version $Rev$  \sa ComonentRegister()
		 **/
		bool registerComponentMetaData(const QString& classid,
																	 QMap<Config::MetaDataType, 
																	 QVariant> metadata);
		
		/** \brief  Returns the metadata for a class
		 * 
		 * Copyright 2010 KSpace MRI. All Rights Reserved.
		 *
		 * Each registered class has a metadtat type that stores class specific 
		 * application data. 
		 * 
		 * \author James Kyle
		 * \author $LastChangedBy$
		 * \date 2010-4-15
		 * \date $LastChangedDate$
		 * \param key a string specifying the registered class 
		 * \version $Rev$ 
		 **/
		const QMap<Config::MetaDataType, QVariant> metaData(QString& key) const;
		
		const QString organizationName() const {return _organizationName;}
		const QString domainName() const {return _domainName;}
		const QString applicationName() const {return _applicationName;}
		const QString storageLocation() const {return _storageLocation;}
		
		
	private:
		QString _organizationName;
		QString _domainName;
		QString _applicationName;
		QString _storageLocation;
		
		//!< map of class's application metadata
		QMap<QString, QMap<MetaDataType, QVariant> > _componentMetaDataMap;
		
		// map between an ApplicationDataDirectoryType and its name
		QMap<ApplicationDataDirectoryType, QString> _directoryTypeList;
		
		Config();
		~Config() {}
	};
}

#endif