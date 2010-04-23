#ifndef COMPONENTMODEL_H
#define COMPONENTMODEL_H
#include <QFileSystemModel>
#include <QResource>
#include <QStringList>
#include <QXmlStreamReader>

#include <Common/Global.h>

namespace kex
{
  /** \brief  Model for all component data
  * 
  * Copyright 2010 KSpace MRI. All Rights Reserved.
  *
  * \author James Kyle
  * \author $LastChangedBy$
  * \date 2010-4-12
  * \date $LastChangedDate$
  * \version $Rev$  \sa ComponentInterface
  **/
  class ComponentModel : public QFileSystemModel
  {
  public:
    /** \brief  Default constructor.
    * 
    * Copyright 2010 KSpace MRI. All Rights Reserved.
    *
    * Sets up the component item model.
    * 
    * \author James Kyle
    * \author $LastChangedBy$
    * \date 2010-4-12
    * \date $LastChangedDate$
    * \param parent pointer to the parent classe. 
    * \version $Rev$  \sa ComponentInterface
    **/
    ComponentModel(Config::ApplicationDataDirectoryType component,
                            QObject *parent = 0);
    
    /** \brief  Default destructor.
     * 
     * Copyright 2010 KSpace MRI. All Rights Reserved.
     * 
     * \author James Kyle
     * \author $LastChangedBy$
     * \date 2010-4-12
     * \date $LastChangedDate$
     * \version $Rev$
     **/
    ~ComponentModel() {}
    
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
  private:
    QXmlStreamReader xmlReader;
    QString _filter;
    
  
  public slots:
    void updateFilter(QString filter);
  };
  

}
#endif