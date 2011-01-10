#ifndef MEDIAACTION_H
#define MEDIAACTION_H

#include <Phonon/MediaObject>
#include <QDebug>

#include <Components/Component.h>

namespace kex
{
  class MediaAction : public Component
  {
    Q_OBJECT
    Q_PROPERTY(QString source   READ source        WRITE setSource)
    Q_PROPERTY(quint64 delay    READ delayMSecs    WRITE setDelayMSecs)
    Q_PROPERTY(quint64 duration READ durationMSecs)

  public:
    typedef MediaAction* Pointer;
    explicit MediaAction(QObject             *parent          = 0,
                         Component::Pointer   parentComponent = 0,
                         const QString&       name            = QString(""),
                         const QString&       description     = QString(""),
                         const QString&       label           = QString(""),
                         const QSet<QString>& categories      = QSet<QString>(),
                         quint64              delayMSecs      = 0,
                         const QString&       source          = QString(""));

      ~MediaAction();
    QString source() const;
    void setSource(const QString& sourceFile);

    const Phonon::MediaObject& mediaObject() const {return m_mediaObject;}

    quint64 durationMSecs() const;
    quint64 delayMSecs() const {return m_delayMSecs;}
    void setDelayMSecs(quint64 delayMSecs) {m_delayMSecs = delayMSecs;}

    Pointer clone() const;
    bool operator==(const Component& other) const;
    bool operator!=(const Component& other) const;

  private:
    void setComponentType();

    Phonon::MediaObject m_mediaObject;
    quint64 m_delayMSecs;
  };

  typedef MediaAction AudioAction;
  typedef MediaAction VideoAction;
}
#endif // MEDIAACTION_H
