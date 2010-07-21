#include "Action.h"

namespace kex
{
  Action::Action(QObject *parent)  : 
    Component(parent), 
    m_durationMSecs(0),
    m_durationUnits(MilliSecondType) 
  {
  }
  
  const QStringList Action::actionTypeList(Component::ComponentTypes t)
  {
    QStringList actionTypes;
    if (t & Component::RestActionType)
      actionTypes << "Rest";

    if (t & Component::TextActionType)
      actionTypes << "Text";
    
    if (t & Component::ImageActionType)
      actionTypes << "Image";
    
    if (t & Component::AudioActionType)
      actionTypes << "Audio";
    
    if (t & Component::VideoActionType)
      actionTypes << "Video";
    
    return actionTypes;
  }
    
  bool Action::setDurationMSecs(quint32 duration) 
  {
    bool isValid(false);
    if (duration <= Action::MAX_DURATION)
    {
      m_durationMSecs = duration;
      isValid = true;
    }
    
    return isValid;
  }
 
  void Action::updateFromTemplate(const Component::SharedPointer t)
  {
    Q_CHECK_PTR(t);
    QSharedPointer<Action> action(t.objectCast<Action>());

    // ensure the passed pointer is, in fact, an Action type object
    Q_CHECK_PTR(action);
    
    // call parent method
    Component::updateFromTemplate(t);
    
    // After that, the only thing left is the duration field for actions
    if (action->durationMSecs() != durationMSecs())
    {
      // test for default time condition indicating it has not been set
      if (durationMSecs() == 0)
      {
        setDurationMSecs(action->durationMSecs());
      }
    }
  }  
}