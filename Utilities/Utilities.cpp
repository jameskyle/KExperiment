#include "Utilities.h"

namespace kex
{
  namespace Utilities
  {
    void configureApplication()
    {

    }

    void setupAppStorageEnvironment()
    {
			QDir dir;
			
			foreach(QString path, Config::instance().dataDirectoryList())
			{
				if (!dir.exists(path))
				{
					if (!dir.mkpath(path))
					{
						QString msg("Failed to create: %1");
						Logger::log(qPrintable(msg.arg(path)));
					} else
					{
						QString msg("Created data directory: %1");
						Logger::log(qPrintable(msg.arg(path)));
					}
				}
			}
    }
  }
	
	namespace Logger
	{
		void logHandler(QtMsgType type, const char *msg) 
    {
    }
		
		void log(const char* msg, const QWidget *obj, 
						 Types::LogLevelType level)
		{
			QString prefix("[Unspecified]");
			
			if (obj)
			{
				prefix = QString("[%1]").arg(obj->metaObject()->className());
			}
			
			switch (level)
			{
				case Types::DebugLogLevel:
					qDebug() << prefix << msg;
					break;
				case Types::WarningLogLevel:
					qWarning() << prefix << msg;
					break;
				case Types::CriticalLogLevel:
					qCritical() << prefix << msg;
					break;
				case Types::FatalLogLevel:
					qFatal("%s %s", qPrintable(prefix), msg);
					break;
				default:
					qDebug() << "Log function passed an unknown LogLevel";
					break;
			}
		}
	}
}