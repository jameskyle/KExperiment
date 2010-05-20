######################################################################
# Automatically generated by qmake (2.01a) Mon Apr 12 09:23:02 2010
######################################################################

TEMPLATE = app
TARGET =

# Begin Mac Options
macx {
  QMAKE_MACOSX_DEPLOYMENT_TARGET=10.6
  QMAKE_MAC_SDK=/Developer/SDKs/MacOSX10.6.sdk
  CONFIG+=x86 x86_64
#  MAKEFILE_GENERATOR = XCODE
}

# end Mac Options

QT +=  xmlpatterns
QT += xml
CONFIG += debug

DEPENDPATH += . \
              Common \
              Components \
              Resources \
              UI \
              Utilities \
              Components/Actions \
              Components/Event \
              Components/Experiment \
              Components/Trial \
              UI/Forms \
              UI/Wizards/ComponentCreation \
              UI/Wizards/ComponentCreation/Trial

INCLUDEPATH += . \
               UI \
               ../3rd

# Input
HEADERS += Common/Global.h \
           Common/Uncopyable.h \
           Common/Logger.h \
           Components/ComponentDomParser.h \
           Components/ComponentDataPrivate.h \
           Components/ComponentFactory.h \
           Components/AggregateComponent.h \
           Models/ComponentModel.h \
           Models/Action/ActionModel.h \
           Components/MetaData.h \
           UI/ComponentLibrary.h \
           UI/LiveView.h \
           UI/MainWindow.h \
           Utilities/Utilities.h \
           Components/Actions/Action.h \
           Components/OutputComponent.h \
           Components/Actions/RestAction.h \
           Components/Actions/TextAction.h \
           Components/Actions/ImageAction.h \
           Components/Actions/AudioAction.h \
           Components/Actions/VideoAction.h \
           Components/Event/Event.h \
           Components/Trial/Trial.h \
           Components/Experiment/Experiment.h \
           Components/ComponentList.h \
           UI/Wizards/ComponentCreation/BaseConfigurationPage.h \
           UI/Wizards/ComponentCreation/BaseInformationPage.h \
           UI/Wizards/ComponentCreation/ComponentSelectionDialog.h \
           UI/Wizards/ComponentCreation/ConfigurationPage.h \
           UI/Wizards/ComponentCreation/CreationWizard.h \
           UI/Wizards/ComponentCreation/FinishedPage.h \
           UI/Wizards/ComponentCreation/InformationPage.h \
           UI/Wizards/ComponentCreation/WelcomePage.h \
           UI/Wizards/ComponentCreation/Trial/TrialConfigurationPage.h
FORMS += UI/Forms/builderFrame.ui \
         UI/Forms/ComponentSelectionDialog.ui \
         UI/Forms/LibraryDockWidget.ui \
         UI/Forms/MainWindow.ui \
         UI/Forms/ViewerFrame.ui
SOURCES += main.cpp \
           Common/Global.cpp \
           Common/Logger.cpp \
           Components/ComponentDomParser.cpp \
           Components/ComponentFactory.cpp \
           Components/AggregateComponent.cpp \
           Components/MetaData.cpp \
           Models/ComponentModel.cpp \
           Models/Action/ActionModel.cpp \
           UI/ComponentLibrary.cpp \
           UI/LiveView.cpp \
           UI/MainWindow.cpp \
           Utilities/Utilities.cpp \
           Components/Actions/Action.cpp \
           Components/OutputComponent.cpp \
           Components/Actions/RestAction.cpp \
           Components/Actions/TextAction.cpp \
           Components/Actions/ImageAction.cpp \
           Components/Actions/AudioAction.cpp \
           Components/Actions/VideoAction.cpp \
           Components/Event/Event.cpp \
           Components/Trial/Trial.cpp \
           Components/Experiment/Experiment.cpp \
           Components/ComponentList.cpp \
           UI/Wizards/ComponentCreation/BaseConfigurationPage.cpp \
           UI/Wizards/ComponentCreation/BaseInformationPage.cpp \
           UI/Wizards/ComponentCreation/ComponentSelectionDialog.cpp \
           UI/Wizards/ComponentCreation/ConfigurationPage.cpp \
           UI/Wizards/ComponentCreation/CreationWizard.cpp \
           UI/Wizards/ComponentCreation/FinishedPage.cpp \
           UI/Wizards/ComponentCreation/InformationPage.cpp \
           UI/Wizards/ComponentCreation/WelcomePage.cpp \
           UI/Wizards/ComponentCreation/Trial/TrialConfigurationPage.cpp

RESOURCES += Resources/resources.qrc