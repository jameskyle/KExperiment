#ifndef ACTION_H
#define ACTION_H
#include <QObject>

#include <Components/OutputComponent.h>

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
  class Action : public OutputComponent
  {
    Q_OBJECT
    Q_FLAGS(UnitType UnitTypes)
    Q_PROPERTY(quint32 durationMSecs READ durationMSecs WRITE setDurationMSecs)
    Q_PROPERTY(UnitTypes units         READ units         WRITE setUnits)

  public:
    enum UnitType {
      MilliSecondType = 0x1,
      SecondType      = 0x1 << 1,
      KiloSecondType  = 0x1 << 2,
    };
    Q_DECLARE_FLAGS(UnitTypes, UnitType)

    /** \brief Constructor for the Action class.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    **/
    Action (QObject *parent = 0) : OutputComponent(parent), _durationMSecs(0) {}

    /** \brief Destructor for the Actiqon class.
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    **/
    virtual ~Action () {}

    virtual bool setDurationMSecs(quint32 duration);
    virtual quint32 durationMSecs(){ return _durationMSecs;}

    UnitTypes units() const {return _durationUnits;}
    void setUnits(UnitTypes t) {_durationUnits = t;}

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
    static const QStringList actionTypeList(
              OutputComponent::ComponentTypes t = OutputComponent::ActionType);

  private:
    quint32 _durationMSecs;
    UnitTypes _durationUnits;

  };
}
#endif
