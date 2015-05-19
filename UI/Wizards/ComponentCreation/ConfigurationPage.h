#ifndef CONFIGURATIONPAGE
#define CONFIGURATIONPAGE
#include <QLabel>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDoubleSpinBox>
#include <QListView>
#include <QSignalMapper>

#include "Components/Event/Event.h"
#include "UI/Wizards/ComponentCreation/BaseConfigurationPage.h"
#include "UI/LiveView.h"
#include "UI/MainWindow.h"
#include "Utilities/Utilities.h"

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
    ConfigurationPage(const Component::ComponentTypes component,
                      QWidget *parent = 0);
    ~ConfigurationPage();

    void initializePage();

    QLabel         durationLabel;
    QLabel         componentListLabel;

    QListView       componentListView;

    QDoubleSpinBox durationSpinBoxMsecs;

    QHBoxLayout*   libraryToolButtonHLayout;
    QHBoxLayout     actionTypeHLayout;
    QVBoxLayout     componentListVLayout;
    QHBoxLayout     durationHLayout;

  private:
    QHBoxLayout* getLibraryButtonLayout();
    void setTitles();

    Component::ComponentTypes _component;

  signals:
    void launchComponentLibraryRequested(Component::ComponentTypes component);

  private slots:
    void dispatchLibraryRequest(const QString& libraryType);

  };

}
#endif
