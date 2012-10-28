#include <QCoreApplication>
#include "iciparser.h"
#include <QString>
#include <QFile>

int main(int argc, char *argv[])
{
    QFile f(argv[1]);
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    ICIParser parser(data);
    if(!parser.parse()){
        qDebug("Parsing failed");
    }
    qDebug() << "-------------";
    QVariantMap values = parser.values();
    for(QVariantMap::const_iterator it = values.begin(); it !=values.end(); ++it){
        qDebug() << it.key() << it.value();
    }
}
