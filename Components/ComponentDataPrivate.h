#ifndef COMPONENTDATAPRIVATE_H
#define COMPONENTDATAPRIVATE_H

#include <QIcon>
#include <QStringList>

namespace kex
{
  /** \brief  Holds the private data of a OutputComponent object 
   * 
   * Copyright 2010 KSpace MRI. All Rights Reserved.
   *
   * \author James Kyle
   * \author $LastChangedBy$
   * \date 2010-5-6
   * \date $LastChangedDate$
   * \version $Rev$  \sa OutputComponent
   **/
  struct ComponentDataPrivate
  {
    /** \brief  Default constructor.
     * 
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     *
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-5-6
     * \date $LastChangedDate$
     * \param <#(name)#> <#(description)#>
     * \prarm <#(name)#> <#(description)#>
     * \version $Rev$  \sa <#(see also)#>
     **/
    ComponentDataPrivate() {}
    
    QAtomicInt  ref;
    QString     name; //!< name of the component
    QString     description; //!< detailed description of the component
    QString     label; //!< brief description of the component
    QString     mainCategory; //!< main group identifier
    QStringList categoryList; //!< list of all categories for component
    QIcon       icon;
  };
}
#endif