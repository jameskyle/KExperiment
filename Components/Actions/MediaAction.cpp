#include "MediaAction.h"

namespace kex
{
  MediaAction::MediaAction(QObject *parent,
                           const QString& name,
                           const QString& description,
                           const QString& label,
                           const QSet<QString>& categories,
                           const QIcon& icon,
                           quint64 delayMSecs,
                           Phonon::MediaObject* mediaObject) :
  Component(parent, name, description, label, categories, icon),
  m_delayMSecs(delayMSecs),
  m_mediaObject(sound)
  {
  }

  MediaAction::~MediaAction()
  {
    if(m_mediaObject)
      delete m_mediaObject;
  }

  quint64 MediaAction::durationMSecs() const
  {
    return m_mediaObject->totalTime();
  }

  MediaAction* MediaAction::copy() const
  {
    MediaAction* action = new MediaAction();

    return action;
  }
}
