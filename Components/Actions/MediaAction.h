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
      explicit MediaAction(Phonon::MediaObject* mediaObject,
                           QObject *parent = 0,
                           const QString& name=QString(""),
                           const QString& description=QString(""),
                           const QString& label=QString(""),
                           const QSet<QString>& categories=QSet<QString>(),
                           quint64 delayMSecs=0);

      ~MediaAction();

    Phonon::MediaObject* mediaObject() const {return m_mediaObject;}
    void setMediaObject(Phonon::MediaObject* mediaObject);
    quint64 durationMSecs() const;
    quint64 delayMSecs() const {return m_delayMSecs;}
    void setDelayMSecs(quint64 delayMSecs) {m_delayMSecs = delayMSecs;}

    MediaAction* copy() const;
    bool operator==(const Component& other) const;
    bool operator!=(const Component& other) const;

  private:
    void setComponentType();

    Phonon::MediaObject* m_mediaObject;
    quint64 m_delayMSecs;
  };

  typedef MediaAction AudioAction;
  typedef MediaAction VideoAction;
}
#endif // MEDIAACTION_H
