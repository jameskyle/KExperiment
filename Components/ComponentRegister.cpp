#include "ComponentRegister.h"

namespace kex
{
  ComponentInterface* ComponentRegister::Create(QString& key)
  {
    QMap<QString, Creator>::const_iterator it;
    ComponentInterface *component = 0;
    
    it = _componentCreatorMap.find(key);
    
    if(it != _componentCreatorMap.end() && (*it))
    {
      component = (*it)();
    }
    
    return component;
  }
  
  ComponentRegister& ComponentRegister::instance()
  {
    static ComponentRegister af;
    return af;
  }
  
  const QStringList ComponentRegister::componentList()
  {
    return _componentCreatorMap.keys();
  }
  
  void ComponentRegister::registerComponent(const QString& name, Creator creator)
  {
    if(!_componentCreatorMap.contains(name))
    {
      _componentCreatorMap[name] = creator;
    }
  }
  
}