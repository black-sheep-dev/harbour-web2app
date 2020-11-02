#ifndef APP_H
#define APP_H

#include <QObject>

class App : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)

public:
    explicit App(QObject *parent = nullptr);

    QString name() const;
    QString url() const;

signals:
    void nameChanged(const QString &name);
    void urlChanged(const QString &url);

public slots:
    void setName(const QString &name);
    void setUrl(const QString &url);

private:
    QString m_name;
    QString m_url;
};

#endif // APP_H
