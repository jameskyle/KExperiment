#include "CreationWizard.h"

namespace kex
{
  CreationWizard::CreationWizard(int component, QWidget *parent)
    : QWizard(parent)
  {
    _welcomePageId = addPage(new WelcomePage);
    // we want the combobox's text values rather than integer id's
    setDefaultProperty("QComboBox", "currentText", "currentIndexChanged");
    configureForComponent(component);
  }

  void CreationWizard::configureForComponent(const int component)
  {
    qDebug() << "configureForCreationSelection called";
    // load pages based on selected wizard type
    if(component == ACTION)
    {
      page(_welcomePage)->setTitle(tr("Welcome to the K_ Action Wizard!"));
      page(_welcomePage)->setSubTitle(tr(
        "The Action Wizard allows you to quickly and easily build custom "
        "Actions. The created actions can be used in Events, Trials, or "
        "Experiments in any order or combination."));
      setPage(Page_Information, new ActionInformationPage);
      
    } else if(EVENT) {


    } else if(TRIAL) {


    } else if(EXPERIMENT) {


    }
     else {

    }
  }
}