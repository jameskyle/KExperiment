#ifndef EXPERIMENT_H
#define EXPERIMENT_H
#include <QString>
#include <QObject>

#include "Components/AggregateComponent.h"
namespace kex
{
  class Experiment : public AggregateComponent  {
    Q_OBJECT
  public:
    Experiment(QObject *parent = 0) : AggregateComponent(parent) {}
    ~Experiment() {}
    
  public slots:
    void begin() {}
    void abort() {}
  };
}
#endif