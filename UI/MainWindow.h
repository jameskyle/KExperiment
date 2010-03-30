#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

namespace kex
{
  class MainWindow : public QMainWindow, private Ui::MainWindow
  {
    Q_OBJECT
  public:
    MainWindow(QMainWindow *parent = 0);
  };
}
#endif