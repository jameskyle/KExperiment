#include "ComponentList.h"

namespace kex {
  ComponentList::ComponentList() :
    _componentList()
  {
    
  }
  ComponentList::~ComponentList() 
  {
  }

  ComponentList& ComponentList::instance()
  {
    static ComponentList componentList;
    return componentList;
  }

  OutputComponent::SharedPointer 
  ComponentList::find(const QString& componentName) const
  {
    ComponentQSetIterator i(_componentList);
    OutputComponent::SharedPointer currentComponent;
    OutputComponent::SharedPointer component;
    
    while (i.hasNext())
    {
      currentComponent = i.next();

      if (currentComponent->name() == componentName)
      {
        component = currentComponent;
        break;
      }
    }
    return component;
  }

  void ComponentList::append( OutputComponent::SharedPointer interface)
  {
    if (_componentList.contains(interface))
    {
      Logger *logger = &Logger::instance();

      QString msg("ComponentList::append");
      QString info(QObject::tr("This component has already been defined: %1"));
      logger->displayMessage(msg, info.arg(interface->name()),
                             QMessageBox::Ok, Logger::WarningLogLevel);
    } else
    {
      _componentList.insert(interface);
    }
  }

  bool ComponentList::remove( OutputComponent::SharedPointer comp)
  {
    bool found(false);

    if (_componentList.contains(comp))
    {
      found = _componentList.remove(comp);
    }

    return found;
  }
  
  void ComponentList::append(OutputComponent* interface)
  {
    OutputComponent::SharedPointer p(interface);
    append(p);
  }

  const ComponentList::ComponentQList 
  ComponentList::filter(OutputComponent::ComponentTypes types) const
  {
    ComponentQList  filteredList;
    
   ComponentQSetIterator i(_componentList);
    
    while (i.hasNext())
    {
      OutputComponent::SharedPointer p(i.next());
      if (p->componentType() & types )
      {
        filteredList.append(p);
      }
    }
    
    qSort(filteredList.begin(), filteredList.end(), sortComponentQList);
    
    return filteredList;
  }

  int ComponentList::count() const
  {
    return _componentList.count();
  }

  bool ComponentList::sortComponentQList(const  OutputComponent::SharedPointer c1,
                                         const  OutputComponent::SharedPointer c2)
  {
    return (c1->name() < c2->name());
  }
  
  const ComponentList::ComponentQList ComponentList::toList() const
  {
    ComponentQList qlist = _componentList.toList();
    
    qSort(qlist.begin(), qlist.end(), sortComponentQList);
    return qlist;
  }
}
