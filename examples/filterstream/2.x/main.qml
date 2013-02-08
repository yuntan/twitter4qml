import QtQuick 2.0
import Twitter4QML 1.1

Rectangle {
    width: 400
    height: 600

    FilterStreamModel {
        id: filterStream
        track: '#2ch'
        sortKey: 'id_str'
    }

    ListView {
        id: view
        anchors.fill: parent
        anchors.bottomMargin: 20
        model: filterStream
        delegate: Item {
            id: delegate
            width: ListView.view.width
            height: 100
            property real height2: height

            Image {
                x: 10
                y: delegate.height - 100 + 10
                width: height
                height: 64
                source: model.user.profile_image_url
                smooth: true
            }

            Text {
                x: 64 + 20
                y: delegate.height - 100 + 10
                text: model.user.screen_name
            }
            Text {
                x: 64 + 20
                y: delegate.height - 100 + 30
                width: parent.width - x - 10
                height: 100 - y - 10
                text: model.plain_text
                wrapMode: Text.WordWrap
                clip: true
                font.family: 'Migu1P'
            }

            ListView.onAdd: SequentialAnimation {
//                ScriptAction { script: if (view.atYBeginning) view.contentY += 1 }
//                PropertyAction { target: delegate; property: "clip"; value: true }
                PropertyAction { target: delegate; property: "height2"; value: height }
                PropertyAction { target: delegate; property: "height"; value: 0 }
                PropertyAction { target: delegate; property: "opacity"; value: 0 }
                ParallelAnimation {
                    NumberAnimation { target: delegate; property: "height"; to: delegate.height2; duration: 250; easing.type: Easing.InOutQuad }
                    NumberAnimation { target: delegate; property: "opacity"; to: 1.0; duration: 500 }
                }
//                PropertyAction { target: delegate; property: "clip"; value: false }
            }
        }
    }

    Rectangle {
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 2
        }
        height: 20
        border.color: 'black'
        border.width: 2

        TextInput {
            id: track
            anchors {
                left: parent.left
                right: parent.right
                verticalCenter: parent.verticalCenter
                margins: 2
            }
            text: filterStream.track
            Keys.onReturnPressed: {
                filterStream.track = track.text
            }
        }
    }
}
