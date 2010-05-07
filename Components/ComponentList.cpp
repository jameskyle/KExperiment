#include "ComponentList.h"

namespace kex {
  ComponentList& ComponentList::instance()
  {
    static ComponentList componentList;
    return componentList;
  }
    
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
  
  void ComponentList::append(ComponentInterface* interface)
  {
    if (contains(interface))
    {
      Logger *logger = &Logger::instance();
      
      QString msg("ComponentList::append");
      QString info("This component has already been defined: %1");
      logger->displayMessage(msg, info.arg(interface->name()), 
                             QMessageBox::Ok, Logger::WarningLogLevel);
    } else
    {
      QList<ComponentInterface *>::append(interface);
    }
  }
  
}