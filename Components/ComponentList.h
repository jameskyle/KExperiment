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
#include "Actions/Action.h"

namespace kex
{
  class Node
  {
  public:
    typedef Node* Pointer;

    Node(OutputComponent::SharedPointer comp);
    ~Node();

    OutputComponent::SharedPointer   component() {return _component;}
    Pointer     parent() const {return _parent;}
    Pointer     previous() const {return _previous;}
    Pointer     next() const {return _next;}
    Pointer     front() const;
    Pointer     back() const;
    Pointer     lastChild() const;
    Pointer     child() const {return _child;}
    int         durationMSecs() const {return _durationMSecs;}
    int         position() const;

    void setParent(Pointer p) {_parent = p;}
    void setPrevious(Pointer p) {_previous = p;}
    void setNext(Pointer c);
    void setDurationMSecs(int duration) {_durationMSecs = duration;}
    void append(Pointer node);
    void prepend(Pointer node);
    void appendChild(Pointer node);
    void remove(Pointer node);
    int  numChildren() const;
    int  count() const;

    // operators
    operator  bool() const;
    bool      operator!() const;
    bool operator==(const Node& other);
    bool operator!=(const Node& other);

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
      {m_node = m_node->next();}

      Value* dereference() const
      {return m_node;}

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
    typedef node_iter<Node const> const_iterator;

  public:
    iterator begin() const {return iterator(front());}
    iterator end() const {return iterator(0);}
    iterator find(Pointer node) const;

  private:
    OutputComponent::SharedPointer _component;
    int       _durationMSecs;
    Pointer   _parent;
    Pointer   _previous;
    Pointer   _next;
    Pointer   _child;
  };

  typedef QList<Node::Pointer> ComponentList;
    //static bool sortComponentList(Node::Pointer c1, Node::Pointer c2);
}

#endif
