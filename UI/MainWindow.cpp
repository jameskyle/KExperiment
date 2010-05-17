#include "MainWindow.h"

namespace kex
{
  MainWindow::MainWindow(QMainWindow *parent) 
    : QMainWindow(parent),
      experimentLibraryDock(new ComponentLibrary(this)),
      actionLibraryDock(new ComponentLibrary(this)),
      eventLibraryDock(new ComponentLibrary(this)),
      trialLibraryDock(new ComponentLibrary(this)),
      componentList(&ComponentList::instance()),
      mapper(new QDataWidgetMapper)
  {    
    setupUi(this); // set up the Qt Designer Gui
    
    // Set up some defaults
    setUnifiedTitleAndToolBarOnMac(true);
    
    // read in xml templates and cache objects in list
    populateComponentList();
    
    // create create and configure docks.
    createLibraryDocks();
    
    setUpWidgetMapper();
    
    makeActionConnections();
  }

  MainWindow::~MainWindow()
  {
    if (mapper)
    {
      delete mapper;
    }
  }
  
  void MainWindow::showLiveView()
  {
    LiveView liveView;
    
  }
  
  void MainWindow::setUpWidgetMapper()
  {
    // set up the data mapper for displaying
    ComponentModel *model = new ComponentModel(OutputComponent::AllComponents, 
                                               this);
    mapper->setModel(model);
    mapper->addMapping(componentNameLabel, 0, "text");
    mapper->addMapping(typeNameLabel, 1, "text");
    // TODO add label to display column 2
    mapper->addMapping(componentDescriptionTextEdit, 3, "plainText");
    mapper->addMapping(componentDurationLabel, 4, "text");
    mapper->addMapping(componentIcon, 5, "pixmap");

    mapper->toFirst();
  }
  
  void MainWindow::makeActionConnections()
  {
    // Creation Wizard
    // TODO make this configuration similar to those for the menuView
    connect( actionNew, SIGNAL(triggered()),
            this, SLOT(selectComponentWizard()) );
    
    // Library Docks
    // Add menu items for docks
    menuView->addAction(actionLibraryDock->toggleViewAction());
    menuView->addAction(eventLibraryDock->toggleViewAction());
    menuView->addAction(trialLibraryDock->toggleViewAction());
    menuView->addAction(experimentLibraryDock->toggleViewAction());
    menuView->addSeparator();
  }

  void MainWindow::selectComponentWizard()
  {
    ComponentSelectionDialog *selectionDialog = 
      new ComponentSelectionDialog(this);
    connect(selectionDialog, SIGNAL(finished(int)), selectionDialog,   
            SLOT(deleteLater()));
    
    selectionDialog->show();
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
    
    // Hide the right docks by default
    actionLibraryDock->hide();
    eventLibraryDock->hide();
    trialLibraryDock->hide();
    experimentLibraryDock->hide();
    
    // Set models for created libraries
   ComponentModel *model = new ComponentModel(OutputComponent::ActionType, 
                                               actionLibraryDock);
   actionLibraryDock->setModel(model);

   model = new ComponentModel(OutputComponent::EventType, eventLibraryDock);
   eventLibraryDock->setModel(model);
    
   model = new ComponentModel(OutputComponent::TrialType, trialLibraryDock);
   trialLibraryDock->setModel(model);
    
  model = new ComponentModel(OutputComponent::AllComponents, 
                               experimentLibraryDock);
  experimentLibraryDock->setModel(model);
  }
  
  void MainWindow::launchComponentLibrary(OutputComponent::ComponentTypes component)
  {
    Logger::instance().log("Launch Library called", this);
    ComponentLibrary *library;
    library = actionLibraryDock; // default

    switch (component)
    {
      case OutputComponent::ActionType:
        library = actionLibraryDock;
        break;
      case OutputComponent::EventType:
        library = eventLibraryDock;
        break;
      case OutputComponent::TrialType:
        library = trialLibraryDock;
        break;
      case OutputComponent::ExperimentType:
        library = experimentLibraryDock;
        break;
      default:
        Logger::instance().log("Launch of Undefined Component "
                               "Library requested", this);
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
    QStringList         xmlFiles(Utilities::xmlFileComponentList());
    ComponentDomParser dom;
    
    foreach(QString path, xmlFiles)
    {
      dom.readFile(path);
      OutputComponent *comp = dom.component();
      // if the component did not specify a name, we set it to the expanded
      // file name
      QString name = comp->name();
      if (name.isEmpty())
      {
        QFileInfo info(path);
        name = Utilities::componentNameFromBaseName(info.baseName());
        comp->setName(name);
      }
      
      // Add the component to our global component list
      componentList->append(comp);
      foreach(OutputComponent *p, comp->childComponents())
      {
        qDebug() << "root name: " << p->name() << "children: " << 
        p->children().count();
        foreach(OutputComponent *pp, p->childComponents())
        {
          qDebug() << "first child name: " << pp->name() << "children: " << 
          pp->children().count();
          
          foreach(OutputComponent *ppp, pp->childComponents())
          {
            qDebug() << "first child name: " << ppp->name() << "children: " << 
            ppp->children().count();
            
          }
          
        }
      }
    }
  }
} // END_KEX_NAMESPACE


