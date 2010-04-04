#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QObjectCleanupHandler>

#include "Common.h"
#include "ui_MainWindow.h"
#include "CreationWizard.h"
#include "ComponentSelectionDialog.h"

namespace kex
{
  class MainWindow : public QMainWindow, private Ui::MainWindow
  {
    Q_OBJECT
  public:
    MainWindow(QMainWindow *parent = 0);
    ~MainWindow();
    
  public slots:
    void selectComponentWizard();
    void log() const;
  };
}
#endif