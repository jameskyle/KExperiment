#ifndef INFORMATIONPAGE_H
#define INFORMATIONPAGE_H
#include <QLabel>
#include <QHBoxLayout>

#include <UI/Wizards/ComponentCreation/BaseInformationPage.h>

namespace kex
{
  /** \brief  Customized information page per specified Component
   * 
   * Copyright 2010 KSpace MRI. All Rights Reserved.
   *
   * \author James Kyle
   * \author $LastChangedBy$
   * \date 2010-4-8
   * \date $LastChangedDate$
   * \version $Rev$  \sa BaseInformationPage
   **/
   class InformationPage : public BaseInformationPage
   {
     Q_OBJECT
   public:
     /** \brief  Default constructor
      * 
      * Copyright 2010 KSpace MRI. All Rights Reserved.
      *
      * \author James Kyle
      * \author $LastChangedBy$
      * \date 2010-4-8
      * \date $LastChangedDate$
      * \param parent the QWidget parent
      * \prarm component the specific component to configure page by
      *  \version $Rev$  \sa BaseConfigurationPage()
      **/
     InformationPage(QWidget *parent, const Types::ComponentType component 
                     = Types::UndefinedComponentType);
     ~InformationPage();
      
     void initializePage();
     
   private:
     int _component;
     QHBoxLayout *_actionTypeComboBoxHLayout;

   };

}
#endif