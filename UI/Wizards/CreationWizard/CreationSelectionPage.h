#ifndef CREATIONSELECTIONPAGE_H
#define CREATIONSELECTIONPAGE_H

#include <QWizardPage>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "Common.h"

namespace kex
{
  /** \brief  Creates a wizard page for selecting available wizards.
  * 
  * Presents the user with a series of radio dials for selecting the type of
  * wizard they wish to initialize. For example, Action, Event, Trial, etc.
  * 
  * © Copyright 2010 KSpace MRI - James Kyle. All Rights Reserved.
  *
  * \author James Kyle KSpace MRI
  * \author $LastChangedBy$
  * \date 2010-04-01
  * \date $LastChangedDate$
  * \version $Rev$  \sa
  **/
  class CreationSelectionPage : public QWizardPage
  {
    Q_OBJECT
    public:
      /** \brief undocumented function
      * 
      *   longer description
      * 
      * \author James Kyle KSpace MRI
      * \date 2010-04-01
      * \param  parent Sets the parent for this widget. default: 0
      * \sa QWizardPage
      **/
      CreationSelectionPage(QWidget *parent = 0);
      
      bool isComplete() const;
      
    private:

      QHBoxLayout   _mainLayout;   //!< the main layout for the instance
    };
  }
  #endif