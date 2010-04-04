#ifndef CONFIGURATIONPAGE_H
#define CONFIGURATIONPAGE_H
#include <QWizardPage>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QVariant>
#include <QToolButton>
#include <QSharedPointer>

#include "Common.h"

namespace kex
{
  /** \brief  Used for additional, detailed configuration.
  * 
  * Based on choices provided in the basic BaseInformationPage, objects are 
  * further configured. For example, if the user chooses a Action of 
  * type Video, this is where they select the video and set any custom 
  * duration variables.
  * 
  * © Copyright 2010 KSpace MRI - James Kyle. All Rights Reserved.
  *
  * \author James Kyle KSpace MRI
  * \author $LastChangedBy$
  * \date 2010-04-01
  * \date $LastChangedDate$
  * \version $Rev$  \sa
  **/
  class ConfigurationPage : public QWizardPage
  {
    Q_OBJECT
    public:
      /** \brief The ConfigurationPage constructor.
      * 
      * Allocates all member objects with their default vaules.
      * 
      * \author James Kyle KSpace MRI
      * \date 2010-04-01
      * 
      * \sa BaseInformationPage CreationWizard
      **/
      ConfigurationPage(QWidget *parent = 0);
      
      /** \brief Initializes variables to values set in BaseInformationPage
      * 
      * This method is derived from QWizardPage and is called when the page
      * is loaded. We initialize all our value labels the those set by the 
      * user in the Information page
      * 
      * \author James Kyle KSpace MRI
      * \date 2010-04-01
      * 
      * \sa QWizardPage::initializePage() 
      **/
      void initializePage();
      
    private:
      /** \brief Creates the custom CreationType layout.
      * 
      * This method creates a custom section of specific layout being 
      * configured. What layout is created is determined by the user's 
      * selection in the CreationSelectionPage and the BaseInformationPage
      * 
      * \author James Kyle KSpace MRI
      * \date 2010-04-02
      * \return QLayout* pointer to the customized layout.
      * 
      * \sa CreationSelectionPage BaseInformationPage
      **/
      QLayout* createCustomLayout();
      
      QLabel nameLabel;  //!< label for the name value
      QLabel labelLabel; //!< label for the Label value
      QLabel selectionLabel; //!< label for the selection value
      
      QLabel nameValue;  //!< displays the value of the name field
      QLabel labelValue;  //!< displays the value of the label field
      QLabel selectionValue;  //!< displays the selection filed value
            
      QVBoxLayout mainLayout; //!< top level layout
      QHBoxLayout nameLayout; //!< row  layout for the name attributes
      QHBoxLayout labelLayout; //!< row layout for the label attributes
      /**
      * row layout for the selection attributes
      **/
      QHBoxLayout selectionLayout; 
      
      /**
      * The following contains a list of layouts for adding the creation
      *  type's speicific widgets according to selections on the
      *  BaseInformationPage
      **/
      QList< QSharedPointer<QLayout> > customLayoutList;
      /**
      * The following contains a list of widgets for adding the creation 
      * type's specific widgets according to selections on the 
      * BaseInformationPage
      **/
      QList< QSharedPointer<QWidget> > customWidgetList;
      
      QToolButton actionLibraryButton;  //!< library of all  actions
      QToolButton eventLibraryButton;  //!< library of all events
      QToolButton experimentLibraryButton;  //!< library of all experiments
      
    };
  }
  #endif