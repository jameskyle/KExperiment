#include "Experiment.h"

namespace kex
{
  Experiment::Experiment(QObject *parent,
                         Component::Pointer parentComponent,
                         const QString& name,
                         const QString& description,
                         const QString& label,
                         const QSet<QString>& categories) :
  Component(parent, parentComponent, name, description, label, categories),
  m_components()
  {
    m_componentType = Component::ExperimentType;
  }

  quint64 Experiment::durationMSecs() const
  {
    Component* comp;
    quint64 duration = 0;
    // all children are trials
    foreach(comp, m_components)
    {
      Trial* trial;
      trial = qobject_cast<Trial *>(comp);

      if(!trial)
      {
        QString msg = "Received %1, but expected Component::EventType";
        InvalidComponentType e(msg.arg(
            Component::componentTypeToString(
                comp->componentType())).toAscii());

        throw e;
      }

      Component* child;
      foreach(child, trial->components())
      {
        duration += child->durationMSecs();
      }
    }

    return duration;
  }

  void Experiment::appendComponent(Component* component)
  {
    Q_CHECK_PTR(component);

    if(!component->componentType() & Component::TrialType)
    {
      QString msg = "Received %1, but expected Component::ActionType";

      InvalidComponentType e(msg.arg(
          Component::componentTypeToString(
              component->componentType())).toAscii());

      throw e;
    }
    component->setParentComponent(this);
    component->setParent(this);
    m_components.append(component);
  }

  void Experiment::removeComponentAt(int index)
  {
    m_components.removeAt(index);
  }

  bool Experiment::operator==(const Component& other) const
  {
    const Experiment* derived = qobject_cast<const Experiment*>(&other);
    bool equal = (derived &&
      Component::operator==(other) &&
      components() == derived->components());

    return equal;
  }

  bool Experiment::operator!=(const Component& other) const
  {
    return !(*this == other);
  }

  Experiment::Pointer Experiment::clone() const
  {
    Experiment *experiment = new Experiment(parent(), parentComponent(),
                                            name(),   description(),
                                            label(),  categories());

    Component* comp;
    foreach(comp, m_components)
    {
      experiment->appendComponent(comp->clone());
    }

    return experiment;
  }
}
