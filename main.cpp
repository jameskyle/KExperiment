#include <QString>
#include <QApplication>
#include <QList>

#include "Utilities/Utilities.h"
#include "UI/MainWindow.h"


int main (int argc, char *argv[])
{
  QApplication app(argc, argv);


  kex::Utilities::configureApplication();

  kex::MainWindow k;
  k.show();
  return app.exec();
}
