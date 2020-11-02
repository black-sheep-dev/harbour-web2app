#include <QtQuick>

#include <sailfishapp.h>

#include "web2app.h"
#include "appssortfiltermodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationVersion(APP_VERSION);
    QCoreApplication::setOrganizationName(QStringLiteral("nubecula.org"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("nubecula.org"));

    qmlRegisterType<App>("org.nubecula.harbour.web2app", 1, 0, "App");
    qmlRegisterType<AppsModel>("org.nubecula.harbour.web2app", 1, 0, "AppsModel");
    qmlRegisterType<AppsSortFilterModel>("org.nubecula.harbour.web2app", 1, 0, "AppsSortFilterModel");

    qmlRegisterSingletonType<Web2App>("org.nubecula.harbour.web2app",
                                      1,
                                      0,
                                      "Web2App",
                                      [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {

        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        auto *manager = new Web2App();

        return manager;
    });

    return SailfishApp::main(argc, argv);
}
