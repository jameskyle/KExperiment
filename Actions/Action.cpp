#include "Action.h"

namespace kex
{
  QStringList& Action::_actionTypeList()
  {
    static QStringList _list;
    if(_list.isEmpty())
    {
      _list << "Rest" << "Text" << "Image" << "Video";
    }
    return _list;
  }
  
  const QStringList& Action::actionTypeList()
  {
    return _actionTypeList();
  }
  
  void Action::addActionType(const QString& type)
  {
    _actionTypeList() << type;
  }
  
  void Action::addActionTypes(const QList<QString>& types)
  {
    foreach(QString st, types) {
      _actionTypeList().append(st);
    }
  }
}