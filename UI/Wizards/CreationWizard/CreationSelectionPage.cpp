#include "CreationSelectionPage.h"

namespace kex
{
  CreationSelectionPage::CreationSelectionPage(QWidget *parent)
    : QWizardPage(parent),
      _actionButton(this),
      _eventButton(this),
      _trialButton(this),
      _experimentButton(this),
      _mainLayout(this)
    
  {
    setTitle(tr("Creation Selection"));
    setSubTitle(tr("Please choose what you would like to create."));
    
    _radioButtonLayout.addStretch();
    
    _actionButton.setText(tr("Action"));
    _radioButtonLayout.addWidget(&_actionButton);
    registerField("ActionButton", &_actionButton);
    // _actionButton.setChecked(true);
    
    _eventButton.setText(tr("Event"));
    _radioButtonLayout.addWidget(&_eventButton);
    registerField("EventButton", &_eventButton);
    
    _trialButton.setText(tr("Trial"));
    _radioButtonLayout.addWidget(&_trialButton);
    registerField("TrialButton", &_trialButton);
    
    _experimentButton.setText(tr("Experiment"));
    _radioButtonLayout.addWidget(&_experimentButton);
    registerField("ExperimentButton", &_experimentButton);
    
    _radioButtonLayout.addStretch();
    _mainLayout.addStretch();
    _mainLayout.addLayout(&_radioButtonLayout);
    _mainLayout.addStretch();
    
  }
  
  bool CreationSelectionPage::isComplete() const
  {
    bool complete = false;
    if(_actionButton.isChecked() || _eventButton.isChecked() || 
       _trialButton.isChecked()  || _experimentButton.isChecked())
    {
      complete = true;
    }

    return complete;
  }
}