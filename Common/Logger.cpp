#include "Logger.h"

namespace kex
{
  Logger& Logger::instance()
  {
    static Logger log;
    return log;
  }

  void Logger::log(const char* msg, const QObject *obj,
                              Logger::LogLevelType level)
  {
    QString prefix("[Unspecified Object]");

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

  void Logger::log(const QString& msg, const QObject *obj,
                   Logger::LogLevelType level)
  {
    log(qPrintable(msg), obj, level);
  }

  void Logger::displayMessage(const QString& text,
                              const QString& info,
                              QMessageBox::StandardButton button,
                              Logger::LogLevelType level) const
  {
    QMessageBox box;
    box.setText(text);
    box.setInformativeText(info);
    box.setDefaultButton(button);
    switch (level)
    {
      case Logger::DebugLogLevel:
        box.setIcon(QMessageBox::Information);
        break;
      case Logger::WarningLogLevel:
        box.setIcon(QMessageBox::Warning);
        break;
      case Logger::CriticalLogLevel:
        box.setIcon(QMessageBox::Critical);
        break;
      case Logger::FatalLogLevel:
        box.setIcon(QMessageBox::Critical);
        break;
      default:
        qDebug() << "Log function passed an unknown LogLevel";
        break;
    }
    box.exec();

  }
} // END_KEX_NAMESPACE
