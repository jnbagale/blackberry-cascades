import bb.cascades 1.2

Page {
    Container {
        //Todo: fill me with QML
        Label {
            // Localized text with the dynamic translation and locale updates support
            text: qsTr("Hello World") + Retranslate.onLocaleOrLanguageChanged
            textStyle.base: SystemDefaults.TextStyles.BigText
        
        }
        
        Label {
            id:testLabel
            text:app.status 
            // Sets the text to be return value of the status function
            // Automatically updated on statusChanged signal
        }
        
        Button {
            id: button
            objectName: "button"
            text: "Click me"
            
            onClicked: {
                app.callme();
                // Calling CPP function through the app context property set
                // callme() function changes the status and triggers the statusChanged signal
                // Thus the test Label will be updated
            }
        }
    }
}
