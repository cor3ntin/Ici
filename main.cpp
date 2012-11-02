/****************************************************************************
**
** Copyright (C) 2012 Corentin Jabot
** Contact: https://github.com/cor3ntin/Ici
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
****************************************************************************/

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
