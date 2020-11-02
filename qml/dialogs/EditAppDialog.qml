import QtQuick 2.2
import Sailfish.Silica 1.0

Dialog {
    property bool edit: false
    property string name
    property string url

    id: dialog

    Column {
        width: parent.width
        spacing: Theme.paddingMedium

        DialogHeader {
            title: edit ? qsTr("Edit Web App") : qsTr("Add Web App")

            acceptText: edit ? qsTr("Save") : qsTr("Add")
        }

        TextField {
            id: nameField

            x: Theme.horizontalPageMargin
            width: parent.width - 2*x

            label: qsTr("Name")
            placeholderText: qsTr("Enter name")

            text: name

            validator: RegExpValidator {
                regExp: /^.{1,}$/
            }

            focus: !edit

            EnterKey.iconSource: "image://theme/icon-m-enter-next"
            EnterKey.onClicked: urlField.focus = true

            onTextChanged: checkInput()
        }

        TextField {
            id: urlField

            x: Theme.horizontalPageMargin
            width: parent.width - 2*x

            label: qsTr("Url")
            placeholderText: qsTr("Enter url like http(s)://example.org")

            text: url

            inputMethodHints: Qt.ImhUrlCharactersOnly
            validator: RegExpValidator {
                regExp: /((((http|https):(?:\/\/)?)(?:[\-;:&=\+\$,\w]+@)?[A-Za-z0-9\.\-]+|(?:www\.|[\-;:&=\+\$,\w]+@)[A-Za-z0-9\.\-]+)((?:\/[\+~%\/\.\w\-_]*)?\??(?:[\-\+=&;%@\.\w_]*)#?(?:[\.\!\/\\\w]*))?)/
            }

            EnterKey.iconSource: "image://theme/icon-m-enter-next"
            EnterKey.onClicked: focus = false

            autoScrollEnabled: true

            onTextChanged: checkInput()
        }
    }

    function checkInput() {
        canAccept = nameField.acceptableInput && urlField.acceptableInput
    }

    onAccepted: {
        name = nameField.text
        url = urlField.text
    }
}
