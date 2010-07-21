#include "ComponentFactory.h"

namespace kex
{
  ComponentFactory::ComponentFactory() 
  {
    // Map components to their constructors.
    _componentCreatorMap[Component::RestActionType] = 
      boost::lambda::new_ptr<RestAction>();
    
    _componentCreatorMap[Component::TextActionType] = 
    boost::lambda::new_ptr<TextAction>();
    
    _componentCreatorMap[Component::ImageActionType] = 
    boost::lambda::new_ptr<ImageAction>();
    
    _componentCreatorMap[Component::AudioActionType] = 
    boost::lambda::new_ptr<AudioAction>();
    
    _componentCreatorMap[Component::VideoActionType] = 
    boost::lambda::new_ptr<VideoAction>();
    
    _componentCreatorMap[Component::EventType] = 
    boost::lambda::new_ptr<Event>();

    _componentCreatorMap[Component::TrialType] = 
    boost::lambda::new_ptr<Trial>();

    _componentCreatorMap[Component::ExperimentType] = 
    boost::lambda::new_ptr<Experiment>();

  }
  
  Component::Pointer 
  ComponentFactory::create(Component::ComponentTypes key) const
  {
    QMap<Component::ComponentTypes, Creator>::const_iterator it;
    Component::Pointer component = 0;

    it = _componentCreatorMap.find(key);

    if(it != _componentCreatorMap.end() && (*it))
    {
      component = (*it)();
      component->setComponentType(key);
    }

    return component;
  }
  
  Component::Pointer
  ComponentFactory::create(Component::ComponentTypes key,
                           const QString& templateName) const
  {
    QMap<Component::ComponentTypes, Creator>::const_iterator it;
    Component::Pointer component = 0;
    
    it = _componentCreatorMap.find(key);
    
    if (it != _componentCreatorMap.end() && (*it))
    {
      component = (*it)();
    }
    
    return component;
  }
  
  ComponentFactory& ComponentFactory::instance()
  {
    static ComponentFactory factory;
    return factory;
  }

  const QList<Component::ComponentTypes> ComponentFactory::componentList()
  {
    return _componentCreatorMap.keys();
  }
}
