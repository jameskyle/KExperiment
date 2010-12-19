#include "ComponentFactory.h"

namespace kex
{
  ComponentFactory::ComponentFactory()
  {
    // Map components to their constructors.
    m_componentCreatorMap[Component::RestActionType] =
      boost::lambda::new_ptr<RestAction>();

    m_componentCreatorMap[Component::TextActionType] =
    boost::lambda::new_ptr<TextAction>();

    m_componentCreatorMap[Component::ImageActionType] =
    boost::lambda::new_ptr<ImageAction>();

    m_componentCreatorMap[Component::AudioActionType] =
    boost::lambda::new_ptr<AudioAction>();

    m_componentCreatorMap[Component::VideoActionType] =
    boost::lambda::new_ptr<VideoAction>();

    m_componentCreatorMap[Component::EventType] =
    boost::lambda::new_ptr<Event>();

    m_componentCreatorMap[Component::TrialType] =
    boost::lambda::new_ptr<Trial>();

    m_componentCreatorMap[Component::ExperimentType] =
    boost::lambda::new_ptr<Experiment>();

  }

  Component::Pointer
  ComponentFactory::create(Component::ComponentTypes key) const
  {
    QMap<Component::ComponentTypes, Creator>::const_iterator it;
    Component::Pointer component = 0;

    it = m_componentCreatorMap.find(key);

    if(it != m_componentCreatorMap.end() && (*it))
    {
      component = (*it)();
    }

    return component;
  }

  Component::Pointer
  ComponentFactory::create(Component::ComponentTypes key,
                           const QString& templateName) const
  {
    QMap<Component::ComponentTypes, Creator>::const_iterator it;
    Component::Pointer component = 0;

    it = m_componentCreatorMap.find(key);

    if (it != m_componentCreatorMap.end() && (*it))
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
    return m_componentCreatorMap.keys();
  }
}
