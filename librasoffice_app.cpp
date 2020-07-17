#include "librasoffice_app.h"


LIBRASOffice_App::LIBRASOffice_App(int argc, char *argv[]) : QGuiApplication(argc, argv){
    QThread *t_eventListener = new QThread;

    //add events to WinEventListener and move to listener thread
    eventListener->addListener(eventsToIdentify);
    eventListener->moveToThread(t_eventListener);
    connect(t_eventListener, SIGNAL(started()), eventListener, SLOT(start()));

    //start ui (systemTray and signs exibition)
    initUI();

    //start WinEventListener
    t_eventListener->start();
}

void LIBRASOffice_App::initUI(){
    //Create a qml component for System tray and load popup to signs exibition
    engine->rootContext()->setContextProperty("laso_backend", this);

    QQmlComponent librasoffice_systray(engine, url_systray);
    librasoffice_systray.create();

    engine->load(url_popup);
}

QString LIBRASOffice_App::getEventCatched(){
    return *eventCatched;
}

bool LIBRASOffice_App::database_contains(const QString &eventName){
    return laso_database->contains(eventName + ".gif");
}

void LIBRASOffice_App::handleSignalExibition(const bool &controlValue){
    if (controlValue == false){
        showingSigns = false;
        qDebug() << "Signs exibition stopped";
    }
    else{
        showingSigns = true;
        qDebug() << "Signs exibiton started";
    }
}

void LIBRASOffice_App::run(){
    this->exec();
}
