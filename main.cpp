#include <QApplication>
#include <QString>
#include <QWizardPage>
#include "MainWindow.h"
#include "Common.h"

int main (int argc, char *argv[])
{
  QList<QString> categories;
  categories << "Special1" << "Special2" << "Special3" << "Special4";
  kex::REGISTER_COMPONENT("Action", kex::Action);
  
  QApplication app(argc, argv);
  kex::Utilities::setupAppStorageEnvironment();
  kex::MetaData::instance().addCategories(categories);
  
  kex::MainWindow k;

  k.show();
  return app.exec();
}
