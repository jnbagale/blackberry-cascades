#include "applicationui.hpp"

#include <iostream>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>

using namespace bb::cascades;
using namespace std;

ApplicationUI::ApplicationUI(bb::cascades::Application *app) :
        QObject(app)
{
    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);
    if(!QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()))) {
        // This is an abnormal situation! Something went wrong!
        // Add own code to recover here
        qWarning() << "Recovering from a failed connect()";
    }
    // initial load
    onSystemLanguageChanged();
    // Initialise value
    m_value = 0;

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    qml->setContextProperty("cppObject", this);

    // Create root object for the UI
    root = qml->createRootObject<AbstractPane>();

    //set a value of a label in QML from CPP
    root->setProperty("label0Text", "Hello World... From CPP");

    // Updates another label on QML
    HelloQML();


    // Set created root object as the application scene
    app->setScene(root);
}

void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("cppandqml_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}

void ApplicationUI::HelloQML()
{
	qDebug() << "Accessing QML Label... from CPP" << endl;
	QObject *newLabel = this->root->findChild<QObject*>("label1");

	if (newLabel)
	    newLabel->setProperty("text", "Hello QML... Yours CPP");
}

void ApplicationUI::HelloCPP(QString message)
{
	qDebug() << message;
}

int ApplicationUI::value()
{
    return m_value;
}

//! [6]
void ApplicationUI::setValue(int value)
{

    m_value = value;
    emit valueChanged(m_value);

}
void ApplicationUI::resetValue()
{

    m_value = 0;
    emit valueChanged(m_value);

}
