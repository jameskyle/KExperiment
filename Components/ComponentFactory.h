#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <boost/lambda/lambda.hpp>
#include <boost/lambda/construct.hpp>
#include <boost/function.hpp>

#include <QStringList>
#include <QMap>
#include <QVariant>
#include <QXmlStreamReader>
#include <QXmlSchemaValidator>
#include <QXmlSchema>

#include "ComponentInterface.h"
#include "ComponentList.h"
#include "Events/Event.h"
#include "Actions/RestAction.h"

#include <Common/Types.h>
#include <Common/Global.h>

class ComponentInterface;

namespace kex
{
  //!< factor creator pointer
  typedef boost::function<ComponentInterface* ()> Creator;

  /** \brief  Factory for the ComponentInterface interface
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
    * \sa ComponentInterface
    **/
    static ComponentFactory& instance();

    /** \brief Returns a pointer to the component interface using its create
    * method
    *
    * Provides a pointer to a newly created object of type 'key'. The object
    * must be derived from the ComponentInterface and be registered before.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-02
    * \param  key the mapped key to the registered component.
    *
    * \return ComponentInterface* pointer to the newly created object
    *
    * \sa ComponentInterface
    **/
    ComponentInterface* create(QString key);

    /** \brief  Creates a component based on the provided xml document.
     *
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-5-3
     * \date $LastChangedDate$
     * \param xml the xml file to be parsed
     * \return ComponentInterface* pointer to the newly created object
     * \version $Rev$  \sa create(QString& key)
     **/
    ComponentInterface* createFromXml(QFile& xml);

    ~ComponentFactory () {}

    /** \brief Registers an Action type
    *
    * This is an instance version of the static registerComponentType. Each
    * Action has a type specifier. That type must be registered in
    * order to appear in selections or filter options in Libraries. It also
    * registers the creation function for that specific Action.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-02
    * \param  type a string specifiying the type of single action
    * \param creator the function to be used for instnatiation
    *
    **/
    bool registerComponent(const QString& name, Creator creator);

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
    const QStringList componentList();
    
  private:
    ComponentFactory() {}    //!< private constructor

    ComponentInterface* parseAction(QXmlStreamReader *reader,
                                    Action::ActionType type);
    
    void readXmlComponentHeader(QXmlStreamReader* reader, 
                                ComponentInterface *component);

    QMap<QString, Creator> _componentCreatorMap;

  };

  #define REGISTER_COMPONENT(CLASSID, COMPONENT) \
    ComponentFactory::instance().registerComponent(CLASSID, \
     boost::lambda::new_ptr<COMPONENT>());
}
#endif
