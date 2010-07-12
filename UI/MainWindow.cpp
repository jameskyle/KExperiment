#include "MainWindow.h"

namespace kex
{
  MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent),
      m_components(ComponentList::globalList()),
      experimentLibraryDock(new ComponentLibrary(this)),
      actionLibraryDock(new ComponentLibrary(this)),
      eventLibraryDock(new ComponentLibrary(this)),
      trialLibraryDock(new ComponentLibrary(this)),
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
    
    Utilities::deleteAll(m_components);
  }
  
  void MainWindow::showLiveView()
  {
    LiveView liveView;
    
  }
  
  void MainWindow::setUpWidgetMapper()
  {
    // set up the data mapper for displaying
    ComponentModel *model = new ComponentModel(this);
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
    ComponentModel *model = new ComponentModel(actionLibraryDock);
    actionLibraryDock->setModel(model, OutputComponent::ActionType);

    model = new ComponentModel(eventLibraryDock);
    eventLibraryDock->setModel(model, OutputComponent::EventType);
    
    model = new ComponentModel(trialLibraryDock);
    trialLibraryDock->setModel(model, OutputComponent::TrialType);

    model = new ComponentModel(experimentLibraryDock);
    experimentLibraryDock->setModel(model, OutputComponent::ExperimentType);
    
    
    ComponentSortFilterProxyModel *proxy;
    proxy = new ComponentSortFilterProxyModel(this);
    proxy->setFilterComponentType(OutputComponent::AllComponents);
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setSourceModel(model);
    
    componentTreeView->setModel(proxy);  
    componentTreeView->setSortingEnabled(true);
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
    QStringList         xmlFiles;
    Config::ApplicationDataDirectoryTypes t;
    
    t = Config::ActionDirectory;
    xmlFiles << QStringList(Config::instance().xmlFileComponentList(t));
    
    t = Config::EventDirectory;
    xmlFiles << QStringList(Config::instance().xmlFileComponentList(t));
    
    t = Config::TrialDirectory;
    xmlFiles << QStringList(Config::instance().xmlFileComponentList(t));

    t = Config::ExperimentDirectory;
    xmlFiles << QStringList(Config::instance().xmlFileComponentList(t));

    ComponentDomParser dom;
    
    // It's important that we parse the files in order of precendence so 
    // template based components can find the original. E.g. if we parsed
    // Experiments before Actions, the Experiment class would not be able to 
    // find the Action templates.
    foreach(QString path, xmlFiles)
    {
      dom.readFile(path);
    }
    
    m_components = dom.components();
  }
} // END_KEX_NAMESPACE


