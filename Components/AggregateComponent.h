#ifndef AGGREGATECOMPONENT_H
#define AGGREGATECOMPONENT_H

#include <QString>
#include <QList>

#include "Components/OutputComponent.h"
#include "Components/OutputComponent.h"

namespace kex
{
  /** \brief  An AggregateComponent is a collection of components
   * 
   * © Copyright 2010 KSpace MRI - James Kyle. All Rights Reserved.
   *
   * \author James Kyle KSpace MRI
   * \author $LastChangedBy$
   * \date 2010-04-01
   * \date $LastChangedDate$
   * \version $Rev$  \sa Action OutputAction RestAction
   **/
  class AggregateComponent : public OutputComponent
  {
  public:
    /** \brief Constructor for the AggregateComponent class.
     * 
     * \author James Kyle KSpace MRI
     * \date 2010-04-01
     * \sa Action()
     **/
    AggregateComponent (QObject *parent = 0) : OutputComponent(parent) {}
    
    /** \brief The destructor for the AggregateComponent class
     * 
     * \author James Kyle KSpace MRI
     * \date 2010-04-01
     * \sa ~Action()
     **/
    virtual ~AggregateComponent ();
    
  private:
    QList<OutputComponent *> _componentList;
  };
}
#endif