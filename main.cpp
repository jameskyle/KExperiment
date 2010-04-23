
#include <QApplication>
#include <QList>

#include <Components/ComponentRegister.h>
#include <Components/MetaData.h>
#include <Utilities/Utilities.h>
#include <Common/Global.h>
#include <QTreeView>
#include "MainWindow.h"

int main (int argc, char *argv[])
{
  QApplication app(argc, argv);

  QList<QString> categories;
  categories << "Special1" << "Special2" << "Special3" << "Special4";
  
  kex::Utilities::configureApplication();
  
  kex::MetaData::instance().addCategories(categories);
  
  kex::MainWindow k;
  k.show();
  return app.exec();
}
