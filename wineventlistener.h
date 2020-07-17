#ifndef WINEVENTLISTENER_H
#define WINEVENTLISTENER_H

#include <windows.h>
#include <UIAutomation.h>

#include <QDebug>
#include <QMap>
#include <QList>
#include <iostream>
#include <QString>

#include "MonitorableUIAutoEvents.h"

//Retrieve event catched for all listener threads
extern QString retrieveEventCatched;


class WinEventListener : public IUIAutomationEventHandler
{
    const QMap<QString, long>* mUIAutoEvents = &uiAutoMonitorableEvents;
    QList<QString> eventsToIdentify;

public:
    explicit WinEventListener();

    void addEventsToIdentify(const QList<QString> &list);

    const QMap<QString, long>* getAllUIAutoMonitorableEvents();
    
    void listenerStart();

    // Start UIAutomation stuff to event listener to work
    ULONG STDMETHODCALLTYPE Release();
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppInterface);
    HRESULT STDMETHODCALLTYPE HandleAutomationEvent(IUIAutomationElement* pSender, EVENTID eventID);
    ULONG STDMETHODCALLTYPE AddRef();
    // End UIAutomation stuff to event listener to work

private:
    LONG _refCount;
    
};

#endif // WINEVENTLISTENER_H
