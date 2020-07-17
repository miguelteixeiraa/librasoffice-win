#include "wineventlistener.h"

//Retrive event catched for all listener threads
QString retrieveEventCatched{};

WinEventListener::WinEventListener(){
    _refCount = 1;
}

void WinEventListener::addEventsToIdentify(const QList<QString> &list){
    for(auto event : list){
        if(mUIAutoEvents->contains(event)){
            eventsToIdentify.append(event);
        }
        else{
            std::cout << "The  event: " << event.toStdString() << " is not valid\n";
        }
    }
}

const QMap<QString, long>* WinEventListener::getAllUIAutoMonitorableEvents(){
    return  mUIAutoEvents;
}

ULONG STDMETHODCALLTYPE WinEventListener::AddRef(){
    ULONG ret = InterlockedIncrement(&_refCount);
    return ret;
}

ULONG STDMETHODCALLTYPE WinEventListener::Release(){
    ULONG ret = InterlockedDecrement(&_refCount);
    if (ret == 0){
        delete this;
        return 0;
    }
    return ret;
}

HRESULT STDMETHODCALLTYPE WinEventListener::QueryInterface(REFIID riid, void** ppInterface)    {
    if (riid == __uuidof(IUnknown))
        *ppInterface = static_cast<IUIAutomationEventHandler*>(this);
    else if (riid == __uuidof(IUIAutomationEventHandler))
        *ppInterface = static_cast<IUIAutomationEventHandler*>(this);
    else{
        *ppInterface = NULL;
        return E_NOINTERFACE;
    }
    this->AddRef();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WinEventListener::HandleAutomationEvent(IUIAutomationElement* pSender, EVENTID eventID){
 //   BSTR eventType;
    BSTR eventName;
 /*   BSTR applicationName;
    BSTR cachedAutomationId;
    BSTR cachedClassName;
    BSTR cachedFrameworkId;
    BSTR cachedHelpText;
    BSTR cachedItemStatus;
    BSTR cachedItemType;
    BSTR cachedLocalizedControlType;
    BSTR cachedProviderDescription;
    BSTR currentAcceleratorKey;
    BSTR currentAccessKey;
    BSTR currentAriaProperties;
    BSTR currentAriaRole;
    BSTR currentAutomationId;
    BSTR currentClassName;
    BSTR currentFrameworkId;*/
    //BSTR currentHelpText;


    auto bstrToQString = [](const BSTR &b){
        QString tmp = QString::fromUtf16(reinterpret_cast<ushort*>(b)).toUtf8();
        return tmp.simplified();
    };

    pSender->get_CurrentName(&eventName);
    //pSender->get_CachedAutomationId(&cachedAutomationId);
 //   pSender->get_CachedClassName(&cachedClassName);
   // pSender->get_CachedFrameworkId(&cachedFrameworkId);
   // pSender->get_CachedHelpText(&cachedHelpText);
   // pSender->get_CachedItemStatus(&cachedItemStatus);
   // pSender->get_CachedItemType(&cachedItemType);
   // pSender->get_CachedLocalizedControlType(&cachedLocalizedControlType);
   // pSender->get_CachedProviderDescription(&cachedProviderDescription);
    //pSender->get_CurrentAcceleratorKey(&currentAcceleratorKey);
    //pSender->get_CurrentAccessKey(&currentAccessKey);
    //pSender->get_CurrentAriaProperties(&currentAriaProperties);
    //pSender->get_CurrentAriaRole(&currentAriaRole);
    //pSender->get_CurrentAutomationId(&currentAutomationId);
    //pSender->get_CurrentClassName(&currentClassName);
    //pSender->get_CurrentFrameworkId(&currentFrameworkId);
    //pSender->get_CurrentHelpText(&currentHelpText);

   // qDebug() << "eventName: \n";
    //qDebug() << bstrToQString(eventName);
    //qDebug() << "cachedAutomationId: \n";
    //qDebug() << bstrToQString(cachedAutomationId);
   // qDebug() << "cachedClassName: \n";
    //qDebug() << bstrToQString(cachedClassName);
   // qDebug() << "cachedFrameworkId: \n";
    //qDebug() << bstrToQString(cachedFrameworkId);
    //qDebug() << "cachedHelpText: \n";
    //qDebug() <<  bstrToQString(cachedHelpText);
   // qDebug() << "cachedItemStatus: \n";
   // qDebug() << bstrToQString(cachedItemStatus);
    //qDebug() << "cachedItemType: \n";
    //qDebug() << bstrToQString(cachedItemType);
   // qDebug() << "cachedLocalizedControlType: \n";
    //qDebug() << bstrToQString(cachedLocalizedControlType);
    //qDebug() << "cachedProviderDescription: \n";
    //qDebug() << bstrToQString(cachedProviderDescription);
   // qDebug() << "currentAcceleratorKey: \n";
    //qDebug() << bstrToQString(currentAcceleratorKey);
    //qDebug() << "currentAccessKey: \n";
    //qDebug() << bstrToQString(currentAccessKey);
    //qDebug() << "currentAriaProperties: \n";
    //qDebug() << bstrToQString(currentAriaProperties);
    //qDebug() << "currentAriaRole: \n";
    //qDebug() << bstrToQString(currentAriaRole);
    //qDebug() << "currentAutomationId: \n";
   // qDebug() << bstrToQString(currentAutomationId);
   // qDebug() << "currentClassName:";
   // qDebug() << bstrToQString(currentClassName);
  //  qDebug() << "currentFrameworkId:";
//    qDebug() << bstrToQString(currentFrameworkId);
 //   qDebug() << "currentHelpText:";
   // qDebug() << bstrToQString(currentHelpText);


    retrieveEventCatched = bstrToQString(eventName);



    return S_OK;
}

void WinEventListener::listenerStart(){
    auto cleanup = [](auto &pAutomation_var, auto &hr_var, auto &pTargetElement_var, auto &ret_var, auto &pEHTemp_var) {
        // Remove event handlers, release resources, and terminate
        if (pAutomation_var != NULL){
            hr_var = pAutomation_var->RemoveAllEventHandlers();
            if (FAILED(hr_var))
                ret_var = 1;
            pAutomation_var->Release();
        }

        if (pEHTemp_var != NULL)
            pEHTemp_var->Release();

        if (pTargetElement_var != NULL)
            pTargetElement_var->Release();

        CoUninitialize();
        return ret_var;
    };

    HRESULT hr;
    int ret = 0;
    IUIAutomationElement* pTargetElement = NULL;
    WinEventListener* pEHTemp = NULL;

    CoInitializeEx(NULL, COINIT_MULTITHREADED);
    IUIAutomation* pAutomation = NULL;
    hr = CoCreateInstance(__uuidof(CUIAutomation), NULL, CLSCTX_INPROC_SERVER, __uuidof(IUIAutomation), (void**)&pAutomation);
    if (FAILED(hr) || pAutomation == NULL){
        ret = 1;
        cleanup(pAutomation, hr, pTargetElement, ret, pEHTemp);
    }

    // Use root element for listening to window and tooltip creation and destruction.
    hr = pAutomation->GetRootElement(&pTargetElement);
    if (FAILED(hr) || pTargetElement == NULL){
        ret = 1;
        cleanup(pAutomation, hr, pTargetElement, ret, pEHTemp);
    }

    pEHTemp = new WinEventListener();
    if (pEHTemp == NULL){
        ret = 1;
        cleanup(pAutomation, hr, pTargetElement, ret, pEHTemp);
    }

    qDebug() << "-Adding Event Handlers.\n";
    if(!eventsToIdentify.empty()){
        for(auto event : eventsToIdentify){
            hr = pAutomation->AddAutomationEventHandler(mUIAutoEvents->value(event), pTargetElement, TreeScope_Subtree, NULL, (IUIAutomationEventHandler*)pEHTemp);
            if(FAILED(hr)){
                ret = 1;
                cleanup(pAutomation, hr, pTargetElement, ret, pEHTemp);
            }
        }
    }
}
