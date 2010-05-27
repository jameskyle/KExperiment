#include "ComponentList.h"

namespace kex {
  ComponentList::ComponentList() :
    ActionComponents(*this),
    _count(0),
    _front(0),
    _back(0)
  {
    
  }
  ComponentList::~ComponentList() 
  {
  }

  ComponentList& ComponentList::instance()
  {
    static ComponentList componentList;
    return componentList;
  }

  ComponentList::iterator 
  ComponentList::find(const Node* node, const_iterator start, 
                      const_iterator stop) const
  {
    iterator found;
    
    while (start != stop)
    {
      if (start == node)
      {
        found = node;
        break;
      }
      ++start;
    }
    
    return found;
  }
  
  void ComponentList::append(Node* node)
  {
    insertAfter(node, _back);
  }
  
  void ComponentList::prepend(Node* node)
  {
    insertBefore(node, _front);
  }
  
  void ComponentList::insertBefore(Node* nextNode, Node* node)
  {
    node->_previous = nextNode->previous();
    node->setNext(nextNode);
    nextNode->setPrevious(node);
    
    // if the nextNode was _front node, we set node to the new _front
    if (!node->previous())
    {
      _front = node;
    } else
    {
      node->previous()->setNext(node);
    }
    
    ++_count;
  }

  void ComponentList::insertAfter(Node* prevNode, Node* node)
  {
    node->setPrevious(prevNode);
    node->setNext(prevNode->next());
    prevNode->setNext(node);
    
    if (!node->next())
    {
      _back = node;
    } else
    {
      node->next()->setPrevious(node);
    }
    
    ++_count;
  }
  
  bool ComponentList::remove(Node* comp)
  {
    bool found(false);
    Node* current = _front;
    
    while (current)
    {
      if (current == comp)
      {
        found = true;
        Node* prev = current->previous();
        Node* next = current->next();
    
        prev->setNext(next);
        next->setPrevious(prev);
        
        current->setNext(0);
        current->setPrevious(0);
        break;
      }
      current = current->next();
    }
    
    
    return found;
  }
  
  void ComponentList::append(OutputComponent* comp)
  {
    Node::Pointer p(comp);
    Node* node = new Node(p);
    append(node);
  }
  
  bool ComponentList::sortComponentList(Node* c1, Node* c2)
  {
    return (c1->component()->name() < c2->component()->name());
  }
  
  ComponentList::iterator ComponentList::begin()
  {
    return iterator(_front);
  }
  
  ComponentList::iterator ComponentList::end()
  {
    return iterator(_back);
  }
  
  void ComponentList::prependChild(Node* parent, Node* child)
  {
    insertBefore(parent->child(), child);
  }
  
  ComponentList::Node::Node(Pointer comp) : 
  _component(comp),
  _position(-1),
  _parentComponent(0),
  _previous(0),
  _next(0),
  _child(0),
  _lastChild(0)
  {
    
  }
  
  bool ComponentList::Node::isNull() const
  {
    bool null(true);
    
    if (_component)
    {
      null = false;
    }
    return null;
  }
  
  ComponentList::Node::operator bool() const
  {
    return !(isNull());
  }
  
  bool ComponentList::Node::operator!() const
  {
    return isNull();
  }
  
  bool ComponentList::Node::hasNext() const
  {
    bool n(false);
    
    if (_next)
    {
      n = true;
    }
    
    return n;
  }
  
  bool ComponentList::Node::hasChildren() const
  {
    bool childFound(false);
    if (_childList->count() > 0)
    {
      childFound = true;
    }
    
    return childFound;
  }

  
}
