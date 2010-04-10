#ifndef RESTACTION
#define RESTACTION
#include "OutputAction.h"

namespace kex
{
  class RestAction : public OutputAction
  {
    Q_OBJECT
    public:
      RestAction(QObject *parent = 0);
      ~RestAction();
    
      void log(QString& msg);
            
    public slots:
      void begin();
      void abort();
    };
}
#endif