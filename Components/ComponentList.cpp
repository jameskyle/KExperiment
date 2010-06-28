#include "ComponentList.h"

namespace kex {
/*  bool ComponentList::sortComponentList(Node::Pointer c1, Node::Pointer c2)
  {
    return (c1->component()->name() < c2->component()->name());
  }*/
  
  Node::Node(OutputComponent::SharedPointer comp) : 
  _component(comp),
  _durationMSecs(0),
  _parent(0),
  _previous(0),
  _next(0),
  _child(0)
  {
    if (comp->componentType() & OutputComponent::ActionType)
    {
      Action *action = qobject_cast<Action *>(comp.data());
      
      if (action)
      {
        _durationMSecs = action->durationMSecs();
      }
    }
  }
  
  Node::Pointer Node::front() const 
  {
    Pointer p;

    if (!_previous)
    {
      p = const_cast<Pointer>(this);
    } else {
      p = _previous->front();
    }

    return p;
  }

  Node::Pointer Node::back() const
  {
    Pointer p;
    if (!_next)
    {
      p = const_cast<Pointer>(this);
    } else {
      p = _next->back();
    }
    return p;
  }
  
  Node::Pointer Node::lastChild() const
  {
    Pointer p;

    if (_child)
    {
      p = _child->back();
    }

    return p;
  }

  bool Node::isNull() const
  {
    bool null(true);
    
    if (!_component.isNull())
    {
      null = false;
    }
    return null;
  }
  
  Node::operator bool() const
  {
    return !(isNull());
  }
  
  bool Node::operator==(const Node& other)
  {
    return (this == &other);
  }
  
  void Node::append(Node::Pointer node)
  {
    if (!_next)
    {
      _next = node;
    } else {
      _next->append(node);
    }
  }

  void Node::prepend(Node::Pointer node)
  {
    if (!_previous)
    {
      _previous = node;

    } else {
      _previous->prepend(node);
    }
  }

  void Node::appendChild(Node::Pointer node)
  {
    if (!_child)
    {
      _child = node;
    } else {
      _child->append(node);
    }
  }
  
  Node::iterator Node::find(Pointer node) const
  {
    iterator b(_child);
    iterator e(end());

    while(*b != node && b != e)
    {
      ++b;
    }

    return b;
  }

  void Node::remove(Node::Pointer node)
  {
    iterator it(find(node));

    if (it != end())
    {
      Pointer prev = (*it)->previous();
      Pointer next = (*it)->next();
      
      prev->setNext(next);
      next->setPrevious(prev);

      (*it)->setPrevious(0);
      (*it)->setNext(0);
      (*it)->setParent(0);
    }
  }

  bool Node::operator!=(const Node& other)
  {
    return !(*this == other);
  }
  
  bool Node::operator!() const
  {
    return isNull();
  }
  
  bool Node::hasNext() const
  {
    bool n(false);
    
    if (_next)
    {
      n = true;
    }
    
    return n;
  }
  
  bool Node::hasChildren() const
  {
    bool childFound(false);
    if (child())
    {
      childFound = true;
    }
    
    return childFound;
  }

  int Node::position() const
  {
    int count(0);
    const_iterator it(this);
    
    while ((*it)->hasPrevious())
    {
      ++count;
      --it;
    }
    
    return count;
  }
  
  void Node::setNext(Pointer node) 
  {
    Q_ASSERT(!node->next());
    Q_ASSERT(!node->previous());
    Q_ASSERT(!node->parent());

    node->setParent(_parent);

    if (_next)
    {
      Pointer prev = _next->previous();

      node->setNext(_next);
      node->setPrevious(prev); 
      _next->setPrevious(node);
      _next = node;

    } else {
      _next = node;
    }
  }

  int Node::numChildren() const
  {
    int count(0);
    
    iterator it(_child);

    while (it != end())
    {
      ++it;
      ++count;
    }

    return count;
  }
  
}
