#ifndef RESTACTION_H
#define RESTACTION_H

#include "Components/OutputComponent.h"
#include "Action.h"

namespace kex
{
  class RestAction : public OutputComponent, public Action
  {
    Q_OBJECT
  public:
    RestAction(QObject *parent = 0);
    ~RestAction();

  public slots:
    void begin();
    void abort();
    };
}
#endif