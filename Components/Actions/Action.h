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
    /** \brief Constructor for the Action class.
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    **/
    Action () : ComponentInterface() {}
    
    /** \brief Destructor for the Action class.
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    **/
    virtual ~Action () {}
    
    /** \brief Registers a Action type
    * 
    * Each Action has a type specifier. That type must be registered in
    * order to appear in selections or filter options in Libraries.
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \param  type a string specifiying the type of single action
    * 
    * \sa registerComponentTypes() actionTypeList()
    **/
    static void addActionType(const QString& type);
    
    /** \brief Registers a list of Action types
    * 
    * Each Action has a type specifier. That type must be registered in
    * order to appear in selections or filter options in Libraries. This 
    * method registers a list of actions at a time.
    * 
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    * \param  type a string specifiying the type of single action
    * 
    * \sa registerComponentType() actionTypeList()
    **/
    static void addActionTypes(const QList<QString>& types);
    
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
    static const QStringList& actionTypeList();
    
    /*
      TODO doc for log function
    */
    virtual void log(const QString& msg) {QString foo = msg;}
    
    enum ActionType {REST, IMAGE, AUDIO, VIDEO};

  protected:
    static QStringList& _actionTypeList();  //!< list of types of actions
    
  };
}
#endif