#ifndef LISTENERCONTROLLER_H
#define LISTENERCONTROLLER_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QString>
#include <QThread>

#include <wineventlistener.h>


class WorkerListener : public QObject
{
    Q_OBJECT

public:
    WinEventListener* listener = new WinEventListener;
    WorkerListener();

public slots:
    Q_INVOKABLE void startWork();

};


class ListenerController : public QObject
{
    Q_OBJECT
    unsigned listenersCount;
    QList<QThread*> threadList;

public:
    QList<WorkerListener*> listeners;
    ListenerController();
    void addListener(const QList<QString> &eventsToIdentify);

public slots:
    void start();
};

#endif // LISTENERCONTROLLER_H
