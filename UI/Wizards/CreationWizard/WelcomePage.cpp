#include "WelcomePage.h"

namespace kex
{
  void WelcomePage::initializePage()
  {
    // We must create a custom welcome page for each possible selection. If
    // new selections are added and no customization is configured, a default
    // welcome page is presented.
    
    // common setup
    if(!layout())
    {
      setLayout(new QVBoxLayout(this));
    }
    
    if(field("Action").toBool())
    {
      setTitle(kex::Action::welcomeTitle());
      setSubTitle(kex::Action::welcomeSubTitle());

    } else if(field("EventCreationType").toBool()) {
      setTitle(tr("Welcome to the K_ Event Wizard!"));
      setSubTitle(tr(
        "The Event Wizard allows you to quickly and easily build custom "
        "Events. The created events can be used in Trials, or "
        "Experiments in any order or combination."));
        
    } else if(field("TrialCreationType").toBool()) {
      setTitle(tr("Welcome to the K_ Trial Wizard!"));
      setSubTitle(tr(
      "The Trial Wizard allows you to quickly and easily build custom "
      "Trials. The created trials can be used in Experiments."));
    } else if(field("ExperimentCreationType").toBool()) {
      setTitle(tr("Welcome to the K_ Experiment Wizard!"));
      setSubTitle(tr(
      "The Experiment Wizard allwos you to quickly and easily build custom "
      "Experiments. The created experiments can be run in the K_ "
      "Experiment Manager."));
    }
     else {
      setTitle(tr("Welcome to the K_ Creation Wizard!"));
      setSubTitle(tr("This Wizard allows you to quickly and easily create "
        "K_ Objects"));
    }
  }
  
}