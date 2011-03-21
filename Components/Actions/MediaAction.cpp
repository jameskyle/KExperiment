#include "MediaAction.h"

namespace kex
{

  MediaAction::MediaAction(QObject *parent,
                           Component::Pointer parentComponent,
                           const QString& name,
                           const QString& description,
                           const QString& label,
                           const QSet<QString>& categories,
                           quint64 delayMSecs,
                           const QString& source) :
  Component(parent,  parentComponent, name, description, label, categories),
  m_mediaObject(),
  m_delayMSecs(delayMSecs)
  {
    if(source.size() > 0 &&  !QFile::exists(source)) {
      Logger& logger = Logger::instance();
      QString msg("Source for %1 does not exist: %2");
      logger.log(msg.arg(name).arg(source), this, Logger::WarningLogLevel);
    }

    Phonon::MediaSource s(source);
    m_mediaObject.setCurrentSource(s);
    setComponentType();
  }

  MediaAction::~MediaAction()
  {
  }

  quint64 MediaAction::durationMSecs() const
  {
    return m_mediaObject.totalTime();
  }

  void MediaAction::setComponentType()
  {
    if(m_mediaObject.hasVideo())
      m_componentType = Component::VideoActionType;
    else
      m_componentType = Component::AudioActionType;
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
    bool equal = (derived &&
      Component::operator==(other) &&
      delayMSecs()                 == derived->delayMSecs()  &&
      mediaObject().currentSource() == derived->mediaObject().currentSource());

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
      logger.log("got here");
    }

    Phonon::MediaSource source(sourceFile.trimmed());
    m_mediaObject.setCurrentSource(source);
    setComponentType();
  }
}
