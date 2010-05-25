#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include <QString>
#include <QSet>
#include <QList>
#include <QHash>
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
      
      Pointer component() {return _component;}
      int position() const {return _position;}
      Node* root() const {return _root;}
      Node* previous() const {return _previous;}
      Node* next() const {return _next;}
      Node* child() const {return _child;}
      
      void setRoot(Node* root) {_root = root;}
      void setPrevious(Node* prev) {_previous = prev;}
      void setNext(Node* next) {_next = next;}
      
      bool hasNext() const;
      Node::Pointer data() const {return _component;}
      bool isNull() const;

      // operators
      operator bool() const;
      bool operator!() const;
      
    private:
      Pointer _component;
      int     _position;
      Node*   _root;
      Node*   _previous;
      Node*   _next;
      Node*   _child;
    };

    ComponentList();
    ~ComponentList();

    static ComponentList& instance();
    
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
    Node* find(const Node& node) const;
    
    const ComponentList filter(OutputComponent::ComponentTypes types) const;
    void insertAfter(Node* node, Node* prevNode);
    void insertBefore(Node* node, Node* nextNode);

    void prepend(Node* node);
    void append(Node* node);
    Node* append(OutputComponent* comp);
    void appendChild(Node* parent, Node* child);
    void prependChild(Node* parent, Node* child);
    bool remove(Node* comp);

    static bool sortComponentList(Node* c1, Node* c2);
    
  private:
    int   _count;
    Node* _front;
    Node* _back;
  };  
}

#endif