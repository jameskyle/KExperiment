
#include <QApplication>
#include <QList>

#include <Components/ComponentRegister.h>
#include <Components/MetaData.h>
#include <Utilities/Utilities.h>
#include <Common/Global.h>

#include "MainWindow.h"

int main (int argc, char *argv[])
{
  QList<QString> categories;
  categories << "Special1" << "Special2" << "Special3" << "Special4";

  kex::REGISTER_COMPONENT("Action", kex::Action);
	kex::REGISTER_COMPONENT("Event", kex::Event);
	
  QApplication app(argc, argv);
  // initialize the Config instance
  QCoreApplication::setOrganizationDomain(
    kex::Config::instance().DOMAIN_NAME);
  QCoreApplication::setOrganizationName(
    kex::Config::instance().ORGANIZATION_NAME);
  QCoreApplication::setApplicationName(
    kex::Config::instance().APPLICATION_NAME);
  
  kex::Utilities::setupAppStorageEnvironment();
  kex::MetaData::instance().addCategories(categories);
  
  kex::MainWindow k;
  k.show();
	return app.exec();
}
