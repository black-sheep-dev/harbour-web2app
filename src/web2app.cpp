#include "web2app.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QSettings>
#include <QStandardPaths>
#include <QTextStream>

Web2App::Web2App(QObject *parent) :
    QObject(parent),
    m_appsModel(new AppsModel(this))
{
    loadApps();
}

Web2App::~Web2App()
{
    saveApps();
}

void Web2App::addApp(const QString &name, const QString &url)
{
    auto *app = new App;
    app->setName(name);
    app->setUrl(url);

    m_appsModel->addApp(app);
}

AppsModel *Web2App::appsModel()
{
    return m_appsModel;
}

void Web2App::initialize()
{

}

void Web2App::loadApps()
{
    QDirIterator it(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
                    + QStringLiteral("/.local/share/applications/"),
                    QStringList() << QStringLiteral("*.desktop"),
                    QDir::Files,
                    QDirIterator::NoIteratorFlags);

    QList<App *> apps;
    while (it.hasNext()) {
        const QFileInfo info = QFileInfo(it.next());

        if ( info.suffix() != QLatin1String("desktop")
             || !info.baseName().startsWith(APP_TARGET) ) {
            continue;
        }

#ifdef QT_DEBUG
    qDebug() << info.fileName();
    qDebug() << info.filePath();
#endif

        auto *app = readDesktopFile(info.filePath());

        if (app == nullptr)
            continue;

        apps.append(app);
    }

    m_appsModel->setApps(apps);
}

void Web2App::removeApp(App *app)
{
    if (app == nullptr)
        return;

    QFile file(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
               + QStringLiteral("/.local/share/applications/")
               + APP_TARGET
               + QStringLiteral("-")
               + app->name().toLower()
               + QStringLiteral(".desktop"));

    if (!file.remove())
        return;

    m_appsModel->removeApp(app);
}

void Web2App::saveApps()
{
    const QList<App *> apps = m_appsModel->apps();
    for (const auto *app : apps) {
        writeDesktopFile(app);
    }
}

App *Web2App::readDesktopFile(const QString &path)
{
    QSettings file(path, QSettings::IniFormat);
    file.beginGroup(QStringLiteral("Desktop Entry"));

    const QString name = file.value(QStringLiteral("Name")).toString();
    if (name.isEmpty())
        return nullptr;

    const QString url = file.value(QStringLiteral("Exec")).toString().split(" ").last();
    if (url.isEmpty())
        return nullptr;

    file.endGroup();

    auto *app = new App;
    app->setName(name);
    app->setUrl(url);

    return app;
}

void Web2App::writeDesktopFile(const App *app)
{
    QFile file(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
               + QStringLiteral("/.local/share/applications/")
               + APP_TARGET
               + QStringLiteral("-")
               + app->name().toLower()
               + QStringLiteral(".desktop"));

#ifdef QT_DEBUG
    qDebug() << file.fileName();
#endif

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << QStringLiteral("[Desktop Entry]\n");
    out << QStringLiteral("Type=Application\n");
    out << QStringLiteral("X-Nemo-Application-Type=browser\n");
    out << QStringLiteral("Icon=harbour-web2app\n");
    out << QString("Exec=harbour-web2app %1\n").arg(app->url());
    //out << QString("Exec=/home/nemo/.local/bin/harbour-web2app-launcher.sh %1\n").arg(app->url());
    out << QString("Name=%1").arg(app->name());
}
