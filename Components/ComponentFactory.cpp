#include "ComponentFactory.h"

namespace kex
{
  ComponentFactory::ComponentFactory() 
  {
    // Map components to their constructors.
    _componentCreatorMap[ComponentInterface::RestActionType] = 
      boost::lambda::new_ptr<RestAction>();
    
    _componentCreatorMap[ComponentInterface::TextActionType] = 
    boost::lambda::new_ptr<TextAction>();
    
    _componentCreatorMap[ComponentInterface::ImageActionType] = 
    boost::lambda::new_ptr<ImageAction>();
    
    _componentCreatorMap[ComponentInterface::AudioActionType] = 
    boost::lambda::new_ptr<AudioAction>();
    
    _componentCreatorMap[ComponentInterface::VideoActionType] = 
    boost::lambda::new_ptr<VideoAction>();
    
    _componentCreatorMap[ComponentInterface::EventType] = 
    boost::lambda::new_ptr<Event>();

    _componentCreatorMap[ComponentInterface::TrialType] = 
    boost::lambda::new_ptr<Trial>();

    _componentCreatorMap[ComponentInterface::ExperimentType] = 
    boost::lambda::new_ptr<Experiment>();

  }
  
  ComponentInterface* 
  ComponentFactory::create(ComponentInterface::ComponentType key) const
  {
    QMap<ComponentInterface::ComponentType, Creator>::const_iterator it;
    ComponentInterface *component = 0;

    it = _componentCreatorMap.find(key);

    if(it != _componentCreatorMap.end() && (*it))
    {
      component = (*it)();
    }

    return component;
  }
  
  ComponentInterface*
  ComponentFactory::create(ComponentInterface::ComponentType key,
                           const QString& templateName) const
  {
    QMap<ComponentInterface::ComponentType, Creator>::const_iterator it;
    ComponentInterface *component = 0;
    
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

  const QList<ComponentInterface::ComponentType> ComponentFactory::componentList()
  {
    return _componentCreatorMap.keys();
  }
}
