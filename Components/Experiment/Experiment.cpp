#include "Experiment.h"

namespace kex
{
  Experiment::Experiment(QObject *parent,
                         Component::Pointer parentComponent,
                         const QString& name,
                         const QString& description,
                         const QString& label,
                         const QSet<QString>& categories) :
  ComponentCollection(parent, parentComponent, name, description, label,
                      categories)
  {
    m_componentType = Component::ExperimentType;
  }

  qint64 Experiment::durationMSecs() const
  {
    Component::SharedPointer comp;
    qint64 duration = 0;
    // all children are trials
    foreach(comp, m_components)
    {
      Trial* trial;
      trial = qobject_cast<Trial *>(comp.data());

      if(!trial)
      {
        QString msg = "Received %1, but expected Component::EventType";
        InvalidComponentType e(msg.arg(
            Component::componentTypeToString(
                comp->componentType())).toAscii());

        throw e;
      }

      Component::SharedPointer child;
      foreach(child, trial->components())
      {
        duration += child->durationMSecs();
      }
    }

    return duration;
  }

  Experiment::Pointer Experiment::clone() const
  {
    Experiment *experiment = new Experiment(parent(), parentComponent(),
                                            name(),   description(),
                                            label(),  categories());

    Component::SharedPointer comp;
    foreach(comp, m_components)
    {
      experiment->appendComponent(comp->clone());
    }

    return experiment;
  }
}
