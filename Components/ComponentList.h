#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/utility/enable_if.hpp>
#include <algorithm>

#include "Utilities/Utilities.h"
#include "Component.h"

namespace kex
{
  class ComponentList
  {
  public:
    struct Node
    {
    public:
      friend class ComponentList;
      
      typedef Node* Pointer;
      
      Node(Component::SharedPointer comp);
      Node(Component::Pointer comp);
      ~Node();
      
      // operators
//      operator  bool() const;
//      bool      operator!() const;
//      bool operator==(const Node& other);
//      bool operator!=(const Node& other);
      
      ComponentList& children();
      int position() const;
      Pointer parent() const {return m_parent;}
      void setParent(Pointer node) {m_parent = node;}
      
      Component::SharedPointer component() const {return m_component;}
      int durationMSecs() const;
      
    private:
      Component::SharedPointer m_component;
      int       m_durationMSecs;
      Pointer   m_parent;
      Pointer   m_previous;
      Pointer   m_next;
      ComponentList*   m_children;
    };
        
    template<class Value>
    class node_iter : public boost::iterator_facade<
    node_iter<Value>,
    Value,
    boost::random_access_traversal_tag,
    Value*>
    {
    private:
      struct enabler {};
      
    public:
      node_iter() : m_node(0) {}
      
      explicit node_iter(Value* p) : m_node(p) {}
      
      // converting constructor for const casting between iterators
      template<class OtherValue>
      node_iter(node_iter<OtherValue> const& other,
                typename boost::enable_if<
                boost::is_convertible<OtherValue*, Value*>,
                enabler>::type = enabler()) : m_node(other.m_node) {}
      
    private:
      friend class boost::iterator_core_access;
      template<class> friend class node_iter;
      
      template<class OtherValue>
      bool equal(node_iter<OtherValue> const& other) const
      {return this->m_node == other.m_node;}
      
      void increment()
      {m_node = m_node->m_next;}
      
      Value* dereference() const
      {return m_node;}
      
      void decrement()
      {m_node = m_node->m_previous;}
      
      void advance(ptrdiff_t n)
      {
        // advance the specified number of nodes
        for (ptrdiff_t i = 0; i < n; ++i)
        {
          // if our current node, m_node, is the null pointer, break the loop
          // and return null
          if (!m_node)
          {
            break;
          }
          m_node = m_node->m_next;
        }
      }
      
      ptrdiff_t distance_to(node_iter<Value> j)
      {
        ptrdiff_t dist(0);
        
        while (*this != j)
        {
          ++dist;
        }
        
        return dist;
      }
      
      Value *m_node;
      
    };
    
    typedef node_iter<Node> iterator;
    typedef node_iter<Node const> const_iterator;
    
    ComponentList(Node::Pointer parent = 0);
    ~ComponentList();
    
    // STL
    Node::Pointer     front();
    Node::Pointer     back();
    int               size() const;
    bool              empty() const;
    void              push_back(Node::Pointer node);
    void              push_back(Component::Pointer comp);
    void              push_back(Component::SharedPointer comp);
    void              push_front(Node::Pointer node);
    void              push_front(Component::Pointer comp);
    void              push_front(Component::SharedPointer comp);
    iterator          begin() const;
    iterator          end() const;
    void              clear();
    void              remove(Node::Pointer node);
    iterator          findByName(const QString& name) const;
    static ComponentList&    globalList();
//    iterator find(Node::Pointer node) const;


  private:
    void connectNodeComponents(Node::Pointer previous, Node::Pointer next) const;
    void disconnectNodeComponents(Node::Pointer previous, Node::Pointer next) const;
    Node::Pointer m_head;
    Node::Pointer m_tail;
    Node::Pointer m_parent;
    int m_size;
    
  };
}

#endif
