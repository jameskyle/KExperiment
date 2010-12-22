#include "Event.h"

namespace kex
{
  Event::Event(QObject *parent,
               Component::Pointer parentComponent,
               const QString& name,
               const QString& description,
               const QString& label,
               const QSet<QString>& categories) :
  Component(parent, parentComponent, name, description, label, categories),
  m_components()
  {
    m_componentType = Component::EventType;
  }

  quint64 Event::durationMSecs() const
  {
    Component* comp;
    quint64 duration = 0;

    foreach(comp, m_components)
    {
      duration += comp->durationMSecs();
    }

    return duration;
  }

  void Event::appendComponent(Component* component)
  {
    Q_CHECK_PTR(component);

    if(!component->componentType() & Component::ActionType)
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

  void Event::removeComponentAt(int index)
  {
    m_components.removeAt(index);
  }

  bool Event::operator==(const Component& other) const
  {
    const Event* derived = qobject_cast<const Event*>(&other);
    bool equal = (derived &&
      Component::operator==(other) &&
      components() == derived->components());

    return equal;
  }

  bool Event::operator!=(const Component& other) const
  {
    return !(*this == other);
  }

  Event::Pointer Event::clone() const
  {
    Event *event = new Event(parent(),      parentComponent(), name(),
                             description(), label(),           categories());

    Component* comp;
    foreach(comp, m_components)
    {
      event->appendComponent(comp->clone());
    }

    return event;
  }
}
