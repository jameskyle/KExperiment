#include "ComponentFactory.h"

namespace kex
{
  ComponentFactory::ComponentFactory() 
  {
    // Map components to their constructors.
    _componentCreatorMap[OutputComponent::RestActionType] = 
      boost::lambda::new_ptr<RestAction>();
    
    _componentCreatorMap[OutputComponent::TextActionType] = 
    boost::lambda::new_ptr<TextAction>();
    
    _componentCreatorMap[OutputComponent::ImageActionType] = 
    boost::lambda::new_ptr<ImageAction>();
    
    _componentCreatorMap[OutputComponent::AudioActionType] = 
    boost::lambda::new_ptr<AudioAction>();
    
    _componentCreatorMap[OutputComponent::VideoActionType] = 
    boost::lambda::new_ptr<VideoAction>();
    
    _componentCreatorMap[OutputComponent::EventType] = 
    boost::lambda::new_ptr<Event>();

    _componentCreatorMap[OutputComponent::TrialType] = 
    boost::lambda::new_ptr<Trial>();

    _componentCreatorMap[OutputComponent::ExperimentType] = 
    boost::lambda::new_ptr<Experiment>();

  }
  
  OutputComponent* 
  ComponentFactory::create(OutputComponent::ComponentTypes key) const
  {
    QMap<OutputComponent::ComponentTypes, Creator>::const_iterator it;
    OutputComponent *component = 0;

    it = _componentCreatorMap.find(key);

    if(it != _componentCreatorMap.end() && (*it))
    {
      component = (*it)();
      component->setComponentType(key);
    }

    return component;
  }
  
  OutputComponent*
  ComponentFactory::create(OutputComponent::ComponentTypes key,
                           const QString& templateName) const
  {
    QMap<OutputComponent::ComponentTypes, Creator>::const_iterator it;
    OutputComponent *component = 0;
    
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

  const QList<OutputComponent::ComponentTypes> ComponentFactory::componentList()
  {
    return _componentCreatorMap.keys();
  }
}
