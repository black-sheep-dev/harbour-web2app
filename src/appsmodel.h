#ifndef APPSMODEL_H
#define APPSMODEL_H

#include <QAbstractListModel>

#include "app.h"

class AppsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum AppRoles {
        NameRole        = Qt::UserRole + 1,
        UrlRole,
        IdxRole
    };
    Q_ENUM(AppRoles)

    explicit AppsModel(QObject *parent = nullptr);

    Q_INVOKABLE void addApp(App *app);
    QList<App *> apps() const;
    void removeApp(App *app);
    void setApps(const QList<App *> &apps);

private:
    QList<App *> m_apps;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;

};

#endif // APPSMODEL_H
