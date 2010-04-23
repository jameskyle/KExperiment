#include "ComponentModel.h"

namespace kex
{
  ComponentModel::ComponentModel(Config::ApplicationDataDirectoryType component,
                                 QObject *parent) 
  : QFileSystemModel(parent),
    _filter("")
  {
    // set the root path according to the specified application directory
    setRootPath(Config::instance().dataDirectoryPath(component));

    // We only want *.xml files
    setFilter(QDir::Files | QDir::NoSymLinks);
    QStringList filters;
    filters << "*.xml";
    setNameFilters(filters);
  }

  QVariant ComponentModel::data(const QModelIndex &index, int role) const
  {
    QVariant result;

    if (role == QFileSystemModel::FileIconRole)
    {
      QIcon icon(":/other/images/other/Science-64.png");
      result = icon;
    } else if (role == Qt::DisplayRole)
    {
      result = QFileSystemModel::data(index, role);
      QString st(result.toString());
      result = st.replace(".xml","").replace("_"," ");
    } else
    {
      result = QFileSystemModel::data(index,role);
    }

    return result;
  }
  
  void ComponentModel::updateFilter(QString filter)
  {
    _filter = filter;
    emit layoutChanged();
    Logger::instance().log("filter changed");
  }
}
