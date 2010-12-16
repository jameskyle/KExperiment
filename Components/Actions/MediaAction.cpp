#include "MediaAction.h"

namespace kex
{

  MediaAction::MediaAction(QObject *parent,
                           const QString& name,
                           const QString& description,
                           const QString& label,
                           const QSet<QString>& categories,
                           quint64 delayMSecs,
                           Phonon::MediaObject* mediaObject) :
  Component(parent, name, description, label, categories),
  m_mediaObject(mediaObject),
  m_delayMSecs(delayMSecs)
  {
    Q_CHECK_PTR(mediaObject);
    if(m_mediaObject)
    {
      setComponentType();
    } else {
      m_componentType = Component::ActionType;
    }
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

  void MediaAction::setMediaObject(Phonon::MediaObject* mediaObject)
  {
    Q_CHECK_PTR(mediaObject);
    Q_CHECK_PTR(m_mediaObject);

    delete m_mediaObject;

    m_mediaObject = mediaObject;
    setComponentType();

  }

  void MediaAction::setComponentType()
  {
    if(m_mediaObject->hasVideo())
      m_componentType = Component::VideoActionType;
    else
      m_componentType = Component::AudioActionType;
  }

  MediaAction::Pointer MediaAction::clone() const
  {
    Phonon::MediaObject* m = new Phonon::MediaObject;
    m->setCurrentSource(m_mediaObject->currentSource());

    Pointer action = new MediaAction(parent(), name(), description(),
                                     label(), categories(),
                                     delayMSecs(), m);

    return action;
  }

  bool MediaAction::operator==(const Component& other) const
  {
    const MediaAction* derived = qobject_cast<const MediaAction*>(&other);
    bool equal = (derived &&
      Component::operator==(other) &&
      delayMSecs()                 == derived->delayMSecs()  &&
      mediaObject()->currentSource() == derived->mediaObject()->currentSource());

    return equal;
  }

  bool MediaAction::operator!=(const Component& other) const
  {
    return !(*this == other);
  }
}
