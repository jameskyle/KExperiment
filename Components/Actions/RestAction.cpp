#include "RestAction.h"

namespace kex
{

  RestAction::RestAction(QObject             *parent,
                         Component::Pointer   parentComponent,
                         const QString&       name,
                         const QString&       description,
                         const QString&       label,
                         const QSet<QString>& categories,
                         quint64              durationMSecs) :
  Component(parent, parentComponent, name, description, label, categories),
  m_durationMSecs(durationMSecs)
  {
    m_componentType = Component::RestActionType;
  }

  RestAction::~RestAction()
  {

  }

  RestAction::Pointer RestAction::clone() const
  {
    RestAction *action = new RestAction(parent(),     parentComponent(),
                                        name(),       description(),
                                        label(),      categories(),
                                        durationMSecs());

    return action;
  }

  bool RestAction::operator==(const Component& other) const
  {
    const RestAction* derived = qobject_cast<const RestAction*>(&other);
    bool equal = (derived &&
                  Component::operator==(other) &&
                  durationMSecs() == derived->durationMSecs());

    return equal;
  }

  bool RestAction::operator!=(const Component& other) const
  {
    return !(*this == other);
  }
}
