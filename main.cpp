
#include <QApplication>
#include <QList>

#include <Components/ComponentFactory.h>
#include <Components/MetaData.h>
#include <Utilities/Utilities.h>
#include <Common/Global.h>
#include <QTreeView>
#include "MainWindow.h"

int main (int argc, char *argv[])
{
  QApplication app(argc, argv);


  kex::Utilities::configureApplication();

  kex::MainWindow k;
  k.show();
  return app.exec();
}
