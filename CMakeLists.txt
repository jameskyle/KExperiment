PROJECT(KExperiment)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(APPLE)
  SET(PROGNAME KExperiment)
  SET(MACOSX_BUNDLE_SHORT_VERSION_STRING 0.1)
  SET(MACOSX_BUNDLE_VERSION 0.1)
  SET(MACOSX_BUNDLE_LONG_VERSION_STRING Version 0.1)
  SET(CMAKE_OSX_ARCHITECTURES x86_64)
  SET(XCODE_VERSION 3.2.1)
  SET(GCC_VERSION llvm)
  SET(DEBUG_INFORMATION_FORMAT dwarf-with-dsym)
  SET(ONLY_ACTIVE_ARCH YES)
  SET(CURRENT_PROJECT_VERSION .01)
  SET(GCC_ENABLE_FIX_AND_CONTINUE YES)
ENDIF(APPLE)

SET(TEMPLATE_FILE ${CMAKE_SOURCE_DIR}/Tests/components.yml)
SET(TEMPLATE_OUTFILE ${CMAKE_CURRENT_BINARY_DIR}/ComponentTemplates.h)
SET(TEMPLATE_SCRIPT ${CMAKE_SOURCE_DIR}/Scripts/create_components.py)
ADD_CUSTOM_COMMAND(
  OUTPUT ${TEMPLATE_OUTFILE}
  COMMAND ${TEMPLATE_SCRIPT} ${TEMPLATE_FILE} ${TEMPLATE_OUTFILE}
)

SET(TASK_FILE "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.tasks")
SET(TASK_SCRIPT ${CMAKE_SOURCE_DIR}/Scripts/create_task_list.py)
ADD_CUSTOM_COMMAND(
  OUTPUT ${TASK_FILE}
  COMMAND  ${TASK_SCRIPT} ${CMAKE_SOURCE_DIR} ${TASK_FILE}
)

ADD_CUSTOM_TARGET(generate DEPENDS ${TEMPLATE_OUTFILE})
ADD_CUSTOM_TARGET(tasks DEPENDS ${TASK_FILE})

IF("${CMAKE_GENERATOR}" MATCHES "Make")
  ADD_CUSTOM_TARGET(clean_generated
    COMMAND /bin/rm -f ${TEMPLATE_OUTFILE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  )
  ADD_CUSTOM_TARGET(clean_tasks
    COMMAND /bin/rm -f ${TASK_FILE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  )
ENDIF("${CMAKE_GENERATOR}" MATCHES "Make")


SET(K_MOC_HDRS
    Models/ComponentModel.h
    Components/Component.h
    Components/ComponentCollection.h
    Components/Actions/RestAction.h
    Components/Actions/TextAction.h
    Components/Actions/ImageAction.h
    Components/Actions/MediaAction.h
    Components/Event/Event.h
    Components/Trial/Trial.h
    Components/Experiment/Experiment.h
    Models/ComponentSortFilterProxyModel.h
    UI/Wizards/ComponentCreation/BaseConfigurationPage.h
    UI/Wizards/ComponentCreation/BaseInformationPage.h
    UI/Wizards/ComponentCreation/ComponentSelectionDialog.h
    UI/Wizards/ComponentCreation/ConfigurationPage.h
    UI/Wizards/ComponentCreation/CreationWizard.h
    UI/Wizards/ComponentCreation/FinishedPage.h
    UI/Wizards/ComponentCreation/InformationPage.h
    UI/Wizards/ComponentCreation/WelcomePage.h
    UI/ComponentLibrary.h
    UI/ComponentGraphicsItem.h
    UI/LiveView.h
    UI/MainWindow.h)

SET(K_UI_FILES
    UI/Forms/builderFrame.ui
    UI/Forms/ComponentSelectionDialog.ui
    UI/Forms/LibraryDockWidget.ui
    UI/Forms/MainWindow.ui
    UI/Forms/ViewerFrame.ui)

SET(KEXP_SRCS main.cpp)
SET(K_SRCS
    Common/Config.cpp
    Common/Logger.cpp
    Models/ComponentModel.cpp
    Utilities/Utilities.cpp
    Components/Component.cpp
    Components/ComponentCollection.cpp
    Components/ComponentExceptions.cpp
    Components/Actions/RestAction.cpp
    Components/Actions/TextAction.cpp
    Components/Actions/ImageAction.cpp
    Components/Actions/MediaAction.cpp
    Components/Event/Event.cpp
    Components/Trial/Trial.cpp
    Components/Experiment/Experiment.cpp
    Components/ComponentList.cpp
    Components/ComponentDomParser.cpp
    Components/ComponentDomParser.cpp
    Components/ComponentFactory.cpp
    Components/MetaData.cpp
    Models/ComponentSortFilterProxyModel.cpp
    UI/ComponentLibrary.cpp
    UI/ComponentGraphicsItem.cpp
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

SET(K_RCS Resources/resources.qrc)

FOREACH(file ${K_SRCS})
  STRING(REPLACE .cpp .h file_src ${file})
  SET(K_SRC_HDRS ${K_SRC_HDRS} ${file_src})
ENDFOREACH(file ${K_SRCS})

SET(K_SRC_HDRS ${K_SRC_HDRS} Components/Components.h )
SET(CMAKE_C_FLAGS_DEBUG "-Wall -ggdb")
SET(CMAKE_CXX_FLAGS_DEBUG "-Wall -ggdb")

SET(QT_USE_QTXML true)
SET(QT_USE_QTXMLPATTERNS true)
SET(QT_USE_QTTEST true)
SET(QT_USE_PHONON true)
FIND_PACKAGE(Qt4 REQUIRED)

QT4_ADD_RESOURCES(K_RC_SRCS   ${K_RCS})
QT4_WRAP_CPP(     K_MOC_SRCS  ${K_MOC_HDRS})


QT4_WRAP_UI(      K_UI_HDRS   ${K_UI_FILES})

INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} ../3rd .)
ADD_LIBRARY(K STATIC ${K_SRCS}
                     ${K_MOC_SRCS}
                     ${K_UI_SRCS}
                     ${K_UI_HDRS}
                     ${K_SRC_HDRS})

ADD_EXECUTABLE(KExperiment MACOSX_BUNDLE ${K_RC_SRCS} ${KEXP_SRCS})

TARGET_LINK_LIBRARIES(KExperiment ${QT_LIBRARIES} K)

FILE(GLOB TEST_FILES "Tests/*.h")

FOREACH(test ${TEST_FILES})
  GET_FILENAME_COMPONENT(BASENAME ${test} NAME_WE)
  STRING(REPLACE ".h" ".cpp" SRC_NAME ${test})

  QT4_WRAP_CPP("${BASENAME}_MOC_SRCS" ${test})
  ADD_EXECUTABLE(${BASENAME} ${SRC_NAME} ${${BASENAME}_MOC_SRCS})  
  ADD_DEPENDENCIES(${BASENAME} generate)
  TARGET_LINK_LIBRARIES(${BASENAME} ${QT_LIBRARIES} K)

ENDFOREACH(test)