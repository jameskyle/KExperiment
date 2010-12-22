#include "TextAction.h"

namespace kex
{
  TextAction::TextAction (QObject *parent,
                          Component::Pointer parentComponent,
                          const QString& name,
                          const QString& description,
                          const QString& label,
                          const QSet<QString>& categories,
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
  Component(parent, parentComponent, name, description, label, categories),
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
    m_componentType = Component::TextActionType;
//    m_text.prepare(0, m_font);
  }

  TextAction::~TextAction() {}

  TextAction::Pointer TextAction::clone() const
  {
    Pointer action = new TextAction(parent(),           parentComponent(),
                                    name(),             description(),
                                    label(),            categories(),
                                    durationMSecs(),    delayMSecs(),
                                    m_text.text(),      m_font.family(),
                                    m_font.pointSize(), foreground(),
                                    background(),       xoffset(),
                                    yoffset(),          position());
    return action;
  }

  bool TextAction::operator==(const Component& other) const
  {

    const TextAction* derived = qobject_cast<const TextAction*>(&other);
    bool equal = (derived &&
                  Component::operator==(other)                &&
                  durationMSecs() == derived->durationMSecs() &&
                  delayMSecs()    == derived->delayMSecs()    &&
                  m_text          == derived->m_text          &&
                  font()          == derived->font()          &&
                  foreground()    == derived->foreground()    &&
                  background()    == derived->background()    &&
                  xoffset()       == derived->xoffset()       &&
                  yoffset()       == derived->yoffset()       &&
                  position()      == derived->position());

    return equal;
  }

  bool TextAction::operator!=(const Component& other) const
  {
    return !(*this == other);
  }
}
