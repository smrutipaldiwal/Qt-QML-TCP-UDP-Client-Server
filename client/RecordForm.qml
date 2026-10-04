import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle { id: form

    width: 430
    height: 370

    radius: 10
    border.width: 1
    border.color: "#aaaaaa"
    color: "white"

    property bool editMode: false
    property int uniqueID: 0
    property real lat: 0
    property real longitude: 0
    property string comment: ""

    signal applyClicked()
    signal cancelClicked()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 12

        Label {
            text: editMode ? "Update Record" : "Add Record"
            font.pixelSize: 22
            font.bold: true
        }

        TextField {
            id: idField

            Layout.fillWidth: true
            placeholderText: "Unique ID"
            text: String(form.uniqueID)
            inputMethodHints: Qt.ImhDigitsOnly

            onTextChanged: {
                if (activeFocus)
                    form.uniqueID = Number(text)
            }
        }

        TextField {
            id: latField

            Layout.fillWidth: true
            placeholderText: "Latitude"
            text: String(form.lat)

            onTextChanged: {
                if (activeFocus)
                    form.lat = Number(text)
            }
        }

        TextField {
            id: longField

            Layout.fillWidth: true
            placeholderText: "Longitude"
            text: String(form.longitude)

            onTextChanged: {
                if (activeFocus)
                    form.longitude = Number(text)
            }
        }

        TextField {
            id: commentField

            Layout.fillWidth: true
            placeholderText: "Comment (maximum 49 characters)"
            text: form.comment
            maximumLength: 49

            onTextChanged: {
                form.comment = text
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Button {
                text: "Apply"
                Layout.fillWidth: true

                onClicked: {
                    form.uniqueID = Number(idField.text)
                    form.lat = Number(latField.text)
                    form.longitude = Number(longField.text)
                    form.comment = commentField.text

                    form.applyClicked()
                }
            }

            Button {
                text: "Cancel"
                Layout.fillWidth: true

                onClicked: {
                    form.cancelClicked()
                }
            }
        }
    }

    // When a form is opened, copy the current properties into the fields.
    onUniqueIDChanged: {
        if (!idField.activeFocus)
            idField.text = String(uniqueID)
    }

    onLatChanged: {
        if (!latField.activeFocus)
            latField.text = String(lat)
    }

    onLongitudeChanged: {
        if (!longField.activeFocus)
            longField.text = String(longitude)
    }

    onCommentChanged: {
        if (!commentField.activeFocus)
            commentField.text = comment
    }
}