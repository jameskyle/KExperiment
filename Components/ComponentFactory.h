#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <boost/lambda/lambda.hpp>
#include <boost/lambda/construct.hpp>
#include <boost/function.hpp>

#include <QStringList>
#include <QMap>
#include <QVariant>

#include "Components/Components.h"
#include "Common/Config.h"
#include "Common/Uncopyable.h"

namespace kex
{
  //!< factor creator pointer
  typedef boost::function<Component::Pointer ()> Creator;

  /** \brief  Factory for the Component interface
  *
  * This singleton class creates specific Actions given the appropriate
  * registered identifier.
  *
  * © Copyright 2010 KSpace MRI - James Kyle. All Rights Reserved.
  *
  * \author James Kyle KSpace MRI
  * \author $LastChangedBy$
  * \date 2010-04-02
  * \date $LastChangedDate$
  * \version $Rev$  \sa
  **/
  class ComponentFactory : private Uncopyable
  {
  public:
    /** \brief Returns the instance for the ComponentFactory
    *
    * The ComponentFactory stores information about created objects. This
    * information is used for object creation and Component specific
    * details for the Wizard creator.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-02
    * \return ComponentFactory a reference to the ComponentFactory object.
    *
    * \sa Component
    **/
    static ComponentFactory& instance();

    /** \brief Returns a pointer to the component interface using its create
    * method
    *
    * Provides a pointer to a newly created object of type 'key'. The object
    * must be derived from the Component and be registered before.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-02
    * \param  key the mapped key to the registered component.
    *
    * \return Component::Pointer pointer to the newly created object
    *
    * \sa Component
    **/
    Component::Pointer create(Component::ComponentTypes key) const;
    Component::Pointer create(Component::ComponentTypes key,
                               const QString& templateName) const;

    /** \brief Returns a list of Action types
    *
    * Each Action has a type specifier. That type must be registered in
    * order to appear in selections or filter options in Libraries. Once
    * registered, the types are available in this list.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \param  types a Qlist of QStrings of Action types.
    *
    * /sa registerComponentTypes() registerComponentType()
    **/
    const QList<Component::ComponentTypes> componentList();
    
  private:
    ~ComponentFactory () {}
    ComponentFactory();    //!< private constructor

    QMap<Component::ComponentTypes, Creator> _componentCreatorMap;

  };

/*  #define REGISTER_COMPONENT(CLASSID, COMPONENT) \
    ComponentFactory::instance().registerComponent(CLASSID, \
     boost::lambda::new_ptr<COMPONENT>()); */
}
#endif
