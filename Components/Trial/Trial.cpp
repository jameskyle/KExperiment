#include "Trial.h"

namespace kex
{
  Trial::Trial(QObject *parent,
          const QString& name,
          const QString& description,
          const QString& label,
          const QSet<QString>& categories) :
  Component(parent, name, description, label, categories),
  m_components()
  {
  }

  quint64 Trial::durationMSecs() const
  {
    Component* comp;
    quint64 duration = 0;
    // all children are events
    foreach(comp, m_components)
    {
      Event* event;
      event = qobject_cast<Event *>(comp);

      if(!event)
      {
        QString msg = "Received %1, but expected Component::EventType";
        InvalidComponentType e(msg.arg(
            Component::componentTypeToString(
                comp->componentType())).toAscii());

        throw e;
      }

      Component* child;
      foreach(child, event->components())
      {
        duration += child->durationMSecs();
      }
    }

    return duration;
  }

  void Trial::appendComponent(Component* component)
  {
    if(!component->componentType() & Component::ActionType)
    {
      QString msg = "Received %1, but expected Component::ActionType";

      InvalidComponentType e(msg.arg(
          Component::componentTypeToString(
              component->componentType())).toAscii());

      throw e;
    }
    m_components.append(component);
  }

  void Trial::removeComponentAt(int index)
  {
    m_components.removeAt(index);
  }

  bool Trial::operator==(const Component& other) const
  {
    const Trial* derived = qobject_cast<const Trial*>(&other);
    bool equal = (derived &&
      Component::operator==(other) &&
      components() == derived->components());

    return equal;
  }

  bool Trial::operator!=(const Component& other) const
  {
    return !(*this == other);
  }

  Trial::Pointer Trial::clone() const
  {
    Trial *event = new Trial(parent(), name(), description(), label(),
                             categories());

    Component* comp;
    foreach(comp, m_components)
    {
      event->appendComponent(comp->clone());
    }

    return event;
  }
}
