#include "ComponentLibrary.h"

namespace kex
{
	ComponentLibrary::ComponentLibrary(QWidget *parent)
	: QDockWidget(parent)
	{
		setupUi(this);
	}
	
	ComponentLibrary::~ComponentLibrary() {
	}
}