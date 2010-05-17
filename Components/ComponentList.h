#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include <QString>
#include <QSet>
#include <QList>

#include "OutputComponent.h"
#include "AbstractComponent.h"
#include "Common/Uncopyable.h"
#include "Utilities/Utilities.h"
#include "Common/Logger.h"

namespace kex
{
  class ComponentList : private Uncopyable
  {
  public:
    typedef QList<OutputComponent*> ComponentQList;
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
    OutputComponent* find(const QString& componentName) const;
    
    const ComponentQList filter(OutputComponent::ComponentTypes types) const;
    
    bool remove(OutputComponent* comp);
    
    void append(OutputComponent* interface);
    
    int count() const;
    
    const ComponentQList toList() const;
  private:
    QSet< OutputComponent* > _componentList;
    ComponentList() {}
    ~ComponentList();
  };  
}

#endif