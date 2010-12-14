#include "Experiment.h"

namespace kex
{
  Experiment::Experiment(QObject *parent) :
    Component(parent), _instructions()
  {
  }

  void Experiment::updateFromTemplate(const Component::SharedPointer t)
  {
    Q_CHECK_PTR(t);

    QSharedPointer<const Experiment> exp = t.objectCast<const Experiment>();
    // ensure this is an experiment type component
    Q_CHECK_PTR(exp);
//    Component::updateFromTemplate(t);

    // Experiments have a unique instructions field

//    if (exp->instructions() != _instructions)
//    {
//      if (_instructions.isEmpty())
//      {
//        _instructions = exp->instructions();
//      }
//    }
  }
}
