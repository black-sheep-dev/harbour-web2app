#include "appssortfiltermodel.h"

AppsSortFilterModel::AppsSortFilterModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    setSortRole(AppsModel::NameRole);
    setDynamicSortFilter(true);
}

void AppsSortFilterModel::sortModel()
{
    this->sort(0, Qt::AscendingOrder);
}

void AppsSortFilterModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    QSortFilterProxyModel::setSourceModel(sourceModel);

    sortModel();
}
