#include "listenercontroller.h"

//WorkerListener stuff, outset
WorkerListener::WorkerListener()
{
}

void WorkerListener::startWork(){
    listener->listenerStart();
}
//end WorkerListener stuff


ListenerController::ListenerController(){
    listenersCount = 0;
}

void ListenerController::addListener(const QList<QString> &eventsToIdentify){
    QThread *t = new QThread;

    //creating an event listener by WorkerListener, and adding eventsToIdentify to it
    WorkerListener *w = new WorkerListener;
    w->listener->addEventsToIdentify(eventsToIdentify);
    w->moveToThread(t);
    connect(t, SIGNAL (started()), w, SLOT (startWork()));
    threadList.append(t);
    listeners.append(w);
    listenersCount += 1;
}


void ListenerController::start(){
    for(auto listenerThread : threadList){
        listenerThread->start();
    }
}
