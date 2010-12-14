#include "TextAction.h"

namespace kex
{
  /**
   * TODO
   */
  TextAction::TextAction (QObject *parent,
               const QString& name,
               const QString& description,
               const QString& label,
               const QSet<QString>& categories,
               const QIcon& icon,
               quint64 durationMSecs,
               quint64 delayMSecs,
               const QString& text,
               const QString& family,
               int pointSize,
               const QColor& foreground,
               const QColor& background,
               qint32 xoffset,
               qint32 yoffset,
               const Component::ComponentPositions& position) :
  Component(parent, name, description, label, categories, icon),
  m_durationMSecs(durationMSecs),
  m_delayMSecs(delayMSecs),
  m_text(text),
  m_foreground(foreground),
  m_background(background),
  m_xoffset(xoffset),
  m_yoffset(yoffset),
  m_position(position),
  m_font(family, pointSize)
  {
//    m_text.prepare(0, m_font);
  }

  TextAction* TextAction::copy() const
  {
    TextAction* action = new TextAction(parent(), name(), description(),
                                        label(), categories(), icon(),
                                        durationMSecs(), delayMSecs(),
                                        m_text.text(), m_font.family(),
                                        m_font.pointSize(), foreground(),
                                        background(), xoffset(), yoffset(),
                                        position());
    return action;
  }
}
