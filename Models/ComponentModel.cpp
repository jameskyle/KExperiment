#include "ComponentModel.h"

namespace kex
{
  ComponentModel::ComponentModel(OutputComponent::ComponentTypes types, 
                                 QObject *parent) 
    : QAbstractItemModel(parent),
      _componentList(ComponentList::instance())
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
      
    } else
    {
      count = _componentList.count();
    }

//    if (parent.isValid())
//    {
//      OutputComponent::SharedPointer sp = getItem(parent);
//      
//      count = sp->numChildren();
//      
//    } else
//    {
//      count = _componentList.count();
//    }

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
//      OutputComponent::SharedPointer sp = getItem(parent);
//      count = sp->numChildren();
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
      ComponentList::Node::Pointer node;
      if (!index.parent().isValid())
      {
        node = &_componentList[index.row()];
      } else
      {
        node = getItem(index);
      }

      if (role == Qt::DisplayRole)
      {
        if (index.column() == 0)
        {
          result.setValue(node->component()->name());
        } else if (index.column() == 1)
        {
          result.setValue(node->component()->mainCategory());
        }
      }
    }
      return result;
  }
  
  QModelIndex ComponentModel::parent(const QModelIndex &index) const 
  {
    QModelIndex p_index;
    
    if (index.isValid())
    {
      ComponentList::Node::Pointer node = getItem(index);
      ComponentList::Node::Pointer p_node;
      p_node = node->parentComponent();
      
      if (p_node)
      {
        p_index = createIndex(0,0, p_node); 
      }
    }
    return p_index;
  }
  
  QModelIndex 
  ComponentModel::index(int row, int column, const QModelIndex &parent) const
  {
    QModelIndex ind;
    
  //  if(hasIndex(row, column, parent))
//    {
//      if(parent.isValid())
//      {
//        OutputComponent::SharedPointer parentItem = getItem(parent);
//        
//        OutputComponent::SharedPointer *child;
//        child = new OutputComponent::SharedPointer;
//        *child = parentItem->child(row);
//        
//        if (*child)
//        {
//          ind = createIndex(row, column, child);
//        }
//        
//      } else
//      {
//        OutputComponent::SharedPointer *sp = new OutputComponent::SharedPointer;
//        *sp = _componentList[row];
//        ind = createIndex(row, column, sp);
//      }
//
//    }
    
    return ind;
  }
  
  ComponentList::Node::Pointer 
  ComponentModel::getItem(const QModelIndex& index) const
  {
    ComponentList::Node::Pointer parentItem;
    
    void *p = index.internalPointer();
    parentItem = static_cast<ComponentList::Node::Pointer>(p);
    return parentItem;
  }
}