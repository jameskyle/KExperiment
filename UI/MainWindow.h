#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QObjectCleanupHandler>
#include <QDebug>
#include <QXmlStreamReader>
#include <QXmlSchemaValidator>
#include <QXmlSchema>
#include <QDir>
#include <QStringList>
#include <QDataWidgetMapper>

#include "Wizards/ComponentCreation/CreationWizard.h"
#include "Wizards/ComponentCreation/ComponentSelectionDialog.h"

#include "Components/ComponentList.h"
#include "Components/ComponentDomParser.h"

#include "ComponentLibrary.h"
#include "LiveView.h"

#include "Models/ComponentModel.h"
#include "Utilities/Utilities.h"
#include "Common/Global.h"

#include "ui_MainWindow.h"

namespace kex
{
  class MainWindow : public QMainWindow, private Ui::MainWindow
  {
    Q_OBJECT
  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /** \brief  Connects the button to the provided component type library
     *
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-4-7
     * \date $LastChangedDate$
     * \param button the button to connect to the librariy dock's toggle event
     * \prarm component the type of component requested
    * \version $Rev$
    **/
    //void connectButtonToLibraryDock(QToolButton *button, );



  private:
    /** \brief  Creates an Experiment Library dock widget
     *
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * Returns a ComponentLibraryDockWidget configured for the Expeirment class
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-4-7
     * \date $LastChangedDate$
    * \version $Rev$  \sa ComponentLibraryDockWidget
    **/
    void createLibraryDocks();

    /** \brief  Populates the componentList from the xml component files.
     *
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * Checked the DataDirectory/{actions,events,trials,experiments}
     * directories for template files and creates the relevant qobjects.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-5-2
     * \date $LastChangedDate$
     * \version $Rev$  \sa OutputComponent ComponentList
     **/
    void populateComponentList();

    void setUpWidgetMapper();

    void makeActionConnections();

    ComponentLibrary *experimentLibraryDock;
    ComponentLibrary *actionLibraryDock;
    ComponentLibrary *eventLibraryDock;
    ComponentLibrary *trialLibraryDock;
    ComponentList    *componentList;
    QDataWidgetMapper *mapper;

  public slots:
    void selectComponentWizard();
    void launchComponentLibrary(OutputComponent::ComponentTypes component);

    void showLiveView();
  };
}

#endif
