#include "ComponentSelectionDialog.h"

namespace kex
{
  ComponentSelectionDialog::ComponentSelectionDialog(QWidget *parent)
    : QDialog(parent)
  {
    setupUi(this);

    Q_CHECK_PTR(actionButton);
    Q_CHECK_PTR(parent);
    
    setObjectName("ComponentSelectionDialog");

    actionButton->setChecked(true);
    connect( this, SIGNAL(finished(int)), this, SLOT(runWizard(int)) );
    
    Logger::instance().log("Initialized", this);
  }
  
  void ComponentSelectionDialog::runWizard(int result)
  {
    if(result == QDialog::Accepted)
    {
      OutputComponent::ComponentTypes component;
      QWidget *parent = qobject_cast<QWidget *>(this->parent());
      
      QString choice("Undefined");
      
      if (!parent)
      {
        Logger::instance().log("Failed to upcast parent widget", this, 
                    Logger::FatalLogLevel);
      }
      
      if(actionButton->isChecked())
      {
        component = OutputComponent::ActionType;
        choice = "ActionButton";
      }
      else if(eventButton->isChecked())
      {
        component = OutputComponent::EventType;
        choice = "EventButton";
      }
      else if(trialButton->isChecked())
      {
        component = OutputComponent::TrialType;
        choice = "TrialButton";
      }
      else if(experimentButton->isChecked())
      {
        component = OutputComponent::ExperimentType;
        choice = "ExperimentButton";
      }

      
      Logger::instance().log(qPrintable(QString("%1 Selected").arg(choice)), this);
                  
      CreationWizard *wizard = new CreationWizard(component, parent);
      
      Q_CHECK_PTR(wizard);
      connect(wizard, SIGNAL(finished(int)), wizard, SLOT(deleteLater()) );

      this->hide();
      wizard->show();
    }
    
    Logger::instance().log("completed", this);
  }
}