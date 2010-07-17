#ifndef COMPONENTSORTFILTERPROXYMODEL_H
#define COMPONENTSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QAction>

#include "Components/OutputComponent.h"
#include "Components/ComponentList.h"

namespace kex
{
  class ComponentSortFilterProxyModel : public QSortFilterProxyModel
  {
    Q_OBJECT
    
  public:
    ComponentSortFilterProxyModel(QObject *parent = 0);
    
    OutputComponent::ComponentTypes 
      filterComponentType() const { return m_type; }
    
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

    void setFilterComponentType(const OutputComponent::ComponentTypes& t)
    {
      m_type = t;
      invalidateFilter();
    }
    
  protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
    
  private:
    OutputComponent::ComponentTypes m_type;
  };
}
#endif