#include "CreationWizard.h"

namespace kex
{
  CreationWizard::CreationWizard(const OutputComponent::ComponentTypes component,
                                 QWidget *parent)
    : QWizard(parent)
  {
    setObjectName("CreationWizard");
    setPage(Page_Welcome, new WelcomePage(component, this));
    setPage(Page_Finished, new FinishedPage(component, this));
    setPage(Page_Information, new InformationPage(component, this));
    setPage(Page_Configuration, new ConfigurationPage(component, this));

    // we want the combobox's text values rather than integer id's
    setDefaultProperty("QComboBox", "currentText", "currentIndexChanged");
    
    
    // Connect the configuration launch library signal the wizards launch
    // library signal
    connect(page(Page_Configuration), 
            SIGNAL(launchComponentLibraryRequested(OutputComponent::ComponentTypes)), 
            parent, SLOT(launchComponentLibrary(OutputComponent::ComponentTypes)));
    
    Logger::instance().log("Initialized", this);
  }
  
}
