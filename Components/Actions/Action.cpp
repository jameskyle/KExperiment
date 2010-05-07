#include "Action.h"

namespace kex
{
  const QStringList Action::actionTypeList(ActionType t)
  {
    QStringList actionTypes;
    if (t & RestType)
      actionTypes << "Rest";

    if (t & TextType)
      actionTypes << "Text";
    
    if (t & ImageType)
      actionTypes << "Image";
    
    if (t & AudioType)
      actionTypes << "Audio";
    
    if (t & VideoType)
      actionTypes << "Video";
    
    return actionTypes;
  }
    
  Action::ActionType Action::getActionType(const QString& action)
  {
    ActionType actionType;
    QString a = action.toLower();
    
    if (a == "rest")
    {
      actionType = RestType;
    } else if (a == "text")
    {
      actionType = TextType;
    } else if (a == "image")
    {
      actionType = ImageType;
    } else if (a == "audio")
    {
      actionType = AudioType;
    } else if (a == "video")
    {
      actionType = VideoType;
    } else
    {
      actionType = UnknownType;
    }

    
    return actionType;
  }
  
  QString Action::getActionString(ActionType actionType)
  {
    QString result("");
    
    switch (actionType)
    {
      case RestType:
        result = "rest";
        break;
      case TextType:
        result = "text";
        break;
      case ImageType:
        result = "image";
        break;
      case AudioType:
        result = "audio";
        break;
      case VideoType:
        result = "video";
        break;
      default:
        result = "unknown";
        break;
    }
    return result;
  }

}