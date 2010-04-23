#include "ComponentLibrary.h"
#include <QTimer>
namespace kex
{
  ComponentLibrary::ComponentLibrary(QWidget *parent)
  : QDockWidget(parent)
  {
    setupUi(this);
    componentListView->setGridSize(QSize(-1,-1));
  }
  
  ComponentLibrary::~ComponentLibrary() {
  }
  
  void ComponentLibrary::setModel(ComponentModel *model)
  {
    componentListView->setModel(model);
    componentListView->setRootIndex(model->index(model->rootPath()));
    
    connect(filterLineEdit, SIGNAL(textChanged(QString)), 
            model,          SLOT(updateFilter(QString)));
  }
}