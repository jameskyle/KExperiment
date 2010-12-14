#ifndef AUDIOACTION_H
#define AUDIOACTION_H

#include <Phonon/MediaObject>

#include "Components/Component.h"

namespace kex
{
  class AudioAction : public Component
  {
    Q_OBJECT
    Q_PROPERTY(QString file WRITE setFile READ file)

  public:
    AudioAction(QObject *parent = 0,
                const QString& name=QString(""),
                const QString& description=QString(""),
                const QString& label=QString(""),
                const QSet<QString>& categories=QSet<QString>(),
                const QIcon& icon=QIcon(Component::DEFAULT_ICON),
                quint64 delayMSecs=0,
                Phonon::MediaObject* sound=0);
    ~AudioAction();

    Phonon::MediaObject* sound() const {return m_sound;}
    void setSound(Phonon::MediaObject* sound);

    quint64 durationMSecs() const;
    AudioAction* copy() const;

  private:
    quint64 m_delayMSecs;
    Phonon::MediaObject* m_sound;
  };
}
#endif
