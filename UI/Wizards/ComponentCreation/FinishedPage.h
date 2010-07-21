#ifndef FINISHEDPAGE_H
#define FINISHEDPAGE_H
#include <QWizardPage>
#include <QString>
#include <QVBoxLayout>
#include <QVariant>

#include "Components/Component.h"

namespace kex
{
  /** \brief  The finished page for the creation wizard.
   *
   * The Finished page is specific to the selected CreationType in the
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
  class FinishedPage : public QWizardPage
  {
    Q_OBJECT
  public:
    FinishedPage(const Component::ComponentTypes component,
                 QWidget *parent = 0);

    ~FinishedPage();
    void initializePage();

  private:
    Component::ComponentTypes _component;
  };

}
#endif
