#include "InformationPage.h"

namespace kex
{
  InformationPage::InformationPage(const OutputComponent::ComponentTypes component,
                                   QWidget *parent) 
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
      case OutputComponent::ActionType:
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
      case OutputComponent::EventType:
        name = "Event";
        break;
      case OutputComponent::TrialType:
        name = "Trial";
        break;
      case OutputComponent::ExperimentType:
        name = "Experiment";
        break;        
    }

    setObjectName(QString("%1InformationPage").arg(name));
    setTitle(tr("%1 Information").arg(name));
    setSubTitle(tr("Please enter the information for your new %1").arg(name));
  }
}