#include "ComponentModel.h"

namespace kex
{
  ComponentModel& ComponentModel::globalInstance()
  {
    static ComponentModel model;
    return model;
  }

  ComponentModel::ComponentModel(ComponentList *c_list, QObject *parent)
    : QAbstractItemModel(parent),
      m_components(*c_list)
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
          result.setValue(QString("Duration"));
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
      ComponentList::Node::Pointer node = getItem(parent);
      // if the index isValid() we should always get a valid node
      Q_CHECK_PTR(node);

      count = node->children().size();

    } else
    {
      count = m_components.size();
    }

    return count;
  }

  int ComponentModel::columnCount(const QModelIndex &parent) const
  {
    int count(4);

    if (parent.isValid())
    {
      count = 5;
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
        ComponentList::iterator it(m_components.begin());
        node = it[index.row()];
      } else
      {
        node = getItem(index);
        // if the index isValid() we should always get a valid node
        Q_CHECK_PTR(node);

      }

      if (role == Qt::DisplayRole  || role == Qt::EditRole)
      {
        switch (index.column())
        {
          case 0:
            result.setValue(node->component()->name());
            break;
          case 1:
            result.setValue(node->component()->mainCategory());
            break;
          case 2:
            result.setValue(node->component()->label());
            break;
          case 3:
            result.setValue(node->component()->description());
            break;
          case 4:
          {
            QTime time(0,0,0);
            result.setValue(time.addMSecs(node->durationMSecs())
                            .toString("mm:ss.zzz"));
          }
            break;
          default:
            break;
        }
      }    }
      return result;
  }

  QModelIndex ComponentModel::parent(const QModelIndex &index) const
  {
    QModelIndex p_index;

    if (index.isValid())
    {
      ComponentList::Node::Pointer node = getItem(index);
      // if the index isValid() we should always get a valid node
      Q_CHECK_PTR(node);
      ComponentList::Node::Pointer p_node;
      p_node = node->parent();

      if (p_node)
      {
        p_index = createIndex(p_node->position(),0, p_node);
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
        ComponentList::Node::Pointer parentItem = getItem(parent);
        // if the index isValid() we should always get a valid node
        Q_CHECK_PTR(parentItem);

        ComponentList::iterator it(parentItem->children().begin());
        it += row;

        if (it != parentItem->children().end())
        {
          ind = createIndex(row, column, *it);
        }

      } else
      {
        ComponentList::iterator it(m_components.begin() + row);
        // make sure the requested node/row is valid
        if (it != m_components.end())
        {
          ind = createIndex(row, column, (*it));
        }
      }

    }

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

  Qt::ItemFlags ComponentModel::flags(const QModelIndex &index) const
  {
    Qt::ItemFlags flags(QAbstractItemModel::flags(index));

    if (index.parent().isValid())
    {
      flags = Qt::ItemIsEnabled;
    }
    return flags;
  }
}
