#include "MainWindow.h"

namespace kex
{
  MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent)
  {
    setupUi(this); // set up the Qt Designer Gui
        
    // Creation Wizard
    connect( this->actionNew, SIGNAL(triggered()),
      this, SLOT(selectComponentWizard()) );

  }

  MainWindow::~MainWindow()
  {
  }

  void MainWindow::selectComponentWizard()
  {
    ComponentSelectionDialog *selectionDialog = 
      new ComponentSelectionDialog(this);
    connect( selectionDialog, SIGNAL(finished(int)), selectionDialog,   
      SLOT(deleteLater()) );
    selectionDialog->show();
  }
  
  void MainWindow::log() const
  {
    qDebug() << "object deleted\n";
  }
}