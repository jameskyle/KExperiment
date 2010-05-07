#include "MainWindow.h"

namespace kex
{
  MainWindow::MainWindow(QMainWindow *parent) 
    : QMainWindow(parent),
      experimentLibraryDock(new ComponentLibrary(this)),
      actionLibraryDock(new ComponentLibrary(this)),
      eventLibraryDock(new ComponentLibrary(this)),
      trialLibraryDock(new ComponentLibrary(this)),
      componentList(new ComponentList)
  {    
    setupUi(this); // set up the Qt Designer Gui
    
    // Set up some defaults
    setUnifiedTitleAndToolBarOnMac(true);
    
    // read in xml templates and cache objects in list
    populateComponentList();
    
    // create create and configure docks.
    createLibraryDocks();
    
    // Creation Wizard
    connect( actionNew, SIGNAL(triggered()),
      this, SLOT(selectComponentWizard()) );
  }

  MainWindow::~MainWindow()
  {
    if (componentList)
    {
      qDeleteAll(componentList->begin(), componentList->end());
      delete componentList;
    }
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
    
    // Set models for created libraries
    ComponentModel *model = new ComponentModel(Config::ActionDirectory, 
                                               actionLibraryDock);
    actionLibraryDock->setModel(model);

    model = new ComponentModel(Config::EventDirectory, eventLibraryDock);
    eventLibraryDock->setModel(model);
    
    model = new ComponentModel(Config::TrialDirectory, trialLibraryDock);
    trialLibraryDock->setModel(model);
    
    model = new ComponentModel(Config::ExperimentDirectory, 
                               experimentLibraryDock);
    experimentLibraryDock->setModel(model);
  }
  
  void MainWindow::launchComponentLibrary(Types::ComponentType component)
  {
    Logger::instance().log("Launch Library called", this);
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
        Logger::instance().log("Launch of Undefined Component Library requested", this);
      break;
    }
    Q_CHECK_PTR(library);
    if (library->isHidden())
    {
      if (!library->isFloating())
      {
        library->hide();
        library->setFloating(true);
        library->resize(QSize(200, 600));
        library->move(QPoint(50, 50));
        library->show();
      } else
      {
        library->show();
      }

    } else // Not hidden
    {
      if (!library->isFloating())
      {
        library->hide();
        library->setFloating(true);
        library->show();
      } else
      {
        library->hide();
      }

    }

  }
  
  void MainWindow::populateComponentList()
  {
    ComponentFactory    *factory = &ComponentFactory::instance();
    ComponentInterface  *interface(0);
    QStringList         xmlFiles(Utilities::xmlFileComponentList());
    
    foreach(QString path, xmlFiles)
    {
      QFile file(path);
      interface = factory->createFromXml(file);
    }
  }
} // END_KEX_NAMESPACE


