#include "ComponentLibrary.h"
#include <QTimer>

namespace kex
{
  ComponentLibrary::ComponentLibrary(QWidget *parent)
  : QDockWidget(parent)
  {
    setupUi(this);
    componentListView->setGridSize(QSize(-1,-1));
    componentListView->setIconSize(QSize(32,32));
  }

  ComponentLibrary::~ComponentLibrary() {
  }

  void ComponentLibrary::setModel(QAbstractItemModel *model, 
                                  OutputComponent::ComponentTypes c_type)
  {
    ComponentSortFilterProxyModel *proxy;
    proxy = new ComponentSortFilterProxyModel(this);
    
    
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setSourceModel(model);
    proxy->setFilterComponentType(c_type);

    componentListView->setModel(proxy);

    connect(filterLineEdit, SIGNAL(textChanged(QString)),
            proxy,          SLOT(setFilterFixedString(QString)));
  }

}
