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
  class ComponentList : private Uncopyable
  {
  public:
    
    class Node
    {
    public:
      typedef QSharedPointer<OutputComponent> Pointer;

      Node(Pointer comp);
      ~Node() {}
      
      Pointer   component() {return _component;}
      Node*     parentComponent() const {return _parentComponent;}
      Node*     previous() const {return _previous;}
      Node*     next() const {return _next;}
      Node*     lastChild() const {return _lastChild;}
      Node*     child() const {return _child;}
      int       durationMSecs() const {return _durationMSecs;}
      
      void setParentComponent(Node* p) {_parentComponent = p;}
      void setPrevious(Node* p) {_previous = p;}
      void setNext(Node* c) {_next = c;}
      void setChild(Node* c) {_child = c;}
      void setLastChild(Node* c) {_lastChild = c;}
      void setDurationMSecs(int duration) {_durationMSecs = duration;}
      
      void updateParent(); 
      
      bool      hasNext() const;
      bool      hasChildren() const;
      bool      isNull() const;

      // operators
      operator  bool() const;
      bool      operator!() const;
      
      void clearPositionalData();
            
    private:
      Pointer _component;
      int     _durationMSecs;
      Node*   _parentComponent;
      Node*   _previous;
      Node*   _next;
      Node*   _child;
      Node*   _lastChild;
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
    
    int count() const {return _count;}
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
     * \return OutputComponent* pointer to found component or 0 if not found
     * \version $Rev$ 
     **/
    iterator find(const Node* node, iterator start, iterator stop) const;
    iterator findByName(const QString& name) const;
    
    void insert(Node* prevNode, Node* node);
    void insert(iterator it, Node* node);
    void clone(Node* prevNode, Node* node);
    bool remove(Node* comp);
    
    void insertAfter(Node* prevNode, Node* node);
    void insertBefore(Node* node, Node* nextNode);

    void prepend(Node* node, Node* parent = 0);
    void prepend(OutputComponent* comp, Node* parent = 0);
    
    void append(Node* node, Node* parent = 0);
    void append(OutputComponent* comp, Node* parent = 0);
        
    static bool sortComponentList(Node* c1, Node* c2);
    
    // iterator methods
    iterator begin(Node* node = 0);
    const_iterator begin(Node* node = 0) const;
    iterator end();
    const_iterator end() const;
    
  private:
    void updateList(Node* node);
    int   _count;
    Node* _front;
    Node* _back;
  };  
}

#endif