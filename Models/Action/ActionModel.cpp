#include "ActionModel.h"

namespace kex
{
	ActionModel::ActionModel(QObject *parent) : QAbstractItemModel(parent)
	{
		// We always parse the default application templates first
		
	}
	
	void ActionModel::setData(const QStringList& resourceList)
	{
	}
}
