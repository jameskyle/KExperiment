#include "ComponentModel.h"

namespace kex
{
  ComponentModel::ComponentModel(OutputComponent::ComponentTypes types, 
                                 QObject *parent) 
    : QAbstractTableModel(parent),
      _componentList(ComponentList::instance().filter(types))
  {
  }

  int ComponentModel::rowCount(const QModelIndex & /* parent */) const
  {
    return _componentList.count();
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
      OutputComponent *comp = _componentList[index.row()];
      result = comp->icon();
    } else if (role == Qt::DisplayRole)
    {
      if (index.row()     < _componentList.count() &&
          index.row()     >= 0 &&
          index.column()  >= 0 &&
          index.column()  < columnCount())
      {
        OutputComponent *comp = _componentList[index.row()];
        
        if (index.column() == 0)
        {
          result.setValue(comp->name());
        } else if (index.column() == 1)
        {
          
          result.setValue(
            AbstractComponent::componentTypeToString(comp->componentType()));
        } else if (index.column() == 2)
        {
          result.setValue(comp->label());
        } else if (index.column() == 3)
        {
          result.setValue(comp->description());
        } else if (index.column() == 4)
        {
          result.setValue(comp->durationMSecs());
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

}
