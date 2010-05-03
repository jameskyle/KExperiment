#include "InformationPage.h"

namespace kex
{
  InformationPage::InformationPage(QWidget *parent, 
                                   const Types::ComponentType component) 
  : BaseInformationPage(parent),
    _component(component),
    _actionTypeComboBoxHLayout(0)
  {
  }
  
  InformationPage::~InformationPage() 
  {
    if (_actionTypeComboBoxHLayout)
    {
      delete _actionTypeComboBoxHLayout;
    }
  }

  void InformationPage::initializePage()
  {
    BaseInformationPage::initializePage();
    QStringList actionTypes;
    QString name("Component");
    // We set up some variables for inserting a combo box in case of an ACTION
    // component
    int extraLayoutPosition = _mainLayout.count() - 1;
    QComboBox *actionTypeComboBox;
    QLabel *actionTypeLabel;
    
    switch (_component)
    {
      case Types::ActionType:
        name = "Action";
        _actionTypeComboBoxHLayout = new QHBoxLayout;
        actionTypeComboBox = new QComboBox(this);
        actionTypeLabel = new QLabel(tr("Action Type:"), this);
        
        actionTypeComboBox->setObjectName("actionTypeComboBox");
        actionTypeLabel->setObjectName("actionTypeLabel");
        actionTypeLabel->setBuddy(actionTypeComboBox);
        
        actionTypeComboBox->addItem(tr("Choose..."));
         actionTypes = Action::actionTypeList();
        actionTypeComboBox->addItems(actionTypes);
        
        _mainLayout.insertLayout(extraLayoutPosition, 
                                 _actionTypeComboBoxHLayout);
        _actionTypeComboBoxHLayout->addWidget(actionTypeLabel);
        _actionTypeComboBoxHLayout->addWidget(actionTypeComboBox);
        
        registerField("action", actionTypeComboBox);
        break;
      case Types::EventType:
        name = "Event";
        break;
      case Types::TrialType:
        name = "Trial";
        break;
      case Types::ExperimentType:
        name = "Experiment";
        break;        
    }

    setObjectName(QString("%1InformationPage").arg(name));
    setTitle(tr("%1 Information").arg(name));
    setSubTitle(tr("Please enter the information for your new %1").arg(name));
  }
}