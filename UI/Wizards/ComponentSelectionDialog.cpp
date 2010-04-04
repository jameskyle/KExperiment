#include "ComponentSelectionDialog.h"

namespace kex
{
  ComponentSelectionDialog::ComponentSelectionDialog(QWidget *parent)
    : QDialog(parent)
  {
    setupUi(this);
    connect( this, SIGNAL(finished(int)), this, SLOT(runWizard(int)) );
  }
  
  void ComponentSelectionDialog::runWizard(int result)
  {
    if(result == QDialog::Accepted)
    {
      if(actionButton->isChecked())
      {
        CreationWizard *wizard = new CreationWizard(CreationWizard::ACTION);
        connect(wizard, SIGNAL(finished(int)), wizard, SLOT(deleteLater()));
        this->hide();
        wizard->show();
      }
      else if(eventButton->isChecked())
      {
      }
      else if(trialButton->isChecked())
      {
      }
      else if(experimentButton->isChecked())
      {
      }
    }
  }
}