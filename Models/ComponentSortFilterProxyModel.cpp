#include "ComponentSortFilterProxyModel.h"

namespace kex
{
  ComponentSortFilterProxyModel::ComponentSortFilterProxyModel(QObject *parent)
  : QSortFilterProxyModel(parent),
    m_type(Component::AllComponents)
  {
  }
  
  bool ComponentSortFilterProxyModel::filterAcceptsRow(int sourceRow, 
                                        const QModelIndex &sourceParent) const
  {
    bool result(false);
    QModelIndex index;
    QRegExp exp = filterRegExp();

    index = sourceModel()->index(sourceRow, 0, sourceParent);
    
    if (index.isValid())
    {
      ComponentList::Node::Pointer parentItem;
      
      void *p = index.internalPointer();
      parentItem = static_cast<ComponentList::Node::Pointer>(p);
      
      result = (parentItem->component()->componentType() & m_type);
      
      // sort by search box
      if (!exp.isEmpty() && exp.indexIn(index.data().toString()) < 0)
      {
        result = false;
      }
    }
    
    return result;
  }
  
  bool ComponentSortFilterProxyModel::lessThan(const QModelIndex &left, 
                                               const QModelIndex &right) const
  {
    bool result;
    
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);
    
    result = (QString::localeAwareCompare(leftData.toString(),
                                          rightData.toString()) < 0);
    
    return result;
  }
  
}