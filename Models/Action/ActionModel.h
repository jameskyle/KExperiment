#ifndef ACTIONMODEL_H
#define ACTIONMODEL_H
#include "Models/ComponentModel.h"

namespace kex
{
  /** \brief  Model for the Action Component
   * 
   * Copyright 2010 KSpace MRI. All Rights Reserved.
   *
   * \author James Kyle
   * \author $LastChangedBy$
   * \date 2010-4-12
   * \date $LastChangedDate$
   * \version $Rev$  \sa Action ComponentInterface  
   **/
  class ActionModel : public QAbstractItemModel
  {
  public:
    ActionModel(QObject *parent = 0);
    ~ActionModel() {}
    
    void setData(const QStringList& resourceList);
  };
  

}
#endif