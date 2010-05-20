#include "Experiment.h"

namespace kex
{
  void Experiment::updateFromTemplate(const OutputComponent::SharedPointer t)
  {
    Q_CHECK_PTR(t);
    
    QSharedPointer<const Experiment> exp = t.objectCast<const Experiment>();
    // ensure this is an experiment type component
    Q_CHECK_PTR(exp);
    AggregateComponent::updateFromTemplate(t);
    
    // Experiments have a unique instructions field
    
    if (exp->instructions() != _instructions)
    {
      if (_instructions.isEmpty())
      {
        _instructions = exp->instructions();
      }
    }
  }
}