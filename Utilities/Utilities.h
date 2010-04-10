#ifndef UTILITIES_H
#define UTILITIES_H

#include <QFile>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QObject>
#include <QApplication>
#include <QWidget>

#include <Common/Global.h>

namespace kex
{
  namespace Utilities
  {
    void setupAppStorageEnvironment();
    void configureApplication();
 	};
			
	namespace Logger
	{
		void logHandler(QtMsgType type, const char *msg);
		
		/** \brief  Logs any debug info
	   * 
		 * Copyright 2010 KSpace MRI. All Rights Reserved.
		 *
		 * Simple logging to qDebug with metaobject identifier prepended
		 * 
		 * \author James Kyle
		 * \author $LastChangedBy$
		 * \date 2010-4-6
		 * \date $LastChangedDate$
		 * \param obj, the object sending the message
		 * \param msg the message to be sent
		 * \version $Rev$  \sa qDebug()
		 **/
		void log(const char* msg, const QWidget *obj = 0, 
						 Types::LogLevelType level = Types::DebugLogLevel);
	}
	
}
#endif