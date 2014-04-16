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

    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged);
    Q_INVOKABLE   void HelloCPP(QString message);
    Q_INVOKABLE   void resetValue();
    void HelloQML();

    public  Q_SLOTS:
    int value();
    void setValue(int value);

    Q_SIGNALS:
    // The change notification signal for the property
    void valueChanged(int);

private slots:
    void onSystemLanguageChanged();
private:
    int m_value;
    QTranslator* m_pTranslator;
    bb::cascades::LocaleHandler* m_pLocaleHandler;
    bb::cascades::AbstractPane* root;
    // root AbstractPane can then be used to access QML objects from CPP
};

#endif /* ApplicationUI_HPP_ */
