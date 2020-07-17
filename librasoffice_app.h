#ifndef LIBRASOFFICE_APP_H
#define LIBRASOFFICE_APP_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QUrl>
#include <QStringLiteral>
#include <QList>
#include <QString>
#include <QThread>

#include <listenercontroller.h>
#include "jsonsdatabase.h"


class LIBRASOffice_App : QGuiApplication
{
    Q_OBJECT
    bool showingSigns = true;
    QList<QString> eventsToIdentify = {
        "UIA_ToolTipOpenedEventId",
        "UIA_ToolTipClosedEventId",
        "UIA_MenuOpenedEventId",
        "UIA_MenuClosedEventId",
        "UIA_Window_WindowOpenedEventId",
        "UIA_MenuModeStartEventId",
        "UIA_MenuModeEndEventId",
    };

    JsonSDatabase *laso_database = new JsonSDatabase;

    QQmlApplicationEngine *engine = new QQmlApplicationEngine;

    const QUrl url_systray = QStringLiteral("qrc:/qml/main.qml");
    const QUrl url_popup = QStringLiteral("qrc:/qml/popupSign.qml");

    ListenerController *eventListener = new ListenerController;

    QString *eventCatched = &retrieveEventCatched;

public:
    explicit LIBRASOffice_App(int argc, char *argv[]);
    Q_INVOKABLE void handleSignalExibition(const bool &value);
    Q_INVOKABLE QString getEventCatched();
    Q_INVOKABLE bool database_contains(const QString &eventName);
    void initUI();
    void run();
};

#endif // LIBRASOFFICE_APP_H
