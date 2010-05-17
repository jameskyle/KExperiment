#ifndef COMPONENTMODEL_H
#define COMPONENTMODEL_H
#include <QAbstractTableModel>
#include <QResource>
#include <QStringList>
#include <QIcon>

#include "Common/Global.h"
#include "Components/ComponentList.h"
#include "Components/OutputComponent.h"

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
  * \version $Rev$  \sa OutputComponent
  **/
  class ComponentModel : public QAbstractTableModel
  {
    Q_OBJECT

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
    * \param types a mask of the types of components
    * \param parent pointer to the parent classe.
    * \version $Rev$  
    * \sa OutputComponent OutputComponent::ComponentTypes
    **/
    ComponentModel(OutputComponent::ComponentTypes types = 
                   OutputComponent::AllComponents, 
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

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const;
    
  private:
    const ComponentList::ComponentQList _componentList;
  public slots:
    void updateComponentList();
  };


}
#endif
