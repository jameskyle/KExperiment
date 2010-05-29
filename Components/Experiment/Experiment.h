#ifndef EXPERIMENT_H
#define EXPERIMENT_H
#include <QString>
#include <QObject>

#include "Components/OutputComponent.h"
namespace kex
{
  class Experiment : public OutputComponent  {
    Q_OBJECT
    Q_PROPERTY(QString instructions READ instructions WRITE setInstructions)
    
  public:
    Experiment(QObject *parent = 0) : OutputComponent(parent) {}
    ~Experiment() {}
    
    const QString instructions() const {return _instructions;}
    void setInstructions(const QString& inst) {_instructions = inst;}
    
    void updateFromTemplate(const OutputComponent::Pointer t);
    void updateFromTemplate(const OutputComponent::SharedPointer t);
  private:
    QString _instructions;
  public slots:
    void begin() {}
    void abort() {}
  };
}
#endif