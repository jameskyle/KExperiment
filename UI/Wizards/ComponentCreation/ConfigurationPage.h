#ifndef CONFIGURATIONPAGE
#define CONFIGURATIONPAGE
#include <QLabel>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDoubleSpinBox>
#include <QListView>
#include <QSignalMapper>

#include <Wizards/ComponentCreation/BaseConfigurationPage.h>
#include <Components/Events/Event.h>
#include <LiveView.h>
#include <MainWindow.h>
#include <Utilities/Utilities.h>

namespace kex
{
  /** \brief  Configures the Event object.
  *
  * © Copyright 2010 KSpace MRI - James Kyle. All Rights Reserved.
  *
  * \author James Kyle KSpace MRI
  * \author $LastChangedBy$
  * \date 2010-04-03
  * \date $LastChangedDate$
  * \version $Rev$  \sa CreationWizard EventInformationPage
  **/
  class ConfigurationPage : public BaseConfigurationPage
  {
    Q_OBJECT
	public:
		ConfigurationPage(QWidget *parent = 0, const Types::ComponentType component 
											= Types::UndefinedComponentType);
		~ConfigurationPage();

		void initializePage();
		
		QLabel         durationLabel;
		QLabel				 componentListLabel;

		QListView			 componentListView;
	
		QDoubleSpinBox durationSpinBoxMsecs;
		
		QHBoxLayout*	 libraryToolButtonHLayout;
		QHBoxLayout		 actionTypeHLayout;
		QVBoxLayout		 componentListVLayout;
		QHBoxLayout		 durationHLayout;
	
	private:
		QHBoxLayout* getLibraryButtonLayout();
		void setTitles();
		
		Types::ComponentType _component;
		
	signals:
		void launchComponentLibraryRequested(Types::ComponentType component);
		
	private slots:
		void dispatchLibraryRequest(const QString& libraryType);
		
	};

}
#endif
