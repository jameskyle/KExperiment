#include "ComponentModelInterface.h"

namespace kex
{
        ComponentModelInterface::ComponentModelInterface(QObject *parent)
                : QAbstractTableModel(parent)
        {

        }

        int ComponentModelInterface::rowCount(const QModelIndex &parent) const
        {
          return 0;
        }

        int ComponentModelInterface::columnCount(const QModelIndex &index,
                                                                                                                                                                         int role) const
        {
          return 0;
        }

        QVariant ComponentModelInterface::data(const QModelIndex &index,
                                                                                                                                                                 int role) const
        {
          return QVariant();
        }

        QVariant ComponentModelInterface::headerData(int section,
                                                Qt::Orientation orientation,
                                                int role) const
        {
          return QVariant();
        }

}
