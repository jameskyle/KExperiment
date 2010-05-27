#include "ComponentModel.h"

namespace kex
{
  ComponentModel::ComponentModel(OutputComponent::ComponentTypes types, 
                                 QObject *parent) 
    : QAbstractItemModel(parent),
      _componentList(ComponentList::const_instance())
  {
  }

 
  QVariant ComponentModel::headerData(int section, Qt::Orientation /*orient*/,
                      int role) const
  {
    // Columns   Value
    // 0         Component Name
    // 1         ComponentType
    // 2         Label
    // 3         Description
    // 4         Duration 
    // 5         Component's Icon
    
    QVariant result;
    if (role == Qt::DisplayRole)
    {
      switch (section)
      {
        case 0:
          result.setValue(QString("Name"));
          break;
        case 1:
          result.setValue(QString("Component Type"));
          break;
        case 2:
          result.setValue(QString("Label"));
          break;
        case 3:
          result.setValue(QString("Description"));
          break;
        case 4:
          result.setValue(QString("Duration (msecs)"));
          break;
        case 5:
          result.setValue(QString("Icon"));
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


  int ComponentModel::rowCount(const QModelIndex &parent) const 
  {
    int count(0);
    
    if (parent.isValid())
    {
      OutputComponent::SharedPointer sp = getItem(parent);
      
      count = sp->numChildren();
      
    } else
    {
      count = _componentList.count();
    }

    return count;
  }
  
  int ComponentModel::columnCount(const QModelIndex &parent) const 
  {
    int count(0);
    
    if (!parent.isValid())
    {
      count = 5;
    } else
    {
      OutputComponent::SharedPointer sp = getItem(parent);
      count = sp->numChildren();
    }

    return count;
  }
  
  QVariant ComponentModel::data(const QModelIndex &index, int role) const 
  {
    // Columns   Value
    // 0         Component Name
    // 1         ComponentType
    // 2         Label
    // 3         Description
    // 4         Duration 
    // 5         Component's Icon
    
    QVariant result;
    
    if (index.isValid())
    {
      OutputComponent::SharedPointer sp;

      if (!index.parent().isValid())
      {
        sp = _componentList[index.row()];
      } else
      {
        sp = getItem(index);
      }

      if (role == Qt::DisplayRole)
      {
        if (index.column() == 0)
        {
          result.setValue(sp->name());
        } else if (index.column() == 1)
        {
          result.setValue(sp->mainCategory());
        }
      }
    }
    
    OutputComponent::SharedPointer sp(ComponentList::instance().find("Double Event Example"));
    qDebug() << "children: " << sp->numChildren();
    OutputComponent::SharedPointer child1(sp->child(0));
    OutputComponent::SharedPointer child2(sp->child(1));
    qDebug() << "child 1: " << child1->name();
    qDebug() << "child 2: " << child2->name();
    
    for (int i=0; i < sp->numChildren(); ++i)
    {
      qDebug() << (sp->child(i))->parent();
    }
    return result;
  }
  
  QModelIndex ComponentModel::parent(const QModelIndex &index) const 
  {
    QModelIndex p_index;
    
    if (index.isValid())
    {
      OutputComponent::SharedPointer sp = getItem(index);
      OutputComponent::SharedPointer parentItem(sp->parentComponent());
      
      if (parentItem)
      {
        p_index = createIndex(0,0, &parentItem);
      }
    }
    return p_index;
  }
  
  QModelIndex 
  ComponentModel::index(int row, int column, const QModelIndex &parent) const
  {
    QModelIndex ind;
    
    if(hasIndex(row, column, parent))
    {
      if(parent.isValid())
      {
        OutputComponent::SharedPointer parentItem = getItem(parent);
        
        OutputComponent::SharedPointer *child;
        child = new OutputComponent::SharedPointer;
        *child = parentItem->child(row);
        
        if (*child)
        {
          ind = createIndex(row, column, child);
        }
        
      } else
      {
        OutputComponent::SharedPointer *sp = new OutputComponent::SharedPointer;
        *sp = _componentList[row];
        ind = createIndex(row, column, sp);
      }

    }
    
    return ind;
  }
  
  OutputComponent::SharedPointer 
  ComponentModel::getItem(const QModelIndex& parent) const
  {
    OutputComponent::SharedPointer parentItem;
    
    void *p = parent.internalPointer();
    parentItem = *static_cast<OutputComponent::SharedPointer *>(p);
    return parentItem;
  }
}