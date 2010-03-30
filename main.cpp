#include <QApplication>
#include <QMainWindow>

#include "MainWindow.h"

int main (int argc, char *argv[])
{
  QApplication app(argc, argv);
  
  kex::MainWindow k;
  
  k.show();
  return app.exec();
}
