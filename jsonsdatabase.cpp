#include "jsonsdatabase.h"

JsonSDatabase::JsonSDatabase()
{
    getContentFromFolder();
    persistDB();
}

QString JsonSDatabase::getCurrentPath(){
    std::string path;
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    path = std::string(buffer);
    path = path.substr(0, path.find_last_of( "\\/" ));
    return QString::fromLocal8Bit(path.c_str());
}

void JsonSDatabase::getContentFromFolder(){
    QString sign;
    QDirIterator it(databaseAddress);
    while (it.hasNext()) {
        sign = it.next();
        sign = sign.right(sign.size() - sign.lastIndexOf("/") - 1);
        if(sign.contains(".gif")){
            librasDatabase.insert(sign, QJsonValue::fromVariant(true));
        }
    }
}

void JsonSDatabase::persistDB(){
    QJsonDocument doc(librasDatabase);
    QString filename = databaseAddress + "\\laso_database.json";

    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << " Could not open file for writing";
        return;
    }

    QString formattedJsonString = doc.toJson(QJsonDocument::Indented);

    QTextStream out(&file);
    for(auto line : formattedJsonString){
        out << line;
    }
    file.flush();
    file.close();
}

bool JsonSDatabase::contains(const QString &s){
    return librasDatabase.contains(s);
}

void JsonSDatabase::updateDatabase(){
    getContentFromFolder();
    persistDB();
}

QJsonObject JsonSDatabase::getDatabase(){
    return librasDatabase;
}
