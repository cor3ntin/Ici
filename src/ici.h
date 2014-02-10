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

#ifndef _ICI_H
#define _ICI_H

#include <QObject>
#include <QVariantMap>
#include <QStringList>

class ICISettingsPrivate;
class ICISettingsContextPrivate;
class ICISettingsContext{
public:
    ~ICISettingsContext();
    void setErrorMessage(const QString & message);
    QVariant value(const QString & key, const QVariant & defaultValue = QVariant()) const;
    bool exists(const QString & key) const;
    void setValue(const QString & key, const QVariant & defaultValue);
    const QVariantList & args() const;
    const QStringList & keys() const;
    bool hasFunction(const QString & name) const;
    QString file() const;
    int line() const;
private:
    friend class ICISettingsPrivate;
    ICISettingsContext();
    ICISettingsContextPrivate* d;
};

class ICISettings : public QObject
{
    Q_OBJECT
public:
    typedef QVariant (*IciFunction)(ICISettingsContext* ctx);

    explicit ICISettings(const QString & file, QObject* parent = 0);
    explicit ICISettings(const QByteArray & data, QObject* parent = 0);
    virtual ~ICISettings();

    bool hasError() const;
    QString errorString() const;

    bool evaluate();

    void setContext(const QVariantMap & ctx);
    void setValue(const QString & key, const QVariant & defaultValue);

    QVariant value(const QString & key, const QVariant & defaultValue = QVariant()) const;
    QMap<QString, QVariant > values() const;

    QStringList keys() const;

    bool contains(const QString & key) const;

    bool createFunction(const QString & name, IciFunction);

    bool reload();

    QStringList files() const;

private:
    ICISettingsPrivate* d;
};

#endif // _ICI_H
