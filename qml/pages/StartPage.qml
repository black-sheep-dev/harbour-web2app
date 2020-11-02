import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.web2app 1.0

Page {
    id: page

    allowedOrientations: Orientation.All

    SilicaListView {
        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
            MenuItem {
                text: qsTr("Add Web App")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditAppDialog.qml"))
                    dialog.accepted.connect(function() {
                        Web2App.addApp(dialog.name, dialog.url)
                        Web2App.saveApps()
                    })
                }
            }
        }

        id: listView
        model: AppsSortFilterModel {
            id: sortModel
            sourceModel: Web2App.appsModel()

            //Component.onCompleted: sortModel.sort()
        }

        anchors.fill: parent
        header: PageHeader {
            title: qsTr("Web Apps")
        }
        delegate: ListItem {
            id: delegate

            width: parent.width
            contentHeight: Theme.itemSizeLarge


            menu: ContextMenu {
                MenuItem {
                    text: qsTr("Delete");
                    onClicked: remorse.execute(delegate, qsTr("Delete app"), function() {
                        console.log("delete")
                    })
                }
                MenuItem {
                    text: qsTr("Edit");
                    onClicked: {
                        var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditAppDialog.qml"), {
                                                        edit: true,
                                                        name: model.name,
                                                        url: model.url
                                                    })

                        dialog.accepted.connect(function() {
                            model.name = dialog.name
                            model.url = dialog.url
                            Web2App.saveApps()
                        })
                    }
                }
            }

            RemorseItem { id: remorse }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * x
                height: parent.height
                anchors.verticalCenter: parent.verticalCenter

                Image {
                    id: appIcon

                    height: parent.height - 2*Theme.paddingSmall
                    width: height
                    anchors.verticalCenter: parent.verticalCenter

                     smooth: true

                    source: "image://theme/harbour-web2app"
                }

                Item {
                    width: Theme.paddingMedium
                    height: 1
                }

                Column {
                    width: parent.width - appIcon.width - Theme.paddingMedium
                    anchors.verticalCenter: parent.verticalCenter

                    Label {
                        width: parent.width
                        text: name
                        color: pressed ? Theme.secondaryHighlightColor : Theme.highlightColor
                        font.pixelSize: Theme.fontSizeLarge
                    }
                    Label {
                        text: url

                        color: Theme.secondaryColor
                        font.pixelSize: Theme.fontSizeMedium
                    }
                }
            }

            onClicked: console.log("Clicked " + index)
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            text: qsTr("No apps available")
            hintText: qsTr("Pull down to create new web apps")
        }

        VerticalScrollDecorator {}
    }

    onVisibleChanged: Web2App.loadApps();
}
