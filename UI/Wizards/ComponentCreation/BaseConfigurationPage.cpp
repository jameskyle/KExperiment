#include "BaseConfigurationPage.h"

namespace kex
{
  const double BaseConfigurationPage::DURATION_STEPSIZE = 0.5;

  BaseConfigurationPage::BaseConfigurationPage(QWidget *parent)
    : QWizardPage(parent),
      _nameLabel(tr("Name:")),
      _labelLabel(tr("Label:")),
      _nameValue(tr("None")),
      _labelValue(tr("None")),
      _mainLayout(this)
  {
    _mainLayout.addLayout(&_nameLayout);
    _mainLayout.addLayout(&_labelLayout);

    _nameLayout.addWidget(&_nameLabel);
    _nameLayout.addWidget(&_nameValue);

    _labelLayout.addWidget(&_labelLabel);
    _labelLayout.addWidget(&_labelValue);

    _actionLibraryButton.setText(tr("Action Library"));
    _eventLibraryButton.setText(tr("Event Library"));
    _experimentLibraryButton.setText(tr("Experiment Library"));
  }
  
  void BaseConfigurationPage::initializePage()
  {
    /*
      TODO refactor Actions and children to provide these in pure virtuals
    */
    _nameValue.setText(field("name").toString());
    _labelValue.setText(field("label").toString());
    
    // if(field("ActionCreationType").toBool())
    //  {
    //    
    //    setTitle();
    //    setSubTitle();
    //    selectionLabel.setText(tr("Action Type:"));
    //    selectionLabel.setObjectName("actionTypeLabel");
    //    selectionValue.setText(field("selection").toString());
    //    nameValue.setText(field("name").toString());
    //    labelValue.setText(field("label").toString());
    //   
    //  } else if(field("EventCreationType").toBool()) {
    //    setTitle(tr("Event Configuration"));
    //    setSubTitle(tr("Please condfigure your new Event"));
    //  
    //  } else if(field("TrialCreationType").toBool()) {
    //    setTitle(tr("Trial Information"));
    //    setSubTitle(tr("Please provide the following details about your new "
    //      "Trial."));
    //   
    //  } else if(field("ExperimentCreationType").toBool()) {
    //    setTitle(tr("Experiment Information"));
    //    setSubTitle(tr("Please provide the following details about your new "
    //      "Experiment"));
    //   
    //  }
    //   else {
    //    setTitle(tr("K_ Configuration Page"));
    //    setSubTitle("");
    //  }
  }
}