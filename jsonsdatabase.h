#ifndef JSONSDATABASE_H
#define JSONSDATABASE_H
#include <windows.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDirIterator>


class JsonSDatabase : public QObject
{
    Q_OBJECT
    QJsonObject librasDatabase;
    QString databaseAddress = getCurrentPath() + "\\gifs";

public:
    JsonSDatabase();
    void getContentFromFolder();
    QJsonObject getDatabase();
    void persistDB();
    void updateDatabase();
    bool contains(const QString &s);

private:
    QString getCurrentPath();
};

#endif // JSONSDATABASE_H
