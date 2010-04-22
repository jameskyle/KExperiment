#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QObjectCleanupHandler>
#include <QDebug>

#include <Wizards/ComponentCreation/CreationWizard.h>
#include <Wizards/ComponentCreation/ComponentSelectionDialog.h>
#include <ComponentLibrary.h>
#include <LiveView.h>
#include <Models/ComponentModel.h>

#include "ui_MainWindow.h"

namespace kex
{
  class MainWindow : public QMainWindow, private Ui::MainWindow
  {
    Q_OBJECT
  public:
    MainWindow(QMainWindow *parent = 0);
    ~MainWindow();
		
		/** \brief  Connects the button to the provided component type library
		 * 
		 * Copyright 2010 KSpace MRI. All Rights Reserved.
		 * 
		 * \author James Kyle
		 * \author $LastChangedBy$
		 * \date 2010-4-7
		 * \date $LastChangedDate$
		 * \param button the button to connect to the librariy dock's toggle event
		 * \prarm component the type of component requested
		* \version $Rev$
		**/
		//void connectButtonToLibraryDock(QToolButton *button, );


	
	private:
		/** \brief  Creates an Experiment Library dock widget
		 * 
		 * Copyright 2010 KSpace MRI. All Rights Reserved.
		 *
		 * Returns a ComponentLibraryDockWidget configured for the Expeirment class
		 * 
		 * \author James Kyle
		 * \author $LastChangedBy$
		 * \date 2010-4-7
		 * \date $LastChangedDate$
		* \version $Rev$  \sa ComponentLibraryDockWidget
		**/
		void createLibraryDocks();
		
		
		ComponentLibrary *experimentLibraryDock;
		ComponentLibrary *actionLibraryDock;
		ComponentLibrary *eventLibraryDock;
		ComponentLibrary *trialLibraryDock;
		
  public slots:
    void selectComponentWizard();
		void launchComponentLibrary(Types::ComponentType component);
		
		void showLiveView();
    void log() const;
  };
}

#endif