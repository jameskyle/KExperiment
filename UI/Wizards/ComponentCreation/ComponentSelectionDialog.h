#ifndef COMPONENTSELECTIONDIALOG_H
#define COMPONENTSELECTIONDIALOG_H

#include "ui_ComponentSelectionDialog.h"
#include "UI/Wizards/ComponentCreation/CreationWizard.h"
#include "Utilities/Utilities.h"
#include "Common/Global.h"

namespace kex
{
  /** \brief  Dialog for selecting a component wizard.
  * 
  * © Copyright 2010 KSpace MRI - James Kyle. All Rights Reserved.
  *
  * \author James Kyle KSpace MRI
  * \author $LastChangedBy$
  * \date 2010-04-03
  * \date $LastChangedDate$
  * \version $Rev$  \sa ActionWizard
  **/
  class ComponentSelectionDialog : public QDialog, 
    private Ui::ComponentSelectionDialog
  {
    Q_OBJECT
  public:
    ComponentSelectionDialog(QWidget *parent = 0);
    ~ComponentSelectionDialog() {}
  
  private slots:
    void runWizard(int result);
  };
}
#endif