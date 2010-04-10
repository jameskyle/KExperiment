#ifndef BASECONFIGURATIONPAGE_H
#define BASECONFIGURATIONPAGE_H
#include <QWizardPage>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QVariant>
#include <QToolButton>

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
	
  class BaseConfigurationPage : public QWizardPage
  {
    Q_OBJECT
    public:
      /** \brief The BaseConfigurationPage constructor.
      *
      * Allocates all member objects with their default vaules.
      *
      * \author James Kyle KSpace MRI
      * \date 2010-04-01
      *
      * \sa BaseInformationPage CreationWizard
      **/
      BaseConfigurationPage(QWidget *parent = 0);

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
      // void initializePage();

			void initializePage();

	protected:
		static const char DURATION_DECIMALS = 3;
    static const double DURATION_STEPSIZE = 0.5;
		
    QLabel _nameLabel;  //!< label for the name value
    QLabel _labelLabel; //!< label for the Label value

    QLabel _nameValue;  //!< displays the value of the name field
		QLabel _labelValue;  //!< displays the value of the label field
		
		QVBoxLayout _mainLayout; //!< top level layout
		QHBoxLayout _nameLayout; //!< row  layout for the name attributes
		QHBoxLayout _labelLayout; //!< row layout for the label attributes
		
		QToolButton _actionLibraryButton;  //!< library of all  actions
		QToolButton _eventLibraryButton;  //!< library of all events
		QToolButton _experimentLibraryButton;  //!< library of all experiments

    };
  }
  #endif
