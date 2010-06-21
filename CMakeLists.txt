PROJECT(KExperiment)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(APPLE)
  SET(PROGNAME KExperiment)
  SET(MACOSX_BUNDLE_SHORT_VERSION_STRING 0.1)
  SET(MACOSX_BUNDLE_VERSION 0.1)
  SET(MACOSX_BUNDLE_LONG_VERSION_STRING Version 0.1)
  SET(CMAKE_OSX_ARCHITECTURES i386;x86_64)
  SET(XCODE_VERSION 3.2.1)
ENDIF(APPLE)

SET(K_MOC_HDRS
    Models/ComponentModel.h
    Components/Actions/Action.h
    Components/OutputComponent.h
    Components/Actions/RestAction.h
    Components/Actions/TextAction.h
    Components/Actions/ImageAction.h
    Components/Actions/AudioAction.h
    Components/Actions/VideoAction.h
    Components/Event/Event.h
    Components/Trial/Trial.h
    Components/Experiment/Experiment.h
    UI/Wizards/ComponentCreation/BaseConfigurationPage.h
    UI/Wizards/ComponentCreation/BaseInformationPage.h
    UI/Wizards/ComponentCreation/ComponentSelectionDialog.h
    UI/Wizards/ComponentCreation/ConfigurationPage.h
    UI/Wizards/ComponentCreation/CreationWizard.h
    UI/Wizards/ComponentCreation/FinishedPage.h
    UI/Wizards/ComponentCreation/InformationPage.h
    UI/Wizards/ComponentCreation/WelcomePage.h
    UI/ComponentLibrary.h
    UI/LiveView.h
    UI/MainWindow.h)

SET(K_UI_FILES
    UI/Forms/builderFrame.ui
    UI/Forms/ComponentSelectionDialog.ui
    UI/Forms/LibraryDockWidget.ui
    UI/Forms/MainWindow.ui
    UI/Forms/ViewerFrame.ui)

SET(K_RCS Resources/resources.qrc)

SET(KEXP_SRCS main.cpp)
SET(K_SRCS
    Common/Global.cpp
    Common/Logger.cpp
    Models/ComponentModel.cpp
    Utilities/Utilities.cpp
    Components/Actions/Action.cpp
    Components/OutputComponent.cpp
    Components/Actions/RestAction.cpp
    Components/Actions/TextAction.cpp
    Components/Actions/ImageAction.cpp
    Components/Actions/AudioAction.cpp
    Components/Actions/VideoAction.cpp
    Components/Event/Event.cpp
    Components/Trial/Trial.cpp
    Components/Experiment/Experiment.cpp
    Components/ComponentList.cpp
    Components/ComponentDomParser.cpp
    Components/ComponentFactory.cpp
    Components/MetaData.cpp
    UI/ComponentLibrary.cpp
    UI/LiveView.cpp
    UI/MainWindow.cpp
    UI/Wizards/ComponentCreation/BaseConfigurationPage.cpp
    UI/Wizards/ComponentCreation/BaseInformationPage.cpp
    UI/Wizards/ComponentCreation/ComponentSelectionDialog.cpp
    UI/Wizards/ComponentCreation/ConfigurationPage.cpp
    UI/Wizards/ComponentCreation/CreationWizard.cpp
    UI/Wizards/ComponentCreation/FinishedPage.cpp
    UI/Wizards/ComponentCreation/InformationPage.cpp
    UI/Wizards/ComponentCreation/WelcomePage.cpp)

FOREACH(file ${K_SRCS})
  STRING(REPLACE .cpp .h file_src ${file})
  SET(K_SRC_HDRS ${K_SRC_HDRS} ${file_src})
ENDFOREACH(file ${K_SRCS})
SET(K_SRC_HDRS ${K_SRC_HDRS} Components/Components.h)
ADD_DEFINITIONS(-Wall -g)

SET(QT_USE_QTXML true)
SET(QT_USE_QTXMLPATTERNS true)
SET(QT_USE_QTTEST true)

FIND_PACKAGE(Qt4 REQUIRED)

QT4_ADD_RESOURCES(K_RC_SRCS   ${K_RCS})
QT4_WRAP_CPP(     K_MOC_SRCS  ${K_MOC_HDRS})
QT4_WRAP_CPP(     CompListTest_MOC_SRCS Tests/ComponentListTest.h)
QT4_WRAP_UI(      K_UI_HDRS   ${K_UI_FILES})

INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} ../3rd .)
ADD_LIBRARY(K STATIC ${K_SRCS}
                     ${K_MOC_SRCS}
                     ${K_UI_SRCS}
                     ${K_UI_HDRS}
                     ${K_RC_SRCS}
                     ${K_SRC_HDRS})

ADD_EXECUTABLE(KExperiment MACOSX_BUNDLE ${KEXP_SRCS})
TARGET_LINK_LIBRARIES(KExperiment ${QT_LIBRARIES} K)

ADD_EXECUTABLE(ComponentListTest Tests/ComponentListTest.cpp ${CompListTest_MOC_SRCS})
TARGET_LINK_LIBRARIES(ComponentListTest ${QT_LIBRARIES} K)