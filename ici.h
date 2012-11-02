#ifndef _ICI_H
#define _ICI_H

#include <QObject>
#include <QVariantMap>

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

    ICISettings(const QString & file, QObject* parent = 0);
    virtual ~ICISettings();

    bool hasError() const;
    QString errorString() const;

    void setContext(const QVariantMap & ctx);
    void setValue(const QString & key, const QVariant & defaultValue);

    QVariant value(const QString & key, const QVariant & defaultValue = QVariant()) const;
    QVariantMap values() const;

    bool contains(const QString & key) const;

    bool createFunction(const QString & name, IciFunction);

private:
    ICISettingsPrivate* d;
};

#endif // _ICI_H
