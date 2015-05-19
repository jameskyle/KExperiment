#include "MediaAction.h"

namespace kex
{

  MediaAction::MediaAction(QObject *parent,
                           Component::Pointer parentComponent,
                           const QString& name,
                           const QString& description,
                           const QString& label,
                           const QSet<QString>& categories,
                           qint64 delayMSecs,
                           const QString& source) :
    Component(parent,  parentComponent, name, description, label, categories),
    m_mediaObject(),
    m_delayMSecs(delayMSecs),
    m_durationMSecs(0)
  {
    if(source.size() > 0 &&  !QFile::exists(source)) {
      Logger& logger = Logger::instance();
      QString msg("Source for %1 does not exist: %2");
      logger.log(msg.arg(name).arg(source), this, Logger::WarningLogLevel);
    }

    if(!source.isEmpty()) {
      Phonon::MediaSource s(source);
      m_mediaObject.setCurrentSource(s);
    }

    setComponentType();

    // Connect to the mediaobjects currentTimeChanged signal

    connect(&m_mediaObject, SIGNAL(totalTimeChanged(qint64)),
            this, SLOT(updateDurationMSecs(qint64)));

  }

  MediaAction::~MediaAction()
  {
  }

  qint64 MediaAction::durationMSecs() const
  {
    return m_durationMSecs;
  }

  void MediaAction::setComponentType()
  {
    // invalid types
    int t = (Phonon::MediaSource::Invalid |
                                   Phonon::MediaSource::Empty);

    if (m_mediaObject.currentSource().type() & t) {
      m_componentType = Component::MediaActionType;
    } else {
      if(m_mediaObject.hasVideo())
        m_componentType = Component::VideoActionType;
      else
        m_componentType = Component::AudioActionType;
    }

  }

  MediaAction::Pointer MediaAction::clone() const
  {
    QString fileName = m_mediaObject.currentSource().fileName();

    Pointer action = new MediaAction(parent(),     parentComponent(),
                                     name(),       description(),
                                     label(),      categories(),
                                     delayMSecs(), fileName);

    return action;
  }

  bool MediaAction::operator==(const Component& other) const
  {
    const MediaAction* derived = qobject_cast<const MediaAction*>(&other);

    QString this_file = m_mediaObject.currentSource().fileName();
    QString other_file = derived->m_mediaObject.currentSource().fileName();

    bool equal = (derived &&
      Component::operator==(other) &&
      delayMSecs() == derived->delayMSecs()  &&
      this_file    == other_file);

    return equal;
  }

  bool MediaAction::operator!=(const Component& other) const
  {
    return !(*this == other);
  }

  QString MediaAction::source() const
  {
    return m_mediaObject.currentSource().fileName();
  }

  void MediaAction::setSource(const QString& sourceFile)
  {
    if(!QFile::exists(sourceFile)) {
      Logger& logger = Logger::instance();
      QString msg("Source for %1 does not exist: %2");
      QString n = name();

      if (n.size() == 0) {n = "Unknown";}

      logger.log(msg.arg(n).arg(sourceFile), this, Logger::WarningLogLevel);
    }

    Phonon::MediaSource source(sourceFile.trimmed());
    // BUG: For some reason, setting the source of a media object causes a leak
    //      Should look into this.
    m_mediaObject.setCurrentSource(source);
    setComponentType();
  }

  void MediaAction::updateDurationMSecs(qint64 duration)
  {
    m_durationMSecs = duration;
  }

  void MediaAction::setDelayMSecs(qint64 delayMSecs)
  {
    if (delayMSecs < 0) {
      QString msg = "Negative value";
      InvalidDelayValue exc(msg.toAscii());
      throw(exc);
    } else if (delayMSecs > Component::MAX_DURATION) {
      QString msg = "Value exceeds MAX_DURATION";
      InvalidDelayValue exc(msg.toAscii());
      throw(exc);
    }

    m_delayMSecs = delayMSecs;
  }

  const QString MediaAction::toString() const
  {
    QString output(Component::toString());
    output.append("\nDurationMSecs: %1");
    output.append("\nDelayMSecs: %2");
    output.append("\nSource: %3");

    return output.arg(durationMSecs()).arg(delayMSecs()).arg(source());
  }
}
