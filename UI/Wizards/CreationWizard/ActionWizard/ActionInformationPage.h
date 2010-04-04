#ifndef ACTIONINFORMATIONPAGE_H
#define ACTIONINFORMATIONPAGE_H
#include "BaseInformationPage.h"

namespace kex
{
  /** \brief  Information page for the Action component type
  * 
  * © Copyright 2010 KSpace MRI - James Kyle. All Rights Reserved.
  *
  * \author James Kyle KSpace MRI
  * \author $LastChangedBy$
  * \date 2010-04-03
  * \date $LastChangedDate$
  * \version $Rev$  \sa BaseInformationPage.h
  **/
  class ActionInformationPage : public BaseInformationPage
  {
    Q_OBJECT
  public:
    /** \brief Constructor for the ActionInformationPage
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-03
    * \sa BaseInformationPage
    **/
    ActionInformationPage(QWidget *parent = 0);
    ~ActionInformationPage() {}
    
  private:
    QLabel _actionTypeLabel;  //!< the type of action to be created
    QComboBox _actionTypeComboBox;  //!< action type options
    
    QHBoxLayout _actionTypeComboBoxLayout;  //!< layout for action types
    
  };
}
#endif