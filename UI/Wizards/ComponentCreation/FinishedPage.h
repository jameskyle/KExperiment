#ifndef FINISHEDPAGE_H
#define FINISHEDPAGE_H
#include <QWizardPage>
#include <QString>
#include <QVBoxLayout>
#include <QVariant>

#include <Utilities/Utilities.h>

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
		FinishedPage(QWidget *parent = 0, const Types::ComponentType component 
								 = Types::UndefinedComponentType);
		
		~FinishedPage();
		void initializePage();
		
	private:
		Types::ComponentType _component;
	};
	
}
#endif