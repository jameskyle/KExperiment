#include "ImageAction.h"

namespace kex
{
  ImageAction::ImageAction (QObject *parent,
                const QString& name,
                const QString& description,
                const QString& label,
                const QSet<QString> categories,
                quint64 durationMSecs,
                quint64 delayMSecs,
                const QImage& image,
                qint32 xoffset,
                qint32 yoffset,
                const Component::ComponentPositions& position
                ) :
  Component(parent, name, description, label, categories),
  m_durationMSecs(durationMSecs),
  m_delayMSecs(delayMSecs),
  m_image(image),
  m_xoffset(xoffset),
  m_yoffset(yoffset),
  m_position(position)
  {
    m_componentType = Component::ImageActionType;
  }

  ImageAction::~ImageAction()
  {
  }


  ImageAction* ImageAction::copy() const
  {
    ImageAction* action = new ImageAction(parent(), name(), description(),
                                          label(), categories(),
                                          durationMSecs(), delayMSecs(),
                                          image(), xoffset(), yoffset(),
                                          position());

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
}
