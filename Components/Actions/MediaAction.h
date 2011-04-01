#ifndef MEDIAACTION_H
#define MEDIAACTION_H

#include <Phonon/MediaObject>
#include <QDebug>
#include <QFile>

#include "Components/Component.h"
#include "Common/Logger.h"
#include "Components/ComponentExceptions.h"

namespace kex
{
  class MediaAction : public Component
  {
    Q_OBJECT
    Q_PROPERTY(QString source   READ source        WRITE setSource)
    Q_PROPERTY(qint64 delay    READ delayMSecs    WRITE setDelayMSecs)
    Q_PROPERTY(qint64 duration READ durationMSecs)

  public:
    typedef MediaAction* Pointer;
    explicit MediaAction(QObject             *parent          = 0,
                         Component::Pointer   parentComponent = 0,
                         const QString&       name            = QString(""),
                         const QString&       description     = QString(""),
                         const QString&       label           = QString(""),
                         const QSet<QString>& categories      = QSet<QString>(),
                         qint64               delayMSecs      = 0,
                         const QString&       source          = QString(""));

    ~MediaAction();
    QString source() const;
    void setSource(const QString& sourceFile);

    /** \brief String representation of the MediaAction object.
     *
     * \author James A. Kyle KSpace, LLC
     * \date 31/03/2011
     * \return Qstring representing the MediaAction instance
    **/
    const QString toString() const;

    qint64 durationMSecs() const;
    qint64 delayMSecs() const {return m_delayMSecs;}
    void setDelayMSecs(qint64 delayMSecs);

    Pointer clone() const;
    bool operator==(const Component& other) const;
    bool operator!=(const Component& other) const;

  private slots:
    void updateDurationMSecs(qint64 duration);

  private:
    void setComponentType();

    Phonon::MediaObject m_mediaObject;
    qint64 m_delayMSecs;
    qint64 m_durationMSecs;
  };
}
#endif // MEDIAACTION_H
