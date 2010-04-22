#include "ComponentModel.h"

namespace kex
{
	ComponentModel::ComponentModel(Config::ApplicationDataDirectoryType component,
																 QObject *parent) : QFileSystemModel(parent)
	{
		// set the root path according to the specified application directory
		setRootPath(Config::instance().dataDirectoryPath(component));
		
		// We only want *.xml files
		setFilter(QDir::Files | QDir::NoSymLinks);
		QStringList filters;
		filters << "*.xml";
		//setNameFilters(filters);
		Logger::instance().log(qPrintable(Config::instance().dataDirectoryPath(component)));
	}
	
	QVariant ComponentModel::data(const QModelIndex &index, int role) const
	{
		QVariant result;
		QString foo("%1");

		if (role == QFileSystemModel::FileIconRole)
		{
			QIcon icon(":/other/images/other/Science-64.png");
			result = icon;
		} else if (role == Qt::DisplayRole)
		{
			result = "foo fucker";
		} else
		{
			result = QFileSystemModel::data(index,role);
		}

		return result;
	}
}
