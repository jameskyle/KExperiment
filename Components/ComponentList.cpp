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
  
  const ComponentList::ComponentList& const_instance()
  {
    return ComponentList::instance();
  }

  
  void ComponentList::insert(Node* prevNode, Node* node)
  {
    Q_CHECK_PTR(prevNode);
    Q_CHECK_PTR(node);
    // ensure the node is not a member of another list, see clone()
    Q_ASSERT(!node->parentComponent() && !node->next() && !node->previous());
    
    insertAfter(prevNode, node);
  }
  
  void ComponentList::insert(iterator it, Node* node)
  {
    Q_CHECK_PTR(node);
    // ensure the node is not a member of another list, see clone()
    Q_ASSERT(!node->parentComponent() && !node->next() && !node->previous());
    insertAfter(&(*it), node);
  }
  
  void ComponentList::clone(Node* prevNode, Node* node)
  {
    Q_CHECK_PTR(prevNode);
    Q_CHECK_PTR(node);
    // this method does a shallow copy of the node, then assigns approprate 
    // links
    Node *newNode = new Node(*node);
    newNode->clearPositionalData();
    insertAfter(prevNode, newNode);
    newNode->updateParent();
  }
  
  ComponentList::iterator 
  ComponentList::find(const Node* node, iterator start, 
                      iterator stop) const
  {
    iterator found;
    
    while (start != stop)
    {
      if (*start == *node)
      {
        found = start;
        break;
      }
      ++start;
    }
    
    return found;
  }

  ComponentList::iterator
  ComponentList::findByName(const QString& name) const
  {
    iterator it = begin();
    
    while (it != end())
    {
      if (it->component()->name() == name)
      {
        break;
      }
      ++it;
    }
    
    return it;
  }
  
  void ComponentList::append(Node* node, Node* parent)
  {
    Q_CHECK_PTR(node);
    Q_ASSERT(!node->previous() && !node->next() && !node->parentComponent());
    
    if (!parent) // append to main list
    {
      if (_back)
      {
        // insert after the last node, insertAfter updates list appropriately
        insertAfter(_back, node);
      } else
      {
        _front = _back = node;
        // update list about new state
        updateList(node);
      }
      
    } else 
    {
      if (!parent->child())
      {
        parent->setChild(node);
        
      } else
      {
        insertAfter(parent->lastChild(), node);
      }
      node->updateParent();
    }
  }
  
  void ComponentList::append(OutputComponent* comp, Node* parent)
  {
    Node::Pointer p(comp);
    Node* node = new Node(p);
    append(node, parent);
  }
  
  void ComponentList::prepend(Node* node, Node* parent)
  {
    Q_CHECK_PTR(node);
    Q_ASSERT(!node->previous() && !node->next() && !node->parentComponent());
    
    if (!parent) // top level/main list
    {
      if (_front)
      {
        // insertBefore updates list appropriately
        insertBefore(_front, node);
      } else 
      {
        _front = _back = node;
        updateList(node);
        node->updateParent();
      }
    } else
    {
      if (!parent->child())
      {
        parent->setChild(node);
      } else
      {
        insertBefore(parent->child(), node);
      }

      node->updateParent();
    }

    
   }
  
  void ComponentList::prepend(OutputComponent* comp, Node* parent)
  {
    Node::Pointer p(comp);
    Node* node = new Node(p);
    prepend(node, parent);
  }
  
  void ComponentList::insertBefore(Node* nextNode, Node* node)
  {
    Q_CHECK_PTR(nextNode);
    Q_CHECK_PTR(node);
    Q_ASSERT(!node->previous() && !node->next() && !node->parentComponent());
    
    node->setPrevious(nextNode->previous());
    node->setNext(nextNode);
    nextNode->setPrevious(node);
    
    // takes parent of other siblings.
    node->setParentComponent(nextNode->parentComponent());
    
    // update the parent node if we are the last child
    node->updateParent();
    
    // update the list if this is a new _front or _back node
    updateList(node);
    
    ++_count;
  }

  void ComponentList::insertAfter(Node* prevNode, Node* node)
  {
    Q_CHECK_PTR(prevNode);
    Q_CHECK_PTR(node);
    Q_ASSERT(!node->parentComponent() && !node->next() && !node->previous());
    
    node->setPrevious(prevNode);
    node->setNext(prevNode->next());
    prevNode->setNext(node);
    
    // takes parent of siblings
    node->setParentComponent(prevNode->parentComponent());
    
    // update parent's lastChild if this node is the new last child
    node->updateParent();
    
    // update the list itself if this is the new _front or _back
    updateList(node);
     
    ++_count;
  }
    
  bool ComponentList::remove(Node* comp)
  {
    bool found(false);
    iterator it(begin(comp));
    
    // while node is not the null pointer indicating end of list
    
    while (it != end())
    {
      if (*it == *comp)
      {
        found = true;
        
        if (it->previous())
        {
          it->previous()->setNext(it->next());
        }
        
        if (it->next())
        {
          it->next()->setPrevious(it->previous());
        }
        
        it->clearPositionalData();
      }
      
      ++it;
    }
    
    return found;
  }
  
  bool ComponentList::sortComponentList(Node* c1, Node* c2)
  {
    return (c1->component()->name() < c2->component()->name());
  }
  
  ComponentList::iterator ComponentList::begin(Node* node)
  {
    // this method returns the _front of any segment for which node belongs to
    // if node == 0 or if node has no parent, we return the _front of the top 
    // level list
    iterator it;
    if (!node || !node->parentComponent())
    {
      it = iterator(_front);
      
    } else
    {
      Node* n = node;
      
      while (n->previous())
      {
        n = n->previous();
      }
      
      it = iterator(n);
    }
    
    return it;
  }
  
  ComponentList::const_iterator ComponentList::begin(Node* node) const
  {
    const_iterator it;
    
    if (!node || !node->parentComponent())
    {
      it = const_iterator(_front);
    } else
    {
      Node* n = node;
      
      while (n->previous())
      {
        n = n->previous();
      }
      
      it = const_iterator(n);
    }

    return it;
  }
  
  ComponentList::iterator ComponentList::end()
  {
    // per STL, the end() method returns one past the last item.
    // in our list, this is always the null pointer, 0x0
    return iterator(0);
  }
  
  ComponentList::const_iterator ComponentList::end() const
  {
    return const_iterator(0);
  }
  
  void ComponentList::updateList(Node* node)
  {
    // indicates this is not a child component
    if (!node->parentComponent())
    {
      if (!node->previous())
      {
        _front = node;
      }
      
      if (!node->next())
      {
        _back = node;
      }
    }
  }

  ComponentList::Node::Node(Pointer comp) : 
  _component(comp),
  _durationMSecs(0),
  _parentComponent(0),
  _previous(0),
  _next(0),
  _child(0),
  _lastChild(0)
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
    if (child())
    {
      childFound = true;
    }
    
    return childFound;
  }

  void ComponentList::Node::clearPositionalData()
  {
    _previous = 0;
    _parentComponent = 0;
    _next = 0;
  }
  
  void ComponentList::Node::updateParent()
  {
    if (_parentComponent)
    {
      if (!_next)
      {
        _parentComponent->setLastChild(this);
      }
     
      ComponentList::iterator it(this);
      int duration = it->durationMSecs();
      
      while (it->hasNext())
      {
        ++it;
        duration += it->durationMSecs();
      }
      
      _parentComponent->setDurationMSecs(duration);
    }
  }

}
