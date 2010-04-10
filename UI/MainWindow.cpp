#include "MainWindow.h"

namespace kex
{
  MainWindow::MainWindow(QMainWindow *parent) 
		: QMainWindow(parent),
			experimentLibraryDock(0),
			actionLibraryDock(0),
			eventLibraryDock(0),
			trialLibraryDock(0)
  {		
    setupUi(this); // set up the Qt Designer Gui
		
		// Set up some defaults
		setUnifiedTitleAndToolBarOnMac(true);

		// create create and configure docks.
		createLibraryDocks();
		
    // Creation Wizard
    connect( actionNew, SIGNAL(triggered()),
      this, SLOT(selectComponentWizard()) );
  }

  MainWindow::~MainWindow()
  {
		
  }
	
	void MainWindow::showLiveView()
	{
		LiveView liveView;
		
	}
	
  void MainWindow::selectComponentWizard()
  {
    ComponentSelectionDialog *selectionDialog = 
      new ComponentSelectionDialog(this);
    connect(selectionDialog, SIGNAL(finished(int)), selectionDialog,   
						SLOT(deleteLater()));
		
    selectionDialog->show();
  }
  
  void MainWindow::log() const
  {
    qDebug() << "triggered\n";
  }
	
	void MainWindow::createLibraryDocks() 
	{
		// verify the pointers are 0, this method should only be called on startup
		Q_ASSERT(!experimentLibraryDock);
		Q_ASSERT(!actionLibraryDock);
		Q_ASSERT(!eventLibraryDock);
		Q_ASSERT(!trialLibraryDock);
		
		experimentLibraryDock = new ComponentLibrary(this);
		actionLibraryDock = new ComponentLibrary(this);
		eventLibraryDock = new ComponentLibrary(this);
		trialLibraryDock = new ComponentLibrary(this);
		
		// Assert that pointer creation was successful
		Q_CHECK_PTR(experimentLibraryDock);
		Q_CHECK_PTR(actionLibraryDock);
		Q_CHECK_PTR(eventLibraryDock);
		Q_CHECK_PTR(trialLibraryDock);
		
		// configure docks
		experimentLibraryDock->setWindowTitle(tr("Experiment Library"));
		actionLibraryDock->setWindowTitle(tr("Action Library"));
		eventLibraryDock->setWindowTitle(tr("Event Library"));
		trialLibraryDock->setWindowTitle(tr("Trial Library"));
		
		// set object names
		experimentLibraryDock->setObjectName("experimentLibraryDock");
		actionLibraryDock->setObjectName("actionLibraryDock");
		eventLibraryDock->setObjectName("eventLibraryDock");
		trialLibraryDock->setObjectName("trialLibraryDock");
		
		// declare acceptable dock points
		experimentLibraryDock->setAllowedAreas(Qt::LeftDockWidgetArea | 
																					 Qt::RightDockWidgetArea);
		actionLibraryDock->setAllowedAreas(Qt::LeftDockWidgetArea |
																			 Qt::RightDockWidgetArea);
		eventLibraryDock->setAllowedAreas(Qt::LeftDockWidgetArea |
																			 Qt::RightDockWidgetArea);
		trialLibraryDock->setAllowedAreas(Qt::LeftDockWidgetArea |
																			Qt::RightDockWidgetArea);
		
		// add docks to window
		addDockWidget(Qt::LeftDockWidgetArea, experimentLibraryDock);
		addDockWidget(Qt::RightDockWidgetArea, actionLibraryDock);
		addDockWidget(Qt::RightDockWidgetArea, eventLibraryDock);
		addDockWidget(Qt::RightDockWidgetArea, trialLibraryDock);
		
		// tabify the right docks
		tabifyDockWidget(actionLibraryDock, eventLibraryDock);
		tabifyDockWidget(actionLibraryDock, trialLibraryDock);
		
		// Add menu items for docks
		menuView->addAction(actionLibraryDock->toggleViewAction());
		menuView->addAction(eventLibraryDock->toggleViewAction());
		menuView->addAction(trialLibraryDock->toggleViewAction());
		menuView->addAction(experimentLibraryDock->toggleViewAction());
		menuView->addSeparator();
		
		// Hide the right docks by default
		actionLibraryDock->hide();
		eventLibraryDock->hide();
		trialLibraryDock->hide();
	}
	
	void MainWindow::launchComponentLibrary(Types::ComponentType component)
	{
		Logger::log("Launch Library called", this);
		ComponentLibrary *library;
		library = actionLibraryDock; // default

		switch (component)
		{
			case Types::ActionType:
				library = actionLibraryDock;
				break;
			case Types::EventType:
				library = eventLibraryDock;
				break;
			case Types::TrialType:
				library = trialLibraryDock;
				break;
			case Types::ExperimentType:
				library = experimentLibraryDock;
				break;
			default:
				Logger::log("Launch of Undefined Component Library requested", this);
			break;
		}
		Q_CHECK_PTR(library);
		if (!library->isVisible())
		{
			library->hide();
			library->setFloating(true);
			library->show();		
		} 
	}
}