#include "ComponentModel.h"

namespace kex
{
  ComponentModel::ComponentModel(Config::ApplicationDataDirectoryType component,
                                 QObject *parent)
  : QAbstractListModel(parent),
    _rootPath(Config::instance().dataDirectoryPath(component))
  {
    _rootPath.setFilter(QDir::Files | QDir::NoSymLinks);
    // We only want *.xml files
    QStringList filters;
    filters << "*.xml";
    _rootPath.setNameFilters(filters);
    _rootPath.setSorting(QDir::Name);
  }

  int ComponentModel::rowCount(const QModelIndex &parent) const
  {
    return _rootPath.count();
  }

  QVariant ComponentModel::data(const QModelIndex &index, int role) const
  {
    QVariant result;

    if (role == Qt::DecorationRole)
    {
      QIcon icon(":/other/images/other/Science-64.png");
      result = icon;
    } else if (role == Qt::DisplayRole)
    {
      result = _rootPath.entryList()[index.row()];
      QString st(result.toString());
      result = st.replace(".xml","").replace("_"," ");
    }

    return result;
  }

  void ComponentModel::updateComponentList()
  {
    _rootPath.refresh();
  }
}
