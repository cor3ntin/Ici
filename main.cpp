#include <QCoreApplication>
#include "ici.h"
#include <QString>
#include <QFile>
#include <QDebug>

int main(int, char *argv[])
{
    ICISettings settings(argv[1]);
    if(settings.hasError()){
       qDebug() << settings.errorString();
    }
    qDebug() << settings.values();
    return 0;
}
