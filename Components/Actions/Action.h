#ifndef ACTION_H
#define ACTION_H
#include <QObject>

#include <Components/ComponentInterface.h>

namespace kex
{
  /** \brief  A single action only performs a single action at a time.
  * 
  * Single actions are for performing one task at a time. Tasks may include
  * displaying an image, playing a sound, or pausing for a specified amount 
  * of time. Each task is of a particular type. Types are unique and are 
  * stored in the class's typeList. These are used to populate combo boxes and
  * used in sorting of tasks in the Action Library.
  * 
  * © Copyright 2010 KSpace MRI - James Kyle. All Rights Reserved.
  *
  * \author James Kyle KSpace MRI
  * \author $LastChangedBy$
  * \date 2010-04-01
  * \date $LastChangedDate$
  * \version $Rev$  \sa
  **/
  class Action : public ComponentInterface
  {
  public:
    enum ActionType {
      RestType  = 0x1,
      TextType  = 0x2,
      ImageType = 0x4,
      AudioType = 0x8,
      VideoType = 0x10,
      AllTypes  = (RestType | TextType | ImageType | AudioType | VideoType),
    };
    
    
    /** \brief Constructor for the Action class.
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    **/
    Action () : ComponentInterface() {}
    
    /** \brief Destructor for the Actiqon class.
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    **/
    virtual ~Action () {}
    
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
    * \sa registerComponentTypes() registerComponentType()
    **/
    static const QStringList actionTypeList(ActionType t = AllTypes);
    
    static const QString getActionType(QString action);
  };
}
#endif