#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QDesktopServices>

#include <Common/Types.h>
#include <Utilities/Utilities.h>
#include <Common/Uncopyable.h>

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
		const QString dataDirectoryPath(
									const Types::DataDirectoryType directoryType) const;


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
		const QStringList dataDirectoryList(Types::DataDirectoryType dt =
																				Types::AllDataDirectories) const;

		const QString ORGANIZATION_NAME;
		const QString DOMAIN_NAME;
		const QString APPLICATION_NAME;
		const QString STORAGE_LOCATION;
		
	private:
		Config();
		~Config() {}
	};
}

#endif