#include "appsmodel.h"

AppsModel::AppsModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

void AppsModel::addApp(App *app)
{
    if (app == nullptr)
        return;

    app->setParent(this);

    beginInsertRows(QModelIndex(), m_apps.count(), m_apps.count());
    m_apps.append(app);
    endInsertRows();
}

QList<App *> AppsModel::apps() const
{
    return m_apps;
}

void AppsModel::removeApp(App *app)
{
    const int idx = m_apps.indexOf(app);

    if (idx < 0)
        return;

    beginRemoveRows(QModelIndex(), idx, idx);
    m_apps.takeAt(idx)->deleteLater();
    endRemoveRows();
}

void AppsModel::setApps(const QList<App *> &apps)
{
    beginResetModel();
    if (!m_apps.isEmpty())
        qDeleteAll(m_apps.begin(), m_apps.end());

    QList<App *> list;
    for (auto *app : apps) {
        if (app == nullptr)
            continue;

        app->setParent(this);
        list.append(app);
    }

    m_apps = list;
    endResetModel();
}

int AppsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_apps.count();
}

QVariant AppsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto *app = m_apps.at(index.row());

    switch (role) {
    case NameRole:
        return app->name();

    case UrlRole:
        return app->url();

    case IdxRole:
        return index.row();

    default:
        return QVariant();
    }
}

bool AppsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    auto *app = m_apps.at(index.row());

    switch (role) {
    case NameRole:
        app->setName(value.toString());
        break;

    case UrlRole:
        app->setUrl(value.toString());
        break;

    default:
        return false;
    }

    emit dataChanged(index, index);

    return true;
}

QHash<int, QByteArray> AppsModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[NameRole]     = "name";
    roles[UrlRole]      = "url";
    roles[IdxRole]      = "idx";

    return roles;
}
