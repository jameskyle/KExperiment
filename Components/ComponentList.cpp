#include "ComponentList.h"

namespace kex {
  ComponentList& ComponentList::instance()
  {
    static ComponentList componentList;
    return componentList;
  }

  QSharedPointer<ComponentInterface>
  ComponentList::find(const QString& componentName) const
  {
    QSharedPointer<ComponentInterface> component(0);
    QSharedPointer<ComponentInterface> currentComponent(0);

    QSetIterator< AbstractComponent::Pointer > i(_componentList);

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

  void ComponentList::append(AbstractComponent::Pointer interface)
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

  bool ComponentList::remove(AbstractComponent::Pointer comp)
  {
    bool success(false);
    // we enforce only a single occurance of a component in the list. limited
    // by name
    if (_componentList.contains(comp))
    {
      success = _componentList.remove(comp);
    }

    return success;
  }

  const ComponentList::ComponentQList* ComponentList::filter(int types) const
  {
    ComponentQList  *filteredList;
    filteredList = new ComponentQList;
    AbstractComponent::Pointer temp;
    
    QSetIterator< AbstractComponent::Pointer > i(_componentList);
    while (i.hasNext())
    {
      temp = i.next();
      if (temp->componentType() & types )
      {
        filteredList->append(temp);
      }
    }
    qSort(filteredList->begin(), filteredList->end(), 
          Utilities::sortComponentQList);
    return filteredList;
  }

  int ComponentList::count() const
  {
    return _componentList.count();
  }

  const ComponentList::ComponentQList* ComponentList::toList() const
  {
    ComponentQList* qlist;
    qlist = new ComponentQList(_componentList.toList());

    qSort(qlist->begin(), qlist->end(), Utilities::sortComponentQList);
    return qlist;
  }

}
