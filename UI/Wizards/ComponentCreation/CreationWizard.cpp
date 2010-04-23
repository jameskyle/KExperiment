#include "CreationWizard.h"

namespace kex
{
  CreationWizard::CreationWizard(QWidget *parent, const Types::ComponentType component)
    : QWizard(parent)
  {
    setObjectName("CreationWizard");
    setPage(Page_Welcome, new WelcomePage(this, component));
    setPage(Page_Finished, new FinishedPage(this, component));
    setPage(Page_Information, new InformationPage(this, component));
    setPage(Page_Configuration, new ConfigurationPage(this, component));

    // we want the combobox's text values rather than integer id's
    setDefaultProperty("QComboBox", "currentText", "currentIndexChanged");
    
    
    // Connect the configuration launch library signal the wizards launch
    // library signal
    connect(page(Page_Configuration), 
            SIGNAL(launchComponentLibraryRequested(Types::ComponentType)), 
            parent, SLOT(launchComponentLibrary(Types::ComponentType)));
    
    Logger::instance().log("Initialized", this);
  }
  
}
