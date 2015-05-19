#include "ComponentCollection.h"

namespace kex
{
   ComponentCollection::ComponentCollection(QObject *parent,
                                         Component::Pointer parentComponent,
                                         const QString& name,
                                         const QString& description,
                                         const QString& label,
                                         const QSet<QString>& categories) :
  Component(parent, parentComponent, name, description, label, categories),
  m_components()
  {
  }

   void ComponentCollection::appendComponent(Component* component)
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
    Component::SharedPointer p(component);
    m_components.append(p);
  }

  Component::SharedPointer ComponentCollection::removeComponentAt(int index)
  {
    Component::SharedPointer sp(m_components[index]);
    sp->setParent(0);
    sp->setParentComponent(0);
    m_components.removeAt(index);
    return sp;
  }

  bool ComponentCollection::operator==(const Component& other) const
  {
    const ComponentCollection* derived;
    derived = qobject_cast<const ComponentCollection*>(&other);

    bool equal = (derived &&
      Component::operator==(other) &&
      components() == derived->components());

    return equal;
  }

  bool ComponentCollection::operator!=(const Component& other) const
  {
    return !(*this == other);
  }

}

