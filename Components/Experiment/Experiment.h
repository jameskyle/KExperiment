#ifndef EXPERIMENT_H
#define EXPERIMENT_H
#include <QString>
#include <QObject>

#include "Components/Component.h"
namespace kex
{
  class Experiment : public Component  {
    Q_OBJECT
    Q_PROPERTY(QString instructions READ instructions WRITE setInstructions)
    
  public:
    Experiment(QObject *parent = 0);
    ~Experiment() {}
    
    const QString instructions() const {return _instructions;}
    void setInstructions(const QString& inst) {_instructions = inst;}
    
    void updateFromTemplate(const Component::Pointer t);
    void updateFromTemplate(const Component::SharedPointer t);
  private:
    QString _instructions;
  public slots:
    void begin() {}
    void abort() {}
  };
}
#endif