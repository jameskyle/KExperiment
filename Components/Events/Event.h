#ifndef EVENT_H
#define EVENT_H
#include <QString>
#include <QList>

#include <Components/ComponentInterface.h>

namespace kex
{
  /** \brief  An Event is a special type of Action that is composed of other
  * basic actions.
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
  class Event : public ComponentInterface
  {
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
    Event () : ComponentInterface() {}
    
    /** \brief The destructor for the Event class
    * 
    * Ensures all allocated resources of the Event class have been freed.
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \sa ~Action()
    **/
    virtual ~Event ();
    
  private:
    QList<ComponentInterface *> _actionList;
  };
}
#endif