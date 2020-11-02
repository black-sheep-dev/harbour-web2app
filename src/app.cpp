#include "app.h"

App::App(QObject *parent) : QObject(parent)
{

}

QString App::name() const
{
    return m_name;
}

QString App::url() const
{
    return m_url;
}

void App::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void App::setUrl(const QString &url)
{
    if (m_url == url)
        return;

    m_url = url;
    emit urlChanged(m_url);
}
