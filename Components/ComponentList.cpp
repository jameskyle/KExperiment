#include "ComponentList.h"

namespace kex {
  ComponentList::~ComponentList() 
  {
    qDeleteAll(_componentList.begin(), _componentList.end());
  }

  ComponentList& ComponentList::instance()
  {
    static ComponentList componentList;
    return componentList;
  }

  OutputComponent*
  ComponentList::find(const QString& componentName) const
  {
    OutputComponent* component(0);
    OutputComponent* currentComponent(0);

    QSetIterator< OutputComponent* > i(_componentList);

    while (i.hasNext())
    {
      currentComponent = i.next();

      if (currentComponent->name() == componentName)
      {
        component = currentComponent;
      }
    }
    return component;
  }

  void ComponentList::append(OutputComponent* interface)
  {
    if (_componentList.contains(interface))
    {
      Logger *logger = &Logger::instance();

      QString msg("ComponentList::append");
      QString info("This component has already been defined: %1");
      logger->displayMessage(msg, info.arg(interface->name()),
                             QMessageBox::Ok, Logger::WarningLogLevel);
    } else
    {
      _componentList.insert(interface);
    }
  }

  bool ComponentList::remove(OutputComponent* comp)
  {
    // when we remove a component from the global list, we delete it
    if (_componentList.contains(comp))
    {
      comp->deleteLater();
    }
    return _componentList.remove(comp);
  }
    
  const ComponentList::ComponentQList 
  ComponentList::filter(OutputComponent::ComponentTypes types) const
  {
    ComponentQList  filteredList;
    OutputComponent* temp;
    
    QSetIterator< OutputComponent* > i(_componentList);
    while (i.hasNext())
    {
      temp = i.next();
      if (temp->componentType() & types )
      {
        filteredList.append(temp);
      }
    }
    
//    qSort(filteredList.begin(), filteredList.end(), 
//          Utilities::sortComponentQList);
    
    return filteredList;
  }

  int ComponentList::count() const
  {
    return _componentList.count();
  }

  const ComponentList::ComponentQList ComponentList::toList() const
  {
    ComponentQList qlist = _componentList.toList();

//    qSort(qlist.begin(), qlist.end(), Utilities::sortComponentQList);
    return qlist;
  }

}
