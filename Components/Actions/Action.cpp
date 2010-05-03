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
    
  const QString getActionType(QString& action)
  {
    
  }

}