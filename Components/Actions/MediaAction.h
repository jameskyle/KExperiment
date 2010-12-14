#ifndef MEDIAACTION_H
#define MEDIAACTION_H

#include <Phonon/MediaObject>

#include <Components/Component.h>

namespace kex
{
  class MediaAction : public Component
  {
      Q_OBJECT
  public:
      explicit MediaAction(QObject *parent = 0,
                const QString& name=QString(""),
                const QString& description=QString(""),
                const QString& label=QString(""),
                const QSet<QString>& categories=QSet<QString>(),
                const QIcon& icon=QIcon(Component::DEFAULT_ICON),
                quint64 delayMSecs=0,
                Phonon::MediaObject* mediaObject=0);

      ~MediaAction();

    Phonon::MediaObject* mediaObject() const {return m_mediaObject;}

    quint64 durationMSecs() const;
    MediaAction* copy() const;

  private:
    quint64 m_delayMSecs;
    Phonon::MediaObject* m_mediaObject;
  };

  typedef MediaAction AudioAction;
  typedef MediaAction VideoAction;
}
#endif // MEDIAACTION_H
