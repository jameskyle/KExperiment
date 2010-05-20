#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include <QString>
#include <QSet>
#include <QList>

#include "OutputComponent.h"
#include "Common/Uncopyable.h"
#include "Utilities/Utilities.h"
#include "Common/Logger.h"

namespace kex
{
  class ComponentList : private Uncopyable
  {
  public:
    typedef QList< OutputComponent::SharedPointer > ComponentQList;
    typedef QListIterator< OutputComponent::SharedPointer > ComponentQListIterator;
    
    static ComponentList& instance();
    
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
    OutputComponent::SharedPointer find(const QString& componentName) const;
    
    const ComponentQList filter(OutputComponent::ComponentTypes types) const;
    
    bool remove(OutputComponent::SharedPointer comp);
    
    void append(OutputComponent::SharedPointer interface);
    void append(OutputComponent* interface);
    
    int count() const;
    
    const ComponentQList toList() const;
    
    static bool sortComponentQList(const OutputComponent::SharedPointer c1,
                                   const OutputComponent::SharedPointer c2);

  private:
    typedef QSet<OutputComponent::SharedPointer> ComponentQSet;
    typedef QSetIterator<OutputComponent::SharedPointer> ComponentQSetIterator;
    
    ComponentQSet _componentList;
    ComponentList();
    virtual ~ComponentList();
  };  
}

#endif