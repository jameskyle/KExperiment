#include "AggregateComponent.h"
#include "Components/Event/Event.h"
namespace kex
{
  AggregateComponent::AggregateComponent(QObject *parent)  : 
    OutputComponent(parent),
    _childComponents()
  {
  
  }
  
  AggregateComponent::~AggregateComponent()
  {
  }
  
  quint32 AggregateComponent::durationMSecs() const
  {
    quint32 duration(0);
    
    QListIterator<SharedPointer> it(_childComponents);
    SharedPointer t;
    
    while (it.hasNext())
    {
      t = it.next();
      duration += t->durationMSecs();
    }
    return duration;
  }
  
  QList<OutputComponent::SharedPointer>
  AggregateComponent::childComponents() const
  {
    return _childComponents;
  }
    
  void AggregateComponent::appendChild(OutputComponent* child)
  {
    ComponentList::Node* node(0);
    _childComponents.append(child);
  }
  
  void AggregateComponent::removeChild(int index)
  {
    OutputComponent::SharedPointer ptr = _childComponents[index];
    _childComponents.removeAt(index);
    ptr.setListIndex(-1);
  }
  
  void AggregateComponent::insertChild(int index, 
                                       SharedPointer child)
  {
    _childComponents.insert(index, child);
    child.setListIndex(index);
//    child->setParentComponent(this);
  }

  bool AggregateComponent::hasChildren() const
  {
    bool success(false);
    
    if (_childComponents.count() > 0)
    {
      success = true;
    }
    
    return success;
  }

  int AggregateComponent::numChildren() const
  {
    return _childComponents.count();
  }
  
  OutputComponent::SharedPointer AggregateComponent::child(int row) const
  {
    SharedPointer p(0);
    if (_childComponents.count() >= 0 && row < _childComponents.count())
    {
      p = _childComponents[row];
    }
    
    return p;
  }
  
  void AggregateComponent::updateFromTemplate(const SharedPointer t)
  {
    OutputComponent::updateFromTemplate(t);
    
    QSharedPointer<AggregateComponent> p(t.objectCast<AggregateComponent>());
    
    Q_CHECK_PTR(p);
    
    if (p->numChildren() > 0)
    {
      _childComponents = p->childComponents();
    }
  }


}
