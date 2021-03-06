#ifndef COMPONENTMODEL_H
#define COMPONENTMODEL_H
#include <QAbstractTableModel>
#include <QResource>
#include <QStringList>
#include <QIcon>
#include <Qt>
#include <QTime>
#include <QDebug>

#include "Common/Config.h"
#include "Components/Component.h"
#include "Components/ComponentCollection.h"

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
  * \version $Rev$  \sa Component
  **/
  class ComponentModel : public QAbstractItemModel
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
     * \sa Component Component::ComponentTypes
     **/
    ComponentModel(Component::ComponentList *c_list = &Component::globalList(),
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

    static ComponentModel& globalInstance();
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    QModelIndex parent(const QModelIndex& index) const;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent) const;

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

  private:
    Component::Pointer  getItem(const QModelIndex& index) const;
    ComponentCollection::Pointer getCollectionItem(const QModelIndex& index) const;
    int getIndexForItem(const Component::ComponentList& list,
                        Component::Pointer component) const;
    Component::ComponentList& m_components;

  public slots:
    void updateComponentList();
  };


};
#endif
