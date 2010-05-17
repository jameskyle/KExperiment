#ifndef COMPONENTINTERFACE_H
#define COMPONENTINTERFACE_H

#include <QStringList>
#include <QTextStream>
#include <QVariant>
#include <QIcon>

#include <typeinfo>

#include "Common/Uncopyable.h"
#include "ComponentDataPrivate.h"

namespace kex
{
  /** \brief  The Action class is the base class for all Action objects.
  *
  *
  * The Action class is the core of al Action objects. Actions are inherently
  * unique. Thus we disallow copying of actions. 
  *
  * © Copyright 2010 KSpace MRI - James Kyle. All Rights Reserved.
  *
  * \author James Kyle KSpace MRI
  * \author $LastChangedBy$
  * \date 2010-04-01
  * \date $LastChangedDate$
  * \version $Rev$  \sa
  **/
  class OutputComponent
  {
  public:

    
    /** \brief This is the constructor for the Action base class.
    *
    * Instantiates the Action class with all attributes set to an empty
    * string
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    **/
    OutputComponent();
    
    /** \brief  Copy constructor for the OutputComponent
     * 
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-5-6
     * \date $LastChangedDate$
     * \param component the component to be copied
     * \version $Rev$
     **/
    OutputComponent(const OutputComponent &component);
    
    /** \brief  Assignment operator.
     * 
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-5-6
     * \date $LastChangedDate$
     * \param component the component being assigned
     * \version $Rev$
     **/
    OutputComponent& operator=(const OutputComponent &component);
    
    /** \brief This is the destructor for the Action base class
    *
    * Performs basic clean up required by the Action base class
    *
    * \author James Kyle KSpace MRI
    * \date 2010-04-01
    **/
    virtual ~OutputComponent ();
    
             
    /** \brief  Returns the type of component this AbstractComponent represents.
     * 
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * <#(detailed descriptoin)#>
     * 
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-5-10
     * \date $LastChangedDate$
     * \param <#(name)#> <#(description)#>
     * \prarm <#(name)#> <#(description)#>
     * \version $Rev$  \sa <#(see also)#>
     **/
    ComponentType componentType() const {return _componentType;}

  private:
 
    
  };
}
#endif