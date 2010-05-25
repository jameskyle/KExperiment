#include "ComponentList.h"

namespace kex {
  ComponentList::ComponentList() :
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

  ComponentList::Node* 
  ComponentList::find(const Node& node) const
  {
    Node* current = _front;
    Node* foundNode(0);
    
    while (current->next())
    {
      if (node == *current->next())
      {
        foundNode = current;
      }
    }
    return foundNode;
  }

  void ComponentList::append(Node* node)
  {
    insertAfter(node, _back);
  }
  
  void ComponentList::prepend(Node* node)
  {
    insertBefore(node, _front);
  }
  
  void ComponentList::insertBefore(Node* node, Node* nextNode)
  {
    node->setPrevious(nextNode->previous());
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

  void ComponentList::insertAfter(Node* node, Node* prevNode)
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

  const ComponentList::ComponentQList 
  ComponentList::filter(OutputComponent::ComponentTypes types) const
  {
    Node* current = _front;
    
    ComponentQList  filteredList;

    while (current->hasNext())
    {
      if (current->component()->componentType() & types)
      {
        filteredList.append(current);
      }
    }
    
    qSort(filteredList.begin(), filteredList.end(), sortComponentList);
    
    return filteredList;
  }

  bool ComponentList::sortComponentList(Node* c1, Node* c2)
  {
    return (c1->component()->name() < c2->component()->name());
  }
  
  ComponentList::Node::Node(Pointer comp) : 
  _component(comp),
  _position(-1),
  _root(0),
  _previous(0),
  _next(0),
  _child(0)
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
  
}
