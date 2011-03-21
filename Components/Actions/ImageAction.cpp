#include "ImageAction.h"

namespace kex
{
  ImageAction::ImageAction (QObject *parent,
                            Component::Pointer parentComponent,
                            const QString& name,
                            const QString& description,
                            const QString& label,
                            const QSet<QString> categories,
                            quint64 durationMSecs,
                            quint64 delayMSecs,
                            const QString& imagePath,
                            qint32 xoffset,
                            qint32 yoffset,
                            const Component::ComponentPositions& position) :
  Component(parent, parentComponent, name, description, label, categories),
  m_durationMSecs(durationMSecs),
  m_delayMSecs(delayMSecs),
  m_image(imagePath),
  m_imagePath(imagePath),
  m_xoffset(xoffset),
  m_yoffset(yoffset),
  m_position(position)
  {
    m_componentType = Component::ImageActionType;
  }

  ImageAction::~ImageAction()
  {
  }


  ImageAction::Pointer ImageAction::clone() const
  {
    Pointer action = new ImageAction(parent(),        parentComponent(),
                                     name(),          description(),
                                     label(),         categories(),
                                     durationMSecs(), delayMSecs(),
                                     imagePath(),         xoffset(),
                                     yoffset(),       position());

    return action;
  }

  bool ImageAction::operator==(const Component& other) const
  {

    const ImageAction* derived = qobject_cast<const ImageAction*>(&other);
    bool equal = (derived &&
                  Component::operator==(other) &&
                  durationMSecs() == derived->durationMSecs(),
                  image()         == derived->image()         &&
                  xoffset()       == derived->xoffset()       &&
                  yoffset()       == derived->yoffset()       &&
                  position()      == derived->position());

    return equal;
  }

  bool ImageAction::operator!=(const Component& other) const
  {
    return !(*this == other);
  }

  void ImageAction::setImagePath(const QString& imagePath)
  {
    m_imagePath = imagePath;
    m_image.load(m_imagePath);
  }

  const QString ImageAction::toString() const
  {
    QString output(Component::toString());
    output.append("\nDurationMSecs: %1");
    output.append("\nDelayMSecs: %2");
    output.append("\nxoffset: %3");
    output.append("\nyoffset: %4");
    output.append("\nimagePath: %5");

    return output.arg(durationMSecs()).arg(delayMSecs()).arg(xoffset()).
                  arg(yoffset()).arg(imagePath());
  }

  void ImageAction::setDurationMSecs(quint64 durationMSecs)
  {
    if (durationMSecs > Component::MAX_DURATION) {
      QString msg;
      msg = "ImageAction::setDurationMSecs argument exceeds maximum allowed duration";

      InvalidDurationValue exc(msg.toAscii());
      throw  exc;

    } else if(durationMSecs < 0) {
      QString msg;
      msg = "ImageAction::setDurationMSecs durationMSecs must be positive";

      InvalidDurationValue exc(msg.toAscii());
      throw exc;
    }

    m_durationMSecs = durationMSecs;

  }
}
