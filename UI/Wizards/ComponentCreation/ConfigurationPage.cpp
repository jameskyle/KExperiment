#include "ConfigurationPage.h"

namespace kex
{
  ConfigurationPage::ConfigurationPage(const Component::ComponentTypes component,
                                       QWidget *parent)
    : BaseConfigurationPage(parent),
      libraryToolButtonHLayout(0),
      _component(component)
  {
    registerField("durationMsecs", &durationSpinBoxMsecs);

    Logger::instance().log("Initialized", this);
  }

  ConfigurationPage::~ConfigurationPage()
  {
    // clean up the library tool button layout if we created one
    if (libraryToolButtonHLayout)
    {
      delete libraryToolButtonHLayout;
    }
  }

  QHBoxLayout* ConfigurationPage::getLibraryButtonLayout()
  {
    libraryToolButtonHLayout = new QHBoxLayout;
    QToolButton *button;
    QSignalMapper *signalMapper = new QSignalMapper(this);

    libraryToolButtonHLayout->addStretch();

    if (_component & (Component::EventType |
                      Component::TrialType |
                      Component::ExperimentType))
    {
      button = new QToolButton(this);
      button->setText(tr("Action Library"));
      libraryToolButtonHLayout->addWidget(button);
      connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
      signalMapper->setMapping(button, "action");
    }

    if (_component & (Component::TrialType | Component::ExperimentType))
    {
      button = new QToolButton(this);
      button->setText(tr("Event Library"));
      libraryToolButtonHLayout->addWidget(button);
      connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
      signalMapper->setMapping(button, "event");
    }

    if (_component & Component::ExperimentType)
    {
      button = new QToolButton(this);
      button->setText(tr("Trial Library"));
      libraryToolButtonHLayout->addWidget(button);
      connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
      signalMapper->setMapping(button, "trial");

    }

    connect(signalMapper, SIGNAL(mapped(const QString&)), this,
            SLOT(dispatchLibraryRequest(const QString&)));
    return libraryToolButtonHLayout;
  }

  void ConfigurationPage::setTitles()
  {
    QString name("Component");

    switch (_component)
    {
      case Component::ActionType:
        name = "Action";
        break;
      case Component::EventType:
        name = "Event";
        break;
      case Component::TrialType:
        name = "Trial";
        break;
      case Component::ExperimentType:
        name = "Experiment";
    }

    setTitle(tr("%1 Configuration").arg(name));
    setSubTitle(tr("Please configure your new %1").arg(name));

  }

  void ConfigurationPage::initializePage()
  {
    BaseConfigurationPage::initializePage();

    Q_ASSERT(field("name").isValid());
    Q_ASSERT(field("label").isValid());

    if(_component & Component::ActionType)
    {
      Logger::instance().log("Configuring for Component::ActionType", this);

      Q_ASSERT(field("action").isValid());
      actionTypeHLayout.addWidget(new QLabel(tr("Action Type:"), this));
      actionTypeHLayout.addWidget(new QLabel(field("action").toString(),
                                             this));
      _mainLayout.addLayout(&actionTypeHLayout);
    }

    if(_component & (Component::ActionType | Component::EventType | Component::TrialType | Component::ExperimentType))
    {
      Logger::instance().log("Adding duration spinbox", this);

      _mainLayout.addLayout(&durationHLayout);
      durationHLayout.setObjectName("durationHLayout");
      durationLabel.setText("Duration:");
      durationLabel.setObjectName("durationLabel");
      durationHLayout.addWidget(&durationLabel);

      durationSpinBoxMsecs.setMaximum(Component::MAX_DURATION);
      durationSpinBoxMsecs.setSingleStep(DURATION_STEPSIZE);
      durationSpinBoxMsecs.setDecimals(DURATION_DECIMALS);
      durationHLayout.addWidget(&durationLabel);
      durationHLayout.addWidget(&durationSpinBoxMsecs);
    }

    if(_component & (Component::EventType | Component::TrialType | Component::ExperimentType))
    {
      Logger::instance().log("Adding comonent list and library buttons", this);

      // Set up the action selection portion
      componentListLabel.setObjectName("componentListLabel");
      componentListVLayout.setObjectName("componentListVLayout");
      componentListView.setObjectName("componentListView");

      componentListLabel.setText("Component List:");

      _mainLayout.addLayout(&componentListVLayout);
      componentListVLayout.addWidget(&componentListLabel);
      componentListVLayout.addWidget(&componentListView);
      componentListVLayout.addLayout(getLibraryButtonLayout());
    }
  }

  void ConfigurationPage::dispatchLibraryRequest(const QString& libraryType)
  {
    QString msg = "didpsatchLibraryRequest Called: %1";
    Logger::instance().log(qPrintable(msg.arg(libraryType)), this);

    if (libraryType == "action")
    {
      emit launchComponentLibraryRequested(Component::ActionType);
    } else if (libraryType == "event")
    {
      emit launchComponentLibraryRequested(Component::EventType);
    } else if (libraryType == "trial")
    {
      emit launchComponentLibraryRequested(Component::TrialType);
    }
  }
}
