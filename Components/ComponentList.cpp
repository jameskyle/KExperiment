#include "ComponentList.h"

namespace kex {
/*  bool ComponentList::sortComponentList(Node::Pointer c1, Node::Pointer c2)
  {
    return (c1->component()->name() < c2->component()->name());
  }*/
  
  ComponentList::Node::Node(Component::SharedPointer comp) : 
  m_component(comp),
  m_durationMSecs(0),
  m_parent(0),
  m_previous(0),
  m_next(0),
  m_children(new ComponentList(this))
  {
  }
  
  ComponentList::Node::Node(Component::Pointer comp) : 
  m_component(comp),
  m_durationMSecs(0),
  m_parent(0),
  m_previous(0),
  m_next(0),
  m_children(new ComponentList(this))  
  {
    
  }
  
  ComponentList::Node::~Node()
  {
    Utilities::deleteAll(*m_children);
    delete m_children;
  }
  
  ComponentList& ComponentList::globalList()
  {
    static ComponentList cList;
    return cList;
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
  
  ComponentList::ComponentList(Node::Pointer parent) :
  m_head(0),
  m_tail(0),
  m_parent(parent),
  m_size(0)
  
  {
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
    Q_ASSERT(!node->m_previous && !node->m_next && !node->m_parent);
    
    node->m_parent = m_parent;
    
    if (m_tail)
    {
      m_tail->m_next = node;
      node->m_previous = m_tail;
      m_tail = node;
    } else {
      Q_ASSERT(m_tail == m_head);
      m_head = m_tail = node;
    }
    
    connectNodeComponents(m_tail->m_previous, m_tail);
    ++m_size;
  }
  
  void ComponentList::push_back(Component::Pointer comp)
  {
    Node::Pointer node = new Node(comp);
    push_back(node);
  }
  
  void ComponentList::push_back(Component::SharedPointer comp)
  {
    Node::Pointer node = new Node(comp);
    push_back(node);
  }
  
  void ComponentList::push_front(Node::Pointer node)
  {
    Q_ASSERT(!node->m_previous && !node->m_next && !node->m_parent);
    
    node->m_parent = m_parent;
    
    if (m_head)
    {
      Q_ASSERT(!m_head->m_previous);
      m_head->m_previous = node;
      node->m_next = m_head;
    } else {
      m_tail = node;
    }
    
    m_head = node;
    
    connectNodeComponents(m_head, m_head->m_next);
    ++m_size;
  }
  
  void ComponentList::push_front(Component::Pointer comp)
  {
    Node::Pointer node = new Node(comp);
    push_front(node);
  }

  void ComponentList::push_front(Component::SharedPointer comp)
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
    return iterator(0);
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
      p->m_parent = 0;
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
      (*it)->m_parent = 0;
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
  
  int ComponentList::Node::durationMSecs() const
  {
    int duration(0);

    if ((m_component->componentType() & Component::ActionType))
    {
      duration = m_component->property("durationMSecs").toInt();
    } else
    {
      iterator it(m_children->begin());
      while (it != m_children->end())
      {
        duration += (*it)->durationMSecs();
        ++it;
      }
    }

    return duration;
  }

  void ComponentList::connectNodeComponents(Node::Pointer previous, 
                                            Node::Pointer next) const
  {
 //   bool success(false);
//    Component* p = previous->m_component.data();
//    Component* n = next->m_component.data();
//    
//    success = QObject::connect(p, SIGNAL(complete()), n, SLOT(begin()));
//    
//    if (!success)
//    {
//      QString msg = "Failed to connect component %1 from %2";
//      msg.arg(previous->m_component->name()).arg(next->m_component->name());
//      Logger::instance().log(msg, 0, Logger::WarningLogLevel);
//    }
    
  }
  
  void ComponentList::disconnectNodeComponents(Node::Pointer previous, 
                                               Node::Pointer next) const
  {
    bool success(false);
    Component* p = previous->m_component.data();
    Component* n = next->m_component.data();
    
    success = QObject::disconnect(p, SIGNAL(complete()), n, SLOT(begin()));
    
    if (!success)
    {
      QString msg = "Failed to disconnect component %1 from %2";
      msg.arg(previous->m_component->name()).arg(next->m_component->name());
      Logger::instance().log(msg, 0, Logger::WarningLogLevel);
    }
    
  }

}
