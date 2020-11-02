# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# VERSION
VERSION = 0.1.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# The name of your application
TARGET = harbour-web2app
DEFINES += APP_TARGET=\\\"$$TARGET\\\"

CONFIG += link_pkgconfig sailfishapp
PKGCONFIG += qt5embedwidget

SOURCES += src/harbour-web2app.cpp \
    src/app.cpp \
    src/appsmodel.cpp \
    src/appssortfiltermodel.cpp \
    src/web2app.cpp

DISTFILES += qml/harbour-web2app.qml \
    qml/cover/CoverPage.qml \
    qml/dialogs/EditAppDialog.qml \
    qml/pages/StartPage.qml \
    qml/pages/WebViewPage.qml \
    rpm/harbour-web2app.changes.in \
    rpm/harbour-web2app.changes.run.in \
    rpm/harbour-web2app.spec \
    rpm/harbour-web2app.yaml \
    translations/*.ts \
    harbour-web2app.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172 512x512

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-web2app-de.ts

RESOURCES += \
    ressources.qrc

HEADERS += \
    src/app.h \
    src/appsmodel.h \
    src/appssortfiltermodel.h \
    src/web2app.h
