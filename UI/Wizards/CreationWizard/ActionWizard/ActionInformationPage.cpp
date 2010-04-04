#include "ActionInformationPage.h"

namespace kex
{
  ActionInformationPage::ActionInformationPage(QWidget *parent)
    : BaseInformationPage(parent), 
      _actionTypeLabel(this),
      _actionTypeComboBox(this)
  {
    setObjectName("ActionInformationPage");
    setTitle(tr("Action Information"));
    setSubTitle(
      tr("Please Provide the following details about your new action."));

    _actionTypeLabel.setText(tr("Action Type:"));
    _actionTypeLabel.setObjectName("actionTypeLabel");
    _actionTypeLabel.setBuddy(&_actionTypeComboBox);
    
    _actionTypeComboBox.setObjectName("actionTypeComboBox");
    // We don't add more members if the box has already been populated.
    // For example, if the user hits the back button.
    if(_actionTypeComboBox.count() == 0)
    {
      _actionTypeComboBox.addItem("Choose...");
      _actionTypeComboBox.addItems(Action::actionTypeList());
    }
    
    _actionTypeComboBoxLayout.addWidget(&_actionTypeLabel);
    _actionTypeComboBoxLayout.addWidget(&_actionTypeComboBox);
    
    
    // we want to insert the combo box layout second from last, 
    // before the description
    int position = mainLayout.count() - 1;
    mainLayout.insertLayout(position, &_actionTypeComboBoxLayout);
    
    registerField("actionType", &_actionTypeComboBox);
  }
}