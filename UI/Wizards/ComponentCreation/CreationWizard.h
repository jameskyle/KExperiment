#ifndef CREATIONWIZARD_H
#define CREATIONWIZARD_H

#include <QWizard>
#include <QDebug>

#include "UI/Wizards/ComponentCreation/WelcomePage.h"
#include "UI/Wizards/ComponentCreation/InformationPage.h"
#include "UI/Wizards/ComponentCreation/ConfigurationPage.h"
#include "UI/Wizards/ComponentCreation/FinishedPage.h"

#include "Components/Component.h"
#include "Common/Config.h"

namespace kex
{
  /** \brief  Creates various objects such as Actions and Trials.
  *
  * The CreationWizar walks the user through the creation of all supported
  * objects such as Actions, Events, Trials, and Experiments.
  *
  * © Copyright 2010 KSpace MRI - James Kyle. All Rights Reserved.
  *
  * \author James Kyle KSpace MRI
  * \author $LastChangedBy$
  * \date 2010-04-01
  * \date $LastChangedDate$
  * \version $Rev$  \sa
  **/
  class CreationWizard : public QWizard
  {
    Q_OBJECT
  public:
    /** \brief Instantiates a CreationWizard with default pages and page
    * configurations.
    *
    * The CreationWizard constructor configures a basic creation wizard
    * template. The wizard is futher customized through the use of the
    * various setup methods.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \param  parent Sets the parent QWidget. default = 0
    * \sa setupPages()
    **/
    CreationWizard(const Component::ComponentTypes component,
                   QWidget *parent = 0);

    ~CreationWizard() {}

    enum {
      Page_Welcome,
      Page_Information,
      Page_Configuration,
      Page_Finished,
    };
  };
}

#endif
