#include "Logger.h"

namespace kex
{
  Logger& Logger::instance()
  {
    static Logger log;
    return log;
  }
  
  void Logger::log(const char* msg, const QWidget *obj, 
                              Logger::LogLevelType level)
  {
    QString prefix("[Unspecified]");
    
    if (obj)
    {
      prefix = QString("[%1]").arg(obj->metaObject()->className());
    }
    
    switch (level)
    {
      case Logger::DebugLogLevel:
        qDebug() << prefix << msg;
        break;
      case Logger::WarningLogLevel:
        qWarning() << prefix << msg;
        break;
      case Logger::CriticalLogLevel:
        qCritical() << prefix << msg;
        break;
      case Logger::FatalLogLevel:
        qFatal("%s %s", qPrintable(prefix), msg);
        break;
      default:
        qDebug() << "Log function passed an unknown LogLevel";
        break;
    }
  }
  
  void Logger::displayMessage(const QString& text, const QString& info) const
  {
    QMessageBox box;
    box.setText(text);
    box.setInformativeText(info);
    box.exec();
  }


}