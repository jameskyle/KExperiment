#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include <QString>
#include <QSet>
#include <QList>
#include <QHash>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/utility/enable_if.hpp>

#include "OutputComponent.h"
#include "Common/Uncopyable.h"
#include "Utilities/Utilities.h"
#include "Common/Logger.h"

namespace kex
{
  class ComponentList
  {
  public:
    class Node
    {
    public:
      typedef Node* Pointer;

      Node(OutputComponent::SharedPointer comp);
      ~Node() {}
      
      OutputComponent::SharedPointer   component() {return _component;}
      Pointer     parentComponent() const {return _parentComponent;}
      Pointer     previous() const {return _previous;}
      Pointer     next() const {return _next;}
      Pointer     lastChild() const {return _lastChild;}
      Pointer     child() const {return _child;}
      int         durationMSecs() const {return _durationMSecs;}
      int         position() const;

      void setParentComponent(Pointer p) {_parentComponent = p;}
      void setPrevious(Pointer p) {_previous = p;}
      void setNext(Pointer c) {_next = c;}
      void setChild(Pointer c) {_child = _lastChild = c;}
      void setLastChild(Pointer c) {_lastChild = c;}
      void setDurationMSecs(int duration) {_durationMSecs = duration;}
      int  numChildren() const;

      void updateParent(); 
      
      bool      hasNext() const;
      bool      hasPrevious() const;
      bool      hasChildren() const;
      bool      isNull() const;

      // operators
      operator  bool() const;
      bool      operator!() const;
      
      void clearPositionalData();
            
    private:
      OutputComponent::SharedPointer _component;
      int       _durationMSecs;
      Pointer   _parentComponent;
      Pointer   _previous;
      Pointer   _next;
      Pointer   _child;
      Pointer   _lastChild;
    };
    
    template<class Value>
    class node_iter : public boost::iterator_facade<
                                 node_iter<Value>,
                                 Value,
                                 boost::random_access_traversal_tag>
    {
    private:
      struct enabler {};
      
    public:
      node_iter() : m_node(0) {}
      
      explicit node_iter(Value* p) : m_node(p) {}
      
      template<class OtherValue>
      node_iter(node_iter<OtherValue> const& other) : 
        m_node(other.m_node) {}
      
      // converting constructor for const casting between iterators
      template<class OtherValue>
      node_iter(node_iter<OtherValue> const& other,
                typename boost::enable_if<
                  boost::is_convertible<OtherValue*, Value*>,
                enabler>::type = enabler()) : m_node(other.m_node) {}
                
    private:
      friend class boost::iterator_core_access;
      template<class> friend class node_iter;
      
      Value& dereference() const
      {return *m_node;}

      template<class OtherValue>
      bool equal(node_iter<OtherValue> const& other) const
      {return this->m_node == other.m_node;}
      
      void increment()
      {m_node = m_node->next();}
      
      void decrement()
      {m_node = m_node->previous();}
      
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
          
          m_node = m_node->next();
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
    typedef node_iter<const Node> const_iterator;
    
    // Filter iterators
    struct isActionComponent 
    {
      bool operator()(Node& node) 
      {return node.component()->componentType() & OutputComponent::ActionType;}
    };
    
    struct ActionComponents
    {
      friend class ComponentList;
      
      typedef boost::filter_iterator<isActionComponent, iterator> 
              action_iterator;
      typedef boost::filter_iterator<isActionComponent, const_iterator>
              const_action_iterator;
      
      
      action_iterator begin() 
      {
        return boost::make_filter_iterator<isActionComponent>(
                                          _comps.begin(),
                                           _comps.end());
      }
      
      action_iterator end()
      {
        return boost::make_filter_iterator<isActionComponent>(
                                           _comps.end(),
                                           _comps.end());
      }
      
    private:
      ActionComponents(ComponentList& comps) : _comps(comps) {}
      ComponentList& _comps;
                                     
    } ActionComponents;
    
    struct isEventComponent
    {
      bool operator()(OutputComponent& comp)
      {return comp.componentType() & OutputComponent::EventType;}
    };
    
    struct isTrialComponent
    {
      bool operator()(OutputComponent& comp)
      {return comp.componentType() & OutputComponent::TrialType;}
    };
    
    struct isExperimentComponent
    {
      bool operator()(OutputComponent& comp)
      {
        return comp.componentType() & OutputComponent::TrialType;
      }
    };
    
    ComponentList();
    ~ComponentList();

    static ComponentList& instance();
    static const ComponentList& const_instance();
    
    int count() const;
    /** \brief  Given the component name, returns a reference to that component.
     * 
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * Returns a pointer to the component with name componentName or zero 
     * otherwise.
     * 
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-5-2
     * \date $LastChangedDate$
     * \param componentName the name of the component to search for.
     * \return OutputComponent::Pointer pointer to found component or 0 if not found
     * \version $Rev$ 
     **/
    iterator find(const Node::Pointer node, iterator start, iterator stop) const;
    iterator findByName(const QString& name);
    
    void insert(Node::Pointer prevNode, Node::Pointer node);
    void insert(iterator it, Node::Pointer node);
    void clone(Node::Pointer prevNode, Node::Pointer node);
    bool remove(Node::Pointer comp);
    
    void insertAfter(Node::Pointer prevNode, Node::Pointer node);
    void insertBefore(Node::Pointer node, Node::Pointer nextNode);

    void prepend(Node::Pointer node, Node::Pointer parent = 0);
    void prepend(OutputComponent::Pointer comp, Node::Pointer parent = 0);
    
    void append(Node::Pointer node, Node::Pointer parent = 0);
    void append(OutputComponent::Pointer comp, Node::Pointer parent = 0);
        
    static bool sortComponentList(Node::Pointer c1, Node::Pointer c2);
    
    // Operators
    Node& operator[](int row);
    
    // iterator methods
    iterator begin(Node::Pointer node = 0);
    const_iterator begin(Node::Pointer node = 0) const;
    iterator end();
    const_iterator end() const;
    
  private:
    void updateList(Node::Pointer node);
    Node::Pointer _front;
    Node::Pointer _back;
  };  
}

#endif