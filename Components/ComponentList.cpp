#include "ComponentList.h"

namespace kex {
/*  bool ComponentList::sortComponentList(Node::Pointer c1, Node::Pointer c2)
  {
    return (c1->component()->name() < c2->component()->name());
  }*/
  
  ComponentList::Node::Node(OutputComponent::SharedPointer comp) : 
  m_component(comp),
  m_durationMSecs(0),
  m_parent(0),
  m_previous(0),
  m_next(0),
  m_children(new ComponentList)
  {
    if (comp->componentType() & OutputComponent::ActionType)
    {
      Action *action = qobject_cast<Action *>(comp.data());
      
      if (action)
      {
        //_durationMSecs = action->durationMSecs();
      }
    }
  }
  
  ComponentList::Node::Node(OutputComponent::Pointer comp) : 
  m_component(comp),
  m_durationMSecs(0),
  m_parent(0),
  m_previous(0),
  m_next(0),
  m_children(new ComponentList)  
  {
    
  }
  
  ComponentList::Node::~Node()
  {
    Utilities::deleteAll(*m_children);
    delete m_children;
  }
  
  ComponentList& ComponentList::Node::children()
  {
    return *m_children;
  }
  
  int ComponentList::Node::position() const
  {
    ComponentList::const_iterator it(this);
    int pos(0);
    
    while ((*it)->m_previous)
    {
      ++pos;
      --it;
    }
    
    return pos;
  }
  
  ComponentList::ComponentList() :
  m_head(0),
  m_tail(0),
  m_size(0)
  {
    
  }
  
  ComponentList::ComponentList(Node::Pointer node) :
  m_head(node),
  m_tail(0),
  m_size(0)
  {
    Node::Pointer temp(m_head);
    
    temp = m_head;
    ++m_size;
    
    while (temp->m_next)
    {
      ++m_size;
      temp = temp->m_next;
    }
    
    m_tail = temp;
    
  }
  
  ComponentList::~ComponentList() {}
  int ComponentList::size() const
  {
    return m_size;
  }
  
  ComponentList::Node::Pointer ComponentList::front() 
  {
    return m_head;
  }
  
  ComponentList::Node::Pointer ComponentList::back()
  {
    return m_tail;
  }
  
  bool ComponentList::empty() const
  {
    return (m_size == 0);
  }
  
  void ComponentList::push_back(Node::Pointer node)
  {
    Q_ASSERT(!node->m_previous && !node->m_next);

    if (m_tail)
    {
      m_tail->m_next = node;
      node->m_previous = m_tail;
      m_tail = node;
    } else {
      Q_ASSERT(m_tail == m_head);
      m_head = m_tail = node;
    }
    
    ++m_size;
  }
  
  void ComponentList::push_back(OutputComponent::Pointer comp)
  {
    Node::Pointer node = new Node(comp);
    push_back(node);
  }
  
  void ComponentList::push_back(OutputComponent::SharedPointer comp)
  {
    Node::Pointer node = new Node(comp);
    push_back(node);
  }
  
  void ComponentList::push_front(Node::Pointer node)
  {
    Q_ASSERT(!node->m_previous && !node->m_next);
    
    if (m_head)
    {
      Q_ASSERT(!m_head->m_previous);
      m_head->m_previous = node;
      node->m_next = m_head;
    } else {
      m_tail = node;
    }
    
    m_head = node;
    ++m_size;
  }
  
  void ComponentList::push_front(OutputComponent::Pointer comp)
  {
    Node::Pointer node = new Node(comp);
    push_front(node);
  }

  void ComponentList::push_front(OutputComponent::SharedPointer comp)
  {
    Node::Pointer node = new Node(comp);
    push_front(node);
  }
  
  ComponentList::iterator ComponentList::begin() const 
  {
    return iterator(m_head);
  }
  
  ComponentList::iterator ComponentList::end() const
  {
    iterator it(0);
    
    if (m_tail)
    {
      it = iterator(m_tail->m_next);
    }
    
    return it;
  }
  
  void ComponentList::clear()
  {
    iterator it(begin());
    Node::Pointer p;
    
    while (it != end())
    {
      p = *it;
      ++it;
      p->m_previous = 0;
      p->m_next = 0;
    }
    
    m_head = m_tail = 0;
    m_size = 0;
  }
  
  void ComponentList::remove(Node::Pointer node)
  {
    iterator it(Utilities::find(begin(), end(), node));
    
    if (it != end())
    {
      if ((*it)->m_previous)
      {
        (*it)->m_previous->m_next = (*it)->m_next;
      } else {
        m_head = (*it)->m_next;
      }
      
      if ((*it)->m_next)
      {
        (*it)->m_next->m_previous = (*it)->m_previous;
      } else {
        m_tail = (*it)->m_previous;
      }
      (*it)->m_previous = 0;
      (*it)->m_next = 0;
      --m_size;
      
    }
  }	
  
  ComponentList::iterator ComponentList::findByName(const QString& name) const
  {
    iterator b(begin());
    iterator e(end());
    while (b != e)
    {
      if ((*b)->component()->name() == name)
      {
        break;
      }
      ++b;
    }
    
    return b;
  }
}
