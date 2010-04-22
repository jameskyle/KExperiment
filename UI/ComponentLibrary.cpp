#include "ComponentLibrary.h"
#include <QTimer>
namespace kex
{
	ComponentLibrary::ComponentLibrary(QWidget *parent)
	: QDockWidget(parent)
	{
		setupUi(this);
	}
	
	ComponentLibrary::~ComponentLibrary() {
	}
	
	void ComponentLibrary::setModel(ComponentModel *model)
	{
		componentListView->setModel(model);
		componentListView->setRootIndex(model->index(model->rootPath()));
	}
	
	
}