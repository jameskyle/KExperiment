#include "Event.h"

namespace kex
{
  Event::Event(QObject *parent,
               Component::Pointer parentComponent,
               const QString& name,
               const QString& description,
               const QString& label,
               const QSet<QString>& categories) :
  ComponentCollection(parent, parentComponent, name, description, label,
                      categories)
  {
    m_componentType = Component::EventType;
  }

  quint64 Event::durationMSecs() const
  {
    Component::SharedPointer comp;
    quint64 duration = 0;

    foreach(comp, m_components)
    {
      duration += comp->durationMSecs();
    }

    return duration;
  }

  Event::Pointer Event::clone() const
  {
    Event *event = new Event(parent(),      parentComponent(), name(),
                             description(), label(),           categories());

    Component::SharedPointer comp;
    foreach(comp, m_components)
    {
      event->appendComponent(comp->clone());
    }

    return event;
  }

}
