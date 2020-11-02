#ifndef APPSSORTFILTERMODEL_H
#define APPSSORTFILTERMODEL_H

#include <QSortFilterProxyModel>

#include "appsmodel.h"

class AppsSortFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit AppsSortFilterModel(QObject *parent = nullptr);

    Q_INVOKABLE void sortModel();

    // QAbstractProxyModel interface
public:
    void setSourceModel(QAbstractItemModel *sourceModel) override;
};

#endif // APPSSORTFILTERMODEL_H
