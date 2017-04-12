import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Araignee")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    MainForm {
        anchors.fill: parent
        id:page
        zone0 {
            onClicked:vueObjetSrvr.jouerUnCoup(0)
        }
        zone1 {
            onClicked:vueObjetSrvr.jouerUnCoup(1)
        }
        zone2 {
            onClicked:vueObjetSrvr.jouerUnCoup(2)
        }
        zone3 {
            onClicked:vueObjetSrvr.jouerUnCoup(3)
        }
        zone4 {
            onClicked:vueObjetSrvr.jouerUnCoup(4)
        }
        zone5 {
            onClicked:vueObjetSrvr.jouerUnCoup(5)
        }
        zone6 {
            onClicked:vueObjetSrvr.jouerUnCoup(6)
        }
        zone7 {
            onClicked:vueObjetSrvr.jouerUnCoup(7)
        }
        zone8 {
            onClicked:vueObjetSrvr.jouerUnCoup(8)
        }
    }


    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
}

