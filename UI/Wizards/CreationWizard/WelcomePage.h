#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H
#include <QWizardPage>
#include <QVBoxLayout>
#include <QVariant>

#include "Common.h"

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
      WelcomePage(QWidget *parent = 0) : QWizardPage(parent) {}
      
      /** \brief Initializes the page according to a CreationType
      *
      * The CreationType is selected in a previous CreationSelectionPage and 
      * set as a field according to its name (e.g. ActionCreationType). 
      * Depending on selection, a custom welcome page is generated.
      * 
      * \author James Kyle KSpace MRI
      * \date 2010-04-01
      * \sa QWizardPage
      **/
      void initializePage();
    };
    
  }
  #endif