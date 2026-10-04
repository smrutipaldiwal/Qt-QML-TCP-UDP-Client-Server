import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow { id: window

    width: 800
    height: 600
    visible: true
    title: "TCP / UDP Client"

    property bool formOpen: false
    property bool editMode: false
    property int editId: -1
    property string statusText: "Ready"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 12

        Label {
            text: "Data List"
            font.pixelSize: 26
            font.bold: true
        }

        Label {
            text: statusText
            color: "#555555"
        }

        ListView {
            id: recordList

            Layout.fillWidth: true
            Layout.fillHeight: true

            model: clientController.records
            clip: true

            delegate: Rectangle {
                width: recordList.width
                height: 72
                radius: 6
                border.width: 1
                border.color: "#cccccc"

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 10

                    ColumnLayout {
                        Layout.fillWidth: true

                        Label {
                            text: "ID: " + modelData.uniqueID
                            font.bold: true
                        }

                        Label {
                            text: "Lat: " + Number(modelData.lat).toFixed(4)
                                + "   Long: " + Number(modelData.longitude).toFixed(4)
                        }

                        Label {
                            text: modelData.comment
                            elide: Text.ElideRight
                            Layout.fillWidth: true
                        }
                    }

                    Button {
                        text: "Update"

                        onClicked: {
                            window.editMode = true
                            window.editId = modelData.uniqueID

                            recordForm.uniqueID = modelData.uniqueID
                            recordForm.lat = modelData.lat
                            recordForm.longitude = modelData.longitude
                            recordForm.comment = modelData.comment

                            window.formOpen = true
                        }
                    }

                    Button {
                        text: "Delete"

                        onClicked: {
                            clientController.deleteRecord(modelData.uniqueID)
                            window.statusText = "Delete request sent. Waiting for ACK..."
                        }
                    }
                }
            }

            Label {
                anchors.centerIn: parent
                visible: clientController.records.length === 0
                text: "No records yet. Click Add."
                color: "#777777"
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Button {
                text: "Add"

                onClicked: {
                    window.editMode = false
                    window.editId = -1

                    recordForm.uniqueID = 0
                    recordForm.lat = 0
                    recordForm.longitude = 0
                    recordForm.comment = ""

                    window.formOpen = true
                }
            }
        }
    }

    RecordForm {
        id: recordForm

        visible: window.formOpen
        anchors.centerIn: parent
        editMode: window.editMode

        onApplyClicked: {
            if (editMode) {
                clientController.updateRecord(
                    uniqueID, lat, longitude, comment
                )

                window.statusText =
                    "Update request sent. Waiting for ACK..."
            } else {
                clientController.addRecord(
                    uniqueID, lat, longitude, comment
                )

                window.statusText =
                    "Add request sent. Waiting for ACK..."
            }

            window.formOpen = false
        }

        onCancelClicked: {
            window.formOpen = false
        }
    }

    Connections {
        target: clientController

        function onRecordChanged() {
            window.statusText = "Server ACK received. List updated."
        }
    }
}