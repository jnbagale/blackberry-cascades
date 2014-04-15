#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>
#include <bb/cascades/AbstractPane>

namespace bb
{
    namespace cascades
    {
        class Application;
        class LocaleHandler;
    }
}

class QTranslator;

/*!
 * @brief Application object
 *
 *
 */

class ApplicationUI : public QObject
{
    Q_OBJECT
public:
    ApplicationUI(bb::cascades::Application *app);
    virtual ~ApplicationUI() { }

    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged);
    Q_INVOKABLE   void callme();


    public  Q_SLOTS:
    QString status();
    void setStatus(QString str);

    Q_SIGNALS:
    // The change notification signal for the property
    void statusChanged();

private slots:
    void onSystemLanguageChanged();
private:
    QString m_status;
    QTranslator* m_pTranslator;
    bb::cascades::LocaleHandler* m_pLocaleHandler;
    bb::cascades::AbstractPane* root;
    // root AbstractPane can then be used to access QML objects from CPP
};

#endif /* ApplicationUI_HPP_ */
