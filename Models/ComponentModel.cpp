#include "ComponentModel.h"

namespace kex
{
  ComponentModel& ComponentModel::globalInstance()
  {
    static ComponentModel model;
    return model;
  }

  ComponentModel::ComponentModel(Component::ComponentList *c_list, QObject *parent)
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
      Component::Pointer p = getItem(parent);
      Q_CHECK_PTR(p);

      if(p->componentType() & ~Component::ActionType)
      {
        ComponentCollection::Pointer collection = getCollectionItem(parent);
        count = collection->components().size();
      }

    } else
    {
      count = m_components.size();
    }

    return count;
  }

  int ComponentModel::columnCount(const QModelIndex &parent) const
  {
    return 5;
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
      Component::Pointer component;

      if (!index.parent().isValid())
      {
        Component::ComponentList::iterator it(m_components.begin());
        component = it[index.row()].data();
      } else
      {
        component = getItem(index);
        // if the index isValid() we should always get a valid component
        Q_CHECK_PTR(component);
      }

      if (role == Qt::DisplayRole  || role == Qt::EditRole)
      {
        switch (index.column())
        {
          case 0:
            result.setValue(component->name());
            break;
          case 1:
            result.setValue(component->mainCategory());
            break;
          case 2:
            result.setValue(component->label());
            break;
          case 3:
            result.setValue(component->description());
            break;
          case 4:
          {
            QTime time(0,0,0);
            result.setValue(time.addMSecs(component->durationMSecs())
                            .toString("mm:ss.zzz"));
          }
            break;
          default:
            break;
        }
      }
    }
      return result;
  }

  QModelIndex ComponentModel::parent(const QModelIndex &index) const
  {
    Q_ASSERT(index.isValid());
    QModelIndex p_index;

    if(index.isValid())
    {
      Component::Pointer p = getItem(index);
      Component::Pointer pp = p->parentComponent();
      if(pp)
      {
        ComponentCollection::Pointer pp;
        pp = qobject_cast<ComponentCollection::Pointer>(p->parentComponent());
        Q_CHECK_PTR(pp);
        int row = getIndexForItem(pp->components(), p);
        p_index = createIndex(row, 0, pp);
      }
    }

    return p_index;
  }

  QModelIndex
  ComponentModel::index(int row, int column, const QModelIndex &parent) const
  {
    QModelIndex ind;

    if(parent.isValid())
    {
      ComponentCollection::Pointer pp = getCollectionItem(parent);
      Q_ASSERT(pp->componentType() & ~Component::ActionType);
      ind = createIndex(row, column, (pp->components()[row]).data());
    } else {
      ind = createIndex(row, column, (m_components[row]).data());
    }
    return ind;
  }

  Component::Pointer
  ComponentModel::getItem(const QModelIndex& index) const
  {
    Component::Pointer parentItem;
    void *p = index.internalPointer();
    parentItem = static_cast<Component::Pointer>(p);
    Q_CHECK_PTR(parentItem);
    return parentItem;
  }

  ComponentCollection::Pointer
  ComponentModel::getCollectionItem(const QModelIndex& index) const
  {
    Q_ASSERT(index.isValid());
    ComponentCollection::Pointer collection;

    void *p = index.internalPointer();
    collection = static_cast<ComponentCollection::Pointer>(p);
    Component::ComponentTypes t  = collection->componentType();
    Q_ASSERT(collection->componentType() & ~Component::ActionType);
    return collection;
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

  int ComponentModel::getIndexForItem(const Component::ComponentList& list,
                                      Component::Pointer component) const
  {
    int index(-1);
    Component::SharedPointer p;

    for(int i =0;i < list.size(); ++i)
    {
      p = list[i];
      if(component == p.data())
      {
        index = i;
        break;
      }
    }

    return index;
  }

}
