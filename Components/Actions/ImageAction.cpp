#include "ImageAction.h"

namespace kex
{
  ImageAction::ImageAction (QObject *parent,
                const QString& name,
                const QString& description,
                const QString& label,
                const QSet<QString> categories,
                const QIcon& icon,
                quint64 durationMSecs,
                int delayMSecs,
                const QImage& image,
                qint32 xoffset,
                qint32 yoffset,
                const Component::ComponentPositions& position
                ) :
  Component(parent, name, description, label, categories, icon),
  m_durationMSecs(durationMSecs),
  m_delayMSecs(delayMSecs),
  m_image(image),
  m_xoffset(xoffset),
  m_yoffset(yoffset),
  m_position(position)
  {
  }

  ImageAction::~ImageAction()
  {
  }


  ImageAction* ImageAction::copy() const
  {
    ImageAction* action = new ImageAction(parent(), name(), description(),
                                          label(), categories(), icon(),
                                          durationMSecs(), delayMSecs(),
                                          image(), xoffset(), yoffset(),
                                          position());

    return action;
  }
}
