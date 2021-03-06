#include "WelcomePage.h"

namespace kex
{
  WelcomePage::WelcomePage(const Component::ComponentTypes component,
                           QWidget *parent)
  : QWizardPage(parent),
    _component(component)
  
  {
    setLayout(new QVBoxLayout);
  }
  
  WelcomePage::~WelcomePage()
  {
    if(layout())
    {
      delete layout();
    }
  }  
  
  void WelcomePage::initializePage()
  {
    QString title = tr("Welcome to the K_ %1 Wizard!");
    QString subtitle = tr("The %1 Wizard allows you to quickly and easily "
                          "build custom %1s. They will also be "
                          "available in the %1 Library");
    
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
      default:
        name = tr("Undefined Component Type");
        Logger::instance().log("Undefined Component!", this, 
                    Logger::CriticalLogLevel);
        break;
    }
    
    setTitle(title.arg(name));
    setSubTitle(subtitle.arg(name));
    
  }
}