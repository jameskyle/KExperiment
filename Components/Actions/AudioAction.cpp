#include "AudioAction.h"

namespace kex
{
  AudioAction::AudioAction(QObject *parent,
                           const QString& name,
                           const QString& description,
                           const QString& label,
                           const QSet<QString>& categories,
                           const QIcon& icon,
                           quint64 delayMSecs,
                           Phonon::MediaObject* sound) :
  Component(parent, name, description, label, categories, icon),
  m_delayMSecs(delayMSecs),
  m_sound(sound)
  {
  }

  AudioAction::~AudioAction()
  {
    if(m_sound)
      delete m_sound;
  }

  void AudioAction::setSound(Phonon::MediaObject* sound)
  {
    if(m_sound)
      delete m_sound;

    m_sound = sound;
  }

  quint64 AudioAction::durationMSecs() const
  {
    return m_sound->totalTime();
  }

  AudioAction* AudioAction::copy() const
  {
    AudioAction* action = new AudioAction();

    return action;
  }
}
