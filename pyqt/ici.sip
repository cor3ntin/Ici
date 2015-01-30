%Module ici

%Import QtCore/QtCoremod.sip

class ICISettingsContext  /NoDefaultCtors / {

%TypeHeaderCode
#include "ici.h"
%End

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
    ICISettingsContext();
};

class ICISettings : public QObject {


%TypeHeaderCode
#include "ici.h"
%End

public:

    explicit ICISettings(const QString & file, QObject* parent = 0);
    virtual ~ICISettings();

    bool hasError() const;
    QString errorString() const;

    bool evaluate(bool clear = false, bool ignore_errors = false);

    void setContext(const QVariantMap & ctx);
    void setValue(const QString & key, const QVariant & defaultValue);

    QVariant value(const QString & key, const QVariant & defaultValue = QVariant()) const;
    QMap<QString, QVariant > values() const;

    QStringList keys() const;

    bool contains(const QString & key) const;

    bool createFunction(const QString & name, SIP_PYCALLABLE);
%MethodCode
        bool ret = false;
        /*PyCodeObject* objCode = reinterpret_cast<PyCodeObject*>(a1);
        int numArgs = objCode->co_flags & CO_VARARGS ? -1 : objCode->co_argcount;
        if( numArgs != 1 ) {
            PyErr_SetString(PyExc_TypeError, "Ici callbacks require a 'context' argument");
        }
        else*/
        {
            ret = sipCpp->createFunction(QString(*a0), python_ici_callback, a1);
        }
        sipRes = sipBuildResult(NULL, "b", &ret);
%End

    bool reload();

    QStringList files() const;
};



%ModuleHeaderCode
#include "../src/ici.h"
QVariant python_ici_callback(ICISettingsContext* ctx);
%End

%ModuleCode

QVariant python_ici_callback(ICISettingsContext* ctx) {
    PyObject* pyobject = static_cast<PyObject*>(ctx->fdata());
    if(pyobject == 0 ) {
        return false;
    }

    PyObject *res =
        sipCallMethod(0, pyobject, "D", ctx, sipType_ICISettingsContext, NULL);

    if(!res || !sipCanConvertToType(res, sipType_QVariant, 0)) {
        PyErr_SetString(PyExc_TypeError, "invalid result type from python callback");
        Py_XDECREF(res);
        return QVariant();
    }
    int err = 0;
    int state = 0;
    void* v = sipConvertToType(res, sipType_QVariant, NULL, 0, &state, &err);
    if(!v) {
        PyErr_SetString(PyExc_TypeError, "Can not convert to QVariant");
        return QVariant();
    }
    QVariant variant(*(QVariant*)v);
    sipReleaseType(v,sipType_QVariant, state);

    Py_XDECREF(res);
    return variant;
}
%End
