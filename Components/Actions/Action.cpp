#include "Action.h"

namespace kex
{
  Action::Action(QObject *parent)  : 
    OutputComponent(parent), 
    _durationMSecs(0),
    _durationUnits(MilliSecondType) 
  {
  }
  
  const QStringList Action::actionTypeList(OutputComponent::ComponentTypes t)
  {
    QStringList actionTypes;
    if (t & OutputComponent::RestActionType)
      actionTypes << "Rest";

    if (t & OutputComponent::TextActionType)
      actionTypes << "Text";
    
    if (t & OutputComponent::ImageActionType)
      actionTypes << "Image";
    
    if (t & OutputComponent::AudioActionType)
      actionTypes << "Audio";
    
    if (t & OutputComponent::VideoActionType)
      actionTypes << "Video";
    
    return actionTypes;
  }
    
  bool Action::setDurationMSecs(quint32 duration) 
  {
    bool isValid(false);
    if (duration <= Action::MAX_DURATION)
    {
      _durationMSecs = duration;
      isValid = true;
    }
    
    return isValid;
  }
 
  void Action::updateFromTemplate(const OutputComponent::SharedPointer t)
  {
    Q_CHECK_PTR(t);
    QSharedPointer<Action> action(t.objectCast<Action>());

    // ensure the passed pointer is, in fact, an Action type object
    Q_CHECK_PTR(action);
    
    // call parent method
    OutputComponent::updateFromTemplate(t);
    
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

  bool Action::hasChildren() const
  {
    return false;
  }
  
  int Action::numChildren() const
  {
    // actions don't have children. 
    return 0;
  }
  
  OutputComponent::SharedPointer Action::child(int /*row*/) const
  {
    OutputComponent::SharedPointer sp(0);
    return sp;
  }
  
}