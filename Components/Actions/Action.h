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
      UnknownType = 0x20,
      AllTypes  = (RestType | TextType | ImageType | AudioType | VideoType),
    };
    
    
    /** \brief Constructor for the Action class.
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    **/
    Action () : ComponentInterface(), _durationMSecs(0) {}
    
    /** \brief Destructor for the Actiqon class.
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    **/
    virtual ~Action () {}
    
    virtual bool setDurationMSecs(quint32 duration);
    virtual quint32 durationMSecs(){ return _durationMSecs;}
    
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
    
    static ActionType getActionType(const QString& action);
    static QString getActionString(ActionType actionType);
    
  private:
    quint32 _durationMSecs;
    
  };
}
#endif