#include "ComponentModel.h"

namespace kex
{
  ComponentModel::ComponentModel(OutputComponent::ComponentTypes types, 
                                 QObject *parent) 
    : QAbstractItemModel(parent),
      _componentList(ComponentList::instance().filter(types))
  {
  }

  int ComponentModel::rowCount(const QModelIndex &parent) const
  {
    int count(0);
    if (parent.isValid())
    {
      OutputComponent *comp;
      comp = static_cast<OutputComponent *>(parent.internalPointer());
      qDebug() << "rowCount::name " << comp->name();
      count = comp->numChildren();
    }

    return count;
  }

  int ComponentModel::columnCount(const QModelIndex & /*parent */) const
  {
    
    // For display purposes, a component shows these values for columens
    // - 0 name
    // - 1 component type
    // - 2 label
    // - 3 description
    // - 4 duration
    // - 5 Icon
    return 6;
  }
  
  QVariant ComponentModel::data(const QModelIndex &index, int role) const
  {
    QVariant result;
    if (role == Qt::DecorationRole)
    {
       QSharedPointer<OutputComponent> comp(_componentList[index.row()]);
      result = comp->icon();
    } else if (role == Qt::DisplayRole)
    {
      // Columns   Value
      // 0         Component Name
      // 1         ComponentType
      // 2         Label
      // 3         Description
      // 4         Duration 
      // 5         Component's Icon
      
      if (index.row()     < _componentList.count() &&
          index.row()     >= 0 &&
          index.column()  >= 0 &&
          index.column()  < columnCount())
      {
        OutputComponent::SharedPointer comp = _componentList[index.row()];
        
        if (index.column() == 0)
        {
          result.setValue(comp->name());
        } else if (index.column() == 1)
        {
          
          result.setValue(
            OutputComponent::componentTypeToString(comp->componentType()));
        } else if (index.column() == 2)
        {
          result.setValue(comp->label());
        } else if (index.column() == 3)
        {
          result.setValue(comp->description());
        } else if (index.column() == 4)
        {
          quint32 duration = comp->durationMSecs();
          quint32 minutes, seconds, msecs;
          float sec_fraction;
          
          msecs   = duration % 1000;
          sec_fraction = msecs / 1000.0;
          seconds = (duration / 1000) % 60;
          minutes = (duration / 1000 / 60) % 60;
          
          QString time("%1 : %2.%3");
          
          result.setValue(time.arg(minutes).arg(seconds).arg(sec_fraction));
        } else if (index.column() == 5)
        {
          result = (comp->icon()).pixmap(QSize(64,64));
        }
        else {
          result.setValue(QString("a column value"));
        }
      }
    } else if (role == Qt::EditRole)
    {
      result = index.data(Qt::DisplayRole);
    }
    
    return result;
  }
  
  QVariant ComponentModel::headerData(int section, Qt::Orientation /*orient*/,
                      int role) const
  {
    QVariant result;
    if (role == Qt::DisplayRole)
    {
      switch (section)
      {
        case 0:
          result.setValue(QString("Name"));
          break;
        case 1:
          result.setValue(QString("Label"));
          break;
        case 2:
          result.setValue(QString("Description"));
          break;
        case 3:
          result.setValue(QString("Duration (msecs)"));
          break;

        default:
          break;
      }
    }
    return result;
  }

  void ComponentModel::updateComponentList()
  {
    //_rootPath.refresh();
  }
  
  QModelIndex ComponentModel::index(int row, int column, 
                                    const QModelIndex &parent) const
  {
    QModelIndex index;
    
    if (hasIndex(row, column, parent))
    {
      if (parent.isValid())
      {
        OutputComponent::SharedPointer parent_item;
        OutputComponent::SharedPointer child;
        
        parent_item = *static_cast<OutputComponent::SharedPointer *>
                                  (parent.internalPointer());
        child = parent_item->child(row);
        
        if (child)
        {
          index = createIndex(row, column, &child);
        }
      }
    }
    
    return index;
  }
  
  QModelIndex ComponentModel::parent(const QModelIndex& index) const
  {
    QModelIndex p_index;
    
    if (index.isValid())
    {
      OutputComponent *comp;
      comp = static_cast<OutputComponent *>(index.internalPointer());
      
      if (comp->parent())
      {
        p_index = createIndex(index.row(), 0, comp->parent() );
      } 
    }
    
    return p_index;
  }
  
  bool ComponentModel::hasChildren(const QModelIndex &parent) const
  {
    bool result(false);
    if (parent.isValid())
    {
      OutputComponent *comp;
      comp = static_cast<OutputComponent *>(parent.internalPointer());
      result = comp->hasChildren(); 
    }
    
    return result;
  }


}
