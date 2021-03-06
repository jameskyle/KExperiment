#ifndef EVENT_H
#define EVENT_H
#include "../ComponentCollection.h"

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

  class Event : public ComponentCollection
  {
    Q_OBJECT
  public:
    typedef Event* Pointer;
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
          Component::Pointer parentComponent=0,
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
    * \return qint64 duration in milliseconds for Event
    * \sa Component()
    **/
    qint64 durationMSecs() const;

   /** \brief Creates a copy of the component.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \return Event::Pointer pointer to a new component that is a copy of original
    **/
    Pointer clone() const;
  };
}
#endif
