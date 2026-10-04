import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: window
    width: 900
    height: 600
    minimumWidth: 800
    minimumHeight: 460
    visible: true
    title: "TCP / UDP Client"

    property bool formOpen: false
    property bool editMode: false
    property int editId: -1
    property string statusText: "Ready"

    // Header and data rows use the SAME widths to keep their columns aligned.
    // Reserve 16 pixels on the right for the vertical scrollbar.
    readonly property real tableWidth: Math.max(0, recordList.width - 16)
    readonly property int actionsWidth: 180

    function columnWidth(column) {
        if (column === 0) return 100  // Unique ID
        if (column === 1) return 110  // Latitude
        if (column === 2) return 110  // Longitude
        return Math.max(100, tableWidth - 320 - actionsWidth) // Comment expands.
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 12

        Label {
            text: "Data Table"
            font.pixelSize: 26
            font.bold: true
        }

        Label {
            Layout.fillWidth: true
            text: window.statusText
            color: "#555555"
            wrapMode: Text.WordWrap
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "white"
            border.color: "#cccccc"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 1
                spacing: 0

                // The header stays visible while the records scroll below it.
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 42
                    color: "#e8edf3"

                    Row {
                        Repeater {
                            model: ["Unique ID", "Latitude", "Longitude", "Comment"]
                            delegate: Rectangle {
                                required property int index
                                required property string modelData
                                width: window.columnWidth(index)
                                height: 42
                                color: "transparent"
                                border.color: "#cccccc"

                                Label {
                                    anchors.fill: parent
                                    anchors.margins: 10
                                    text: parent.modelData
                                    font.bold: true
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                        }

                        Rectangle {
                            width: window.actionsWidth
                            height: 42
                            color: "transparent"
                            border.color: "#cccccc"
                            Label {
                                anchors.centerIn: parent
                                text: "Actions"
                                font.bold: true
                            }
                        }
                    }
                }

                // Keep the existing QVariantList model. A ListView can display
                // table-shaped rows without changing your C++ controller.
                ListView {
                    id: recordList
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true
                    model: clientController.records
                    boundsBehavior: Flickable.StopAtBounds
                    ScrollBar.vertical: ScrollBar { }

                    delegate: Rectangle {
                        id: recordRow
                        required property int index
                        required property var modelData
                        width: window.tableWidth
                        height: 52
                        color: index % 2 === 0 ? "white" : "#f5f7fa"

                        Row {
                            // One cell for each field, in the same order as the header.
                            Repeater {
                                model: [
                                    String(recordRow.modelData.uniqueID),
                                    Number(recordRow.modelData.lat).toFixed(4),
                                    Number(recordRow.modelData.longitude).toFixed(4),
                                    String(recordRow.modelData.comment)
                                ]

                                delegate: Rectangle {
                                    required property int index
                                    required property string modelData
                                    width: window.columnWidth(index)
                                    height: recordRow.height
                                    color: "transparent"
                                    border.color: "#dddddd"

                                    Label {
                                        anchors.fill: parent
                                        anchors.margins: 10
                                        text: parent.modelData
                                        textFormat: Text.PlainText
                                        verticalAlignment: Text.AlignVCenter
                                        elide: Text.ElideRight
                                    }

                                    // Hover to read a comment that does not fit in its cell.
                                    HoverHandler { id: cellHover }
                                    ToolTip.visible: cellHover.hovered
                                    ToolTip.delay: 500
                                    ToolTip.text: modelData
                                }
                            }

                            Rectangle {
                                width: window.actionsWidth
                                height: recordRow.height
                                color: "transparent"
                                border.color: "#dddddd"

                                Row {
                                    anchors.centerIn: parent
                                    spacing: 8

                                    Button {
                                        text: "Update"
                                        width: 78
                                        onClicked: {
                                            window.editMode = true
                                            window.editId = recordRow.modelData.uniqueID
                                            recordForm.uniqueID = recordRow.modelData.uniqueID
                                            recordForm.lat = recordRow.modelData.lat
                                            recordForm.longitude = recordRow.modelData.longitude
                                            recordForm.comment = recordRow.modelData.comment
                                            window.formOpen = true
                                        }
                                    }

                                    Button {
                                        text: "Delete"
                                        width: 78
                                        onClicked: {
                                            window.statusText = "Delete request sent. Waiting for ACK..."
                                            clientController.deleteRecord(recordRow.modelData.uniqueID)
                                        }
                                    }
                                }
                            }
                        }
                    }

                    Label {
                        anchors.centerIn: parent
                        visible: recordList.count === 0
                        text: "No records yet. Click Add."
                        color: "#777777"
                    }
                }
            }
        }

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

    // Dim the table and prevent clicks on its buttons while the form is open.
    Rectangle {
        anchors.fill: parent
        visible: window.formOpen
        color: "#66000000"
        z: 10
        MouseArea { anchors.fill: parent }

        // Uses your existing RecordForm.qml without changing its interface.
        RecordForm {
            id: recordForm
            anchors.centerIn: parent
            editMode: window.editMode

            onApplyClicked: {
                if (editMode) {
                    window.statusText = "Update request sent. Waiting for ACK..."
                    clientController.updateRecord(uniqueID, lat, longitude, comment)
                } else {
                    window.statusText = "Add request sent. Waiting for ACK..."
                    clientController.addRecord(uniqueID, lat, longitude, comment)
                }
                window.formOpen = false
            }

            onCancelClicked: window.formOpen = false
        }
    }

    Connections {
        target: clientController

        // The C++ signal is recordsChanged (plural), not recordChanged.
        // The displayed model changes only when the controller accepts an ACK.
        function onRecordsChanged() {
            window.statusText = "Server ACK received. Table updated."
        }
    }
}
