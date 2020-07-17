import QtQuick 2.1
import QtQuick.Window 2.15


Window {
    id: librasoffice
    width: 200
    height: 250
    visible: false
    flags: Qt.Popup
    y: Screen.desktopAvailableHeight - height
    x: Screen.desktopAvailableWidth - width

    property string f_eventCatched: ""

    AnimatedImage {
        id: signGif
        anchors.fill: parent
    }

    Timer {
        id: timer
        interval: 200; repeat: true
        running: true
        triggeredOnStart: true
        onTriggered: {
            if(f_eventCatched !== laso_backend.getEventCatched()){
                f_eventCatched = laso_backend.getEventCatched()
                if(laso_backend.database_contains(f_eventCatched)){
                    signGif.source = "..\\gifs\\" + f_eventCatched + ".gif";
                    librasoffice.visible = true;
                    console.log(f_eventCatched);
                }
                else{
                    librasoffice.visible = false;
                    console.log(f_eventCatched);
                }
            }
        }
    }
}
