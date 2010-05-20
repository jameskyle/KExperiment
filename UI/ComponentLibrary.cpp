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

  void ComponentLibrary::setModel(QAbstractItemModel *model)
  {
    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);

    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setSourceModel(model);

    componentListView->setModel(proxy);

    connect(filterLineEdit, SIGNAL(textChanged(QString)),
            proxy,          SLOT(setFilterFixedString(QString)));
  }

}
