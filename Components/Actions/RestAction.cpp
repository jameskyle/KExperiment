#include "RestAction.h"

namespace kex
{

  RestAction::RestAction(QObject *parent,
                         const QString& name,
                         const QString& description,
                         const QString& label,
                         const QSet<QString>& categories,
                         const QIcon& icon,
                         quint64 durationMSecs,
                         quint64 delayMSecs) :
  Component(parent, name, description, label, categories, icon),
  m_durationMSecs(durationMSecs),
  m_delayMSecs(delayMSecs)
  {
    m_componentType = Component::RestActionType;
  }

  RestAction::~RestAction()
  {

  }
}
