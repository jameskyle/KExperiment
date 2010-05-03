#include "ComponentList.h"

namespace kex {
  ComponentInterface* ComponentList::find(const QString& componentName) const
  {
    ComponentInterface *interface = 0;
    ComponentInterface *currentInterface = 0;
    
    QListIterator<ComponentInterface *> i(*this);
    
    while (i.hasNext())
    {
      currentInterface = i.next();
      
      if (currentInterface->name() == componentName)
      {
        interface = currentInterface;
      }
    }
    return interface;
  }
}