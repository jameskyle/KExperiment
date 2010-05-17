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
    
    const QString instructions() const {return _instructions;}
    void setInstructions(const QString& inst) {_instructions = inst;}
    
  private:
    QString _instructions;
  public slots:
    void begin() {}
    void abort() {}
  };
}
#endif