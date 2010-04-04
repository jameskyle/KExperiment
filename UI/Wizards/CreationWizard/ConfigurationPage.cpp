#include "ConfigurationPage.h"

namespace kex
{
  ConfigurationPage::ConfigurationPage(QWidget *parent)
    : QWizardPage(parent),
      nameLabel(tr("Name:")),
      labelLabel(tr("Label:")),
      selectionLabel(tr("Selection:")),
      nameValue(tr("None")),
      labelValue(tr("None")),
      selectionValue(tr("None")),
      mainLayout(this)
  {
    mainLayout.addLayout(&nameLayout);
    mainLayout.addLayout(&labelLayout);
    mainLayout.addLayout(&selectionLayout);
    
    nameLayout.addWidget(&nameLabel);
    nameLayout.addWidget(&nameValue);
    
    labelLayout.addWidget(&labelLabel);
    labelLayout.addWidget(&labelValue);
    
    selectionLayout.addWidget(&selectionLabel);
    selectionLayout.addWidget(&selectionValue);
    
    actionLibraryButton.setText(tr("Action Library"));
    eventLibraryButton.setText(tr("Event Library"));
    experimentLibraryButton.setText(tr("Experiment Library"));
  }
  
  void ConfigurationPage::initializePage()
  {
    /*
      TODO refactor Actions and children to provide these in pure virtuals
    */
    if(field("ActionCreationType").toBool())
    {
      
      setTitle(tr("Action Configuration"));
      setSubTitle(tr("Please configure your new action."));
      selectionLabel.setText(tr("Action Type:"));
      selectionLabel.setObjectName("actionTypeLabel");
      selectionValue.setText(field("selection").toString());
      nameValue.setText(field("name").toString());
      labelValue.setText(field("label").toString());

    } else if(field("EventCreationType").toBool()) {
      setTitle(tr("Event Configuration"));
      setSubTitle(tr("Please condfigure your new Event"));
    
    } else if(field("TrialCreationType").toBool()) {
      setTitle(tr("Trial Information"));
      setSubTitle(tr("Please provide the following details about your new "
        "Trial."));

    } else if(field("ExperimentCreationType").toBool()) {
      setTitle(tr("Experiment Information"));
      setSubTitle(tr("Please provide the following details about your new "
        "Experiment"));

    }
     else {
      setTitle(tr("K_ Configuration Page"));
      setSubTitle("");
    }
  }
  
  QLayout* ConfigurationPage::createCustomLayout()
  {
 
  }
}