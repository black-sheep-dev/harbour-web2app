#ifndef WEB2APP_H
#define WEB2APP_H

#include <QObject>

#include "appsmodel.h"

class Web2App : public QObject
{
    Q_OBJECT

public:
    explicit Web2App(QObject *parent = nullptr);
    ~Web2App() override;

    Q_INVOKABLE void addApp(const QString &name, const QString &url);
    Q_INVOKABLE AppsModel *appsModel();
    Q_INVOKABLE void initialize();
    Q_INVOKABLE void loadApps();
    Q_INVOKABLE void removeApp(App *app);
    Q_INVOKABLE void saveApps();

private:
    App *readDesktopFile(const QString &path);
    void writeDesktopFile(const App *app);

    AppsModel *m_appsModel{nullptr};
};

#endif // WEB2APP_H
