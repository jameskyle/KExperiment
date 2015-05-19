#include "AggregateComponent.h"
#include "Components/Event/Event.h"
namespace kex
{
  AggregateComponent::AggregateComponent(QObject *parent)  : 
    OutputComponent(parent)
  {
  
  }
  
  AggregateComponent::~AggregateComponent()
  {
  }
    
  void AggregateComponent::updateFromTemplate(const SharedPointer t)
  {
    OutputComponent::updateFromTemplate(t);
    
    QSharedPointer<AggregateComponent> p(t.objectCast<AggregateComponent>());
    
    Q_CHECK_PTR(p);
  }


}
