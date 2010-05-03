#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include <QList>
#include <QListIterator>
#include <QString>

#include <Components/ComponentInterface.h>

namespace kex
{
  class ComponentList : public QList<ComponentInterface *>
  {
  public:
    /** \brief  A subclass of QList for storign components
     * 
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-5-2
     * \date $LastChangedDate$
     * \version $Rev$  \sa QList
     **/
    
    
    ComponentList() {}
    ~ComponentList() {}
    
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
     * \version $Rev$ 
     **/
    ComponentInterface* find(const QString& componentName) const;
  };  
}

#endif