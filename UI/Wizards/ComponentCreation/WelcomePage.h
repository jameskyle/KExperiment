#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H
#include <QWizardPage>
#include <QString>
#include <QVBoxLayout>
#include <QVariant>
#include <Utilities/Utilities.h>

namespace kex
{
  /** \brief  The welcome page for the creation wizard.
  * 
  * The Welcome page is specific to the selected CreationType in the 
  * CreationSelectionPage instance.
  * 
  * © Copyright 2010 KSpace MRI - James Kyle. All Rights Reserved.
  *
  * \author James Kyle KSpace MRI
  * \author $LastChangedBy$
  * \date 2010-04-01
  * \date $LastChangedDate$
  * \version $Rev$  \sa CreationWizard CreationSelectionPage
  **/
  class WelcomePage : public QWizardPage
  {
    Q_OBJECT
  public:
    WelcomePage(const ComponentInterface::ComponentType component,
                QWidget *parent = 0);
    
    ~WelcomePage();
    void initializePage();
    
  private:
    ComponentInterface::ComponentType _component;
  };
    
}
  #endif