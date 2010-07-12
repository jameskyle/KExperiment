#include "MainWindow.h"

namespace kex
{
  MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent),
      m_components(ComponentList::globalList()),
      m_componentLibraryDock(new ComponentLibrary(this)),
      m_mapper(new QDataWidgetMapper(this)),
      m_componentModel(new ComponentModel(m_componentLibraryDock))
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
    Utilities::deleteAll(m_components);
  }
  
  void MainWindow::showLiveView()
  {
    LiveView liveView;
    
  }
  
  void MainWindow::setUpWidgetMapper()
  {
    // set up the data m_mapper for displaying
    m_mapper->setModel(m_componentModel);
    m_mapper->addMapping(componentNameLabel, 0, "text");
    m_mapper->addMapping(typeNameLabel, 1, "text");
    // TODO add label to display column 2
    m_mapper->addMapping(componentDescriptionTextEdit, 3, "plainText");
    m_mapper->addMapping(componentDurationLabel, 4, "text");
    m_mapper->addMapping(componentIcon, 5, "pixmap");

    m_mapper->toFirst();
  }
  
  void MainWindow::makeActionConnections()
  {
    // Creation Wizard
    // TODO make this configuration similar to those for the menuLibrary
    connect( actionNew, SIGNAL(triggered()),
            this, SLOT(selectComponentWizard()) );
    
    // Component Library Dock
    // Add menu items for component filters
    menuLibrary->addAction(m_componentLibraryDock->toggleActionAction());
    menuLibrary->addAction(m_componentLibraryDock->toggleEventAction());
    menuLibrary->addAction(m_componentLibraryDock->toggleTrialAction());
    menuLibrary->addAction(m_componentLibraryDock->toggleExperimentAction());
    menuLibrary->addAction(m_componentLibraryDock->toggleAllComponentsAction());
    menuLibrary->addSeparator();
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
    m_componentLibraryDock->setWindowTitle(tr("Component Library"));
    m_componentLibraryDock->setObjectName("componentLibraryDock");
    m_componentLibraryDock->setAllowedAreas(Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, m_componentLibraryDock);
    
    m_componentLibraryDock->setModel(m_componentModel);
  }
  
  void MainWindow::launchComponentLibrary(OutputComponent::ComponentTypes component)
  {
    Logger::instance().log("Launch Library called", this);

    Q_CHECK_PTR(m_componentLibraryDock);
    if (m_componentLibraryDock->isHidden())
    {
      if (!m_componentLibraryDock->isFloating())
      {
        m_componentLibraryDock->hide();
        m_componentLibraryDock->setFloating(true);
        m_componentLibraryDock->resize(QSize(200, 600));
        m_componentLibraryDock->move(QPoint(50, 50));
        m_componentLibraryDock->show();
      } else
      {
        m_componentLibraryDock->show();
      }

    } else // Not hidden
    {
      if (!m_componentLibraryDock->isFloating())
      {
        m_componentLibraryDock->hide();
        m_componentLibraryDock->setFloating(true);
        m_componentLibraryDock->show();
      } else
      {
        m_componentLibraryDock->hide();
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


