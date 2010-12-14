#include "Action.h"

namespace kex
{
  Action::Action(QObject *parent)  :
    Component(parent),
    m_durationMSecs(0)
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

}
