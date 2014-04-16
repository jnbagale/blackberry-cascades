import bb.cascades 1.2

Page {
    property alias label0Text:label0.text
    Container {
        //Todo: fill me with QML
        Label {
            id:label0
            // Localized text with the dynamic translation and locale updates support
            //text: qsTr("Hello World") + Retranslate.onLocaleOrLanguageChanged
            textStyle.base: SystemDefaults.TextStyles.BigText
        
        }
        
        Label {
            objectName:"label1" // to be used for access from CPP
            //text:" Message from CPP will appear here"
        }
        
        Button {
            id: button
            text: "Call CPP from QML"
            
            onClicked: {
                cppObject.HelloCPP(qsTr("Hello CPP... Yours QML"));
                // Calling CPP function through the app context property which is
                // set in the applicationUI constructor 
            }
        }
        
        Label {
            text:"---------------------------------------------------------------"
        }
        Button {
            id: increaseButton
            text: "Increase the value"
            onClicked: {
                cppObject.value = cppObject.value + 1;
            }
        }
        Button {
            id: resetButton
            text: "Reset the value"
            onClicked: {
                cppObject.resetValue ();
            }
        }
        Label {
            id: valueLabel
            text: "The value is " + cppObject.value
        }
        Label {
            text:"---------------------------------------------------------------"
        }
        
        Slider{
            id:slider0
            objectName: "slider0"
            fromValue: 0.0
            toValue: 100.0

            onCreationCompleted: {
                // Define a slot to connect to onValueChanged() signal from CPP
                cppObject.valueChanged.connect(slider0.onCppValueChanged);

            }
            function onCppValueChanged (val) {
                slider0.value  = val;
            }
            
        }
    }
}
