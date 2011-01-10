#include "Trial.h"

namespace kex
{
  Trial::Trial(QObject *parent,
               Component::Pointer parentComponent,
               const QString& name,
               const QString& description,
               const QString& label,
               const QSet<QString>& categories) :
  ComponentCollection(parent, parentComponent, name, description, label,
                      categories)
  {
    m_componentType = Component::TrialType;
  }

  quint64 Trial::durationMSecs() const
  {
    Component::SharedPointer comp;
    quint64 duration = 0;
    // all children are events
    foreach(comp, m_components)
    {
      Event* event;
      event = qobject_cast<Event *>(comp.data());

      if(!event)
      {
        QString msg = "Received %1, but expected Component::EventType";
        InvalidComponentType e(msg.arg(
            Component::componentTypeToString(
                comp->componentType())).toAscii());

        throw e;
      }

      Component::SharedPointer child;
      foreach(child, event->components())
      {
        duration += child->durationMSecs();
      }
    }

    return duration;
  }

  Trial::Pointer Trial::clone() const
  {
    Trial *event = new Trial(parent(),      parentComponent(), name(),
                             description(), label(),           categories());

    Component::SharedPointer comp;
    foreach(comp, m_components)
    {
      event->appendComponent(comp->clone());
    }

    return event;
  }
}
