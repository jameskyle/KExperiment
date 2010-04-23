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
  
  bool ComponentRegister::registerComponent(const QString& name, 
                                            Creator creator)
  {
    bool found = _componentCreatorMap.contains(name);
    
    if(!found)
    {
      _componentCreatorMap[name] = creator;
    }
    
    return found;
  }
}