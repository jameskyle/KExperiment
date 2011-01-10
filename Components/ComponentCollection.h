#ifndef COMPONENTCOLLECTION_H
#define COMPONENTCOLLECTION_H

#include <QObject>
#include <QString>
#include <QSet>

#include "Component.h"
#include "ComponentExceptions.h"

namespace kex
{
  /** \brief  A collection of components.
  *
  * An CollectionComponent is a collection of other, more basic Components. It
  * has the same basic properties of component.
  *
  * © Copyright 2010 KSpace MRI - James Kyle. All Rights Reserved.
  *
  * \author James Kyle KSpace MRI
  * \author $LastChangedBy$
  * \date 2010-12-21
  * \date $LastChangedDate$
  * \version $Rev$  \sa Component
  **/
  class ComponentCollection : public Component
  {
    Q_OBJECT

  public:
    typedef ComponentCollection* Pointer;
    typedef QSharedPointer<ComponentCollection> SharedPointer;

    /** \brief Constructor for the ComponentCollection class.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \sa Component()
    **/
    explicit ComponentCollection(QObject *parent = 0,
                          Component::Pointer parentComponent = 0,
                          const QString& name = QString(""),
                          const QString& description = QString(""),
                          const QString& label = QString(""),
                          const QSet<QString>& categories=QSet<QString>());

    /** \brief Desctructor for the Collection class.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-21
    **/
    virtual ~ComponentCollection() {}

    /** \brief Returns the list of child components for ComponentCollection
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-21
    * \return QList<Component *> list of components
    **/
    virtual const Component::ComponentList& components() const {return m_components;}

    /** \brief Appends the given component to the child list
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-21
    * \param component the component to be appended
    **/
    virtual void appendComponent(Component* component);

   /** \brief Removes the given component found at index
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-21
    * \param index the index for the component to be removed
    **/
    virtual Component::SharedPointer removeComponentAt(int index);

    /** \brief The equivalence operator for the ComponentCollection object.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-21
    * \return bool true if equal, false otherwise
    **/
    virtual bool operator==(const Component& other) const;

   /** \brief The inequivalence operator for the ComponentCollection object.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-12-21
    * \return bool false if equal, true if not
    **/
    virtual bool operator!=(const Component& other) const;

  protected:
    Component::ComponentList m_components;
  };
}

#endif // COMPONENTCOLLECTION_H
