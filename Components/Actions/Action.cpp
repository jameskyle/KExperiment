#include "Action.h"

namespace kex
{
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
  
}