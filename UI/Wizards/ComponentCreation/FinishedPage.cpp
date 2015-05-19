#include "FinishedPage.h"

namespace kex
{
  FinishedPage::FinishedPage(const Component::ComponentTypes component,
                             QWidget *parent)
  : QWizardPage(parent),
  _component(component)
  
  {
    setLayout(new QVBoxLayout);
  }
  
  FinishedPage::~FinishedPage()
  {
    if(layout())
    {
      delete layout();
    }
  }  
  
  void FinishedPage::initializePage()
  {
    QString title = tr("New %1 Finished.");
    QString subtitle = tr("Youre new %1 has been added to the %1 Library");  
    QString name("Component");
    
    switch (_component)
    {
      case Component::ActionType:
        name = tr("Action");
        break;
      case Component::EventType:
        name = tr("Event");
        break;
      case Component::TrialType:
        name = tr("Trial");
        break;
      case Component::ExperimentType:
        name = tr("Experiment");
    }
    
    setTitle(title.arg(name));
    setSubTitle(subtitle.arg(name));
    
  }
}