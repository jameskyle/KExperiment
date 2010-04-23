#include "FinishedPage.h"

namespace kex
{
  FinishedPage::FinishedPage(QWidget *parent, const Types::ComponentType component)
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
      case Types::ActionType:
        name = tr("Action");
        break;
      case Types::EventType:
        name = tr("Event");
        break;
      case Types::TrialType:
        name = tr("Trial");
        break;
      case Types::ExperimentType:
        name = tr("Experiment");
    }
    
    setTitle(title.arg(name));
    setSubTitle(subtitle.arg(name));
    
  }
}