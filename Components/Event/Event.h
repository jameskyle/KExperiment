#ifndef EVENT_H
#define EVENT_H
#include <QString>
#include <QList>

#include "../Component.h"
#include "../ComponentExceptions.h"

namespace kex
{
  /** \brief  A collection of Action type components.
  *
  * An Event a type of action that is a collection of other basic actions. It
  * has the same basic properties of an action. An Event runs all of its
  * actions concurrently. Thus, if an audio and an image action are added to
  * the Event, both audio and image run concurrently. An Event lasts as long
  * as the duration of its longest Action.
  *
  * © Copyright 2010 KSpace MRI - James Kyle. All Rights Reserved.
  *
  * \author James Kyle KSpace MRI
  * \author $LastChangedBy$
  * \date 2010-04-01
  * \date $LastChangedDate$
  * \version $Rev$  \sa Action OutputAction RestAction
  **/

  class Event : public Component
  {
    Q_OBJECT
  public:
    /** \brief Constructor for the Event class.
    *
    * The constructor for the Event class ensures all core type have been
    * allocated and instantiated.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \sa Action()
    **/
    Event(QObject *parent = 0,
          const QString& name=QString(""),
          const QString& description=QString(""),
          const QString& label=QString(""),
          const QSet<QString>& categories=QSet<QString>());

    /** \brief The destructor for the Event class
    *
    * Ensures all allocated resources of the Event class have been freed.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \sa ~Action()
    **/
    ~Event () {}

   /** \brief Returns the total duration in milliseconds for event.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \return quint64 duration in milliseconds for Event
    * \sa Component()
    **/
    quint64 durationMSecs() const;

   /** \brief Returns the list of child components for Event
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \return QList<Component *> list of components
    **/
    const QList<Component *> components() const {return m_components;}

   /** \brief Appends the given component to the child list
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \param component the component to be appended
    **/
    void appendComponent(Component* component);

   /** \brief Removes the given component found at index
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \param index the index for the component to be removed
    **/
    void removeComponentAt(int index);

   /** \brief The equivalence operator for the Event object.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \return bool true if equal, false otherwise
    **/
    bool operator==(const Component& other) const;

   /** \brief The inequivalence operator for the Event object.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \return bool false if equal, true if not
    **/
    bool operator!=(const Component& other) const;

   /** \brief Creates a copy of the component.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \return Event* pointer to a new component that is a copy of original
    **/
    Event* copy() const;

  private:
    QList<Component *> m_components; //!< list of components

  };
}
#endif
