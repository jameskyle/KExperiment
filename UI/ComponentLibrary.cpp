#include "ComponentLibrary.h"
#include <QTimer>

namespace kex
{
  ComponentLibrary::ComponentLibrary(QWidget *parent)
  : QDockWidget(parent),
  m_toggleActionAction(new QAction(tr("&Actions..."), this)),
  m_toggleEventAction(new QAction(tr("&Events..."), this)),
  m_toggleTrialAction(new QAction(tr("&Trials..."), this)),
  m_toggleExperimentAction(new QAction(tr("E&xperiments..."), this)),
  m_toggleAllComponentsAction(new QAction(tr("A&ll..."), this))
  {
    setupUi(this);
    componentListView->setGridSize(QSize(-1,-1));
    componentListView->setIconSize(QSize(32,32));
    
    m_toggleActionAction->setCheckable(true);
    connect(m_toggleActionAction, SIGNAL(toggled(bool)),
            this, SLOT(toggleActions(bool)));
    
    m_toggleEventAction->setCheckable(true);
    connect(m_toggleEventAction, SIGNAL(toggled(bool)),
            this, SLOT(toggleEvents(bool)));
    
    m_toggleTrialAction->setCheckable(true);
    connect(m_toggleTrialAction, SIGNAL(toggled(bool)),
            this, SLOT(toggleTrials(bool)));
    
    m_toggleExperimentAction->setCheckable(true);
    connect(m_toggleExperimentAction, SIGNAL(toggled(bool)),
            this, SLOT(toggleExperiments(bool)));
    
    m_toggleAllComponentsAction->setCheckable(true);

    connect(m_toggleAllComponentsAction, SIGNAL(triggered(bool)), 
            m_toggleActionAction, SLOT(setChecked(bool)));
    connect(m_toggleAllComponentsAction, SIGNAL(triggered(bool)), 
            m_toggleEventAction, SLOT(setChecked(bool)));
    connect(m_toggleAllComponentsAction, SIGNAL(triggered(bool)), 
            m_toggleTrialAction, SLOT(setChecked(bool)));
    connect(m_toggleAllComponentsAction, SIGNAL(triggered(bool)), 
            m_toggleExperimentAction, SLOT(setChecked(bool)));
    
    m_toggleAllComponentsAction->trigger();
    
    // when a component is clicked, emit the selectedIndexChanged signal
    connect(componentListView, SIGNAL(clicked(const QModelIndex&)), 
            this, SIGNAL(selectedIndexChanged(const QModelIndex&)));
  }

  ComponentLibrary::~ComponentLibrary() {
  }

  void ComponentLibrary::setModel(ComponentModel *model)
  {
    ComponentSortFilterProxyModel *proxy;
    proxy = new ComponentSortFilterProxyModel(this);
    Q_CHECK_PTR(proxy);
    
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setSourceModel(model);
    proxy->setFilterComponentType(OutputComponent::AllComponents);

    componentListView->setModel(proxy);

    connect(filterLineEdit, SIGNAL(textChanged(QString)),
            proxy,   SLOT(setFilterFixedString(QString)));
  }
  
  void ComponentLibrary::toggleActions(bool checked)
  {
    Q_CHECK_PTR(m_toggleActionAction);
    
    toggleComponentFilter(checked, OutputComponent::ActionType);
  }
  
  void ComponentLibrary::toggleEvents(bool checked)
  {
    Q_CHECK_PTR(m_toggleEventAction);
    
    toggleComponentFilter(checked, OutputComponent::EventType);
  }
  
  void ComponentLibrary::toggleTrials(bool checked)
  {
    Q_CHECK_PTR(m_toggleTrialAction);
    
    toggleComponentFilter(checked, OutputComponent::TrialType);
  }
  
  void ComponentLibrary::toggleExperiments(bool checked)
  {
    Q_CHECK_PTR(m_toggleExperimentAction);
    
    toggleComponentFilter(checked, OutputComponent::ExperimentType);
  }
  
  void ComponentLibrary::toggleComponentFilter(
                          bool checked, 
                          OutputComponent::ComponentTypes t)
  {
    ComponentSortFilterProxyModel *model;
    
    model = qobject_cast<ComponentSortFilterProxyModel *>(componentListView->model());
      
    if (model)
    {
      OutputComponent::ComponentTypes current_types(model->filterComponentType());
      
      if (checked)
      {
        model->setFilterComponentType((t | current_types));
      } else
      {
        model->setFilterComponentType((~t & current_types));
      }
    }
    udpateAllComponentsAction();
  }
  
  void ComponentLibrary::udpateAllComponentsAction()
  {
    Q_CHECK_PTR(m_toggleAllComponentsAction);
    Q_CHECK_PTR(m_toggleActionAction);
    Q_CHECK_PTR(m_toggleEventAction);
    Q_CHECK_PTR(m_toggleTrialAction);
    Q_CHECK_PTR(m_toggleExperimentAction);
    
    if (m_toggleActionAction->isChecked()  && 
        m_toggleEventAction->isChecked()   &&
        m_toggleTrialAction->isChecked()   &&
        m_toggleExperimentAction->isChecked())
    {
      m_toggleAllComponentsAction->setChecked(true);
      
    } else
    {
      m_toggleAllComponentsAction->setChecked(false);

    }
  }

}
