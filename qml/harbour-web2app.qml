import QtQuick 2.0
import Sailfish.Silica 1.0
import "pages"

import org.nubecula.harbour.web2app 1.0

ApplicationWindow
{
    initialPage: {
        if (Qt.application.arguments[1] === undefined) {
            return Qt.createComponent("pages/StartPage.qml")
        } else {
            var component = Qt.createComponent("pages/WebViewPage.qml")
            //component.url = Qt.application.arguments[1]
            return component
        }
    }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations

    Component.onCompleted: Web2App.initialize()
}
