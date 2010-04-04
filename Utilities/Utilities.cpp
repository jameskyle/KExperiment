#include "Utilities.h"

namespace kex
{
  namespace Utilities
  {
    void configAppEnvironment(QApplication *app)
    {
      // Configure a few application specific variables
       app->setOrganizationDomain(Config::instance().organizationName());
    }

    void setupAppStorageEnvironment()
    {
      QString log_dir(QObject::tr("%1/Log").arg(Config::instance() .storageLocation()));
      qDebug() << log_dir << "\n";
    }
  }
  
}