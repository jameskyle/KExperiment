#ifndef TEXTACTION_H
#define TEXTACTION_H

#include "Components/OutputComponent.h"
#include "Action.h"

namespace kex
{
  class TextAction : public OutputComponent, public Action
  {
    Q_OBJECT
  public:
    TextAction(QObject *parent = 0);
    ~TextAction();

    const QString text() const {return _text;}
    void setText(const QString& text) { _text = text;}
    
  private:
    QString _text;
  public slots:
    void begin();
    void abort();
    };
}
#endif