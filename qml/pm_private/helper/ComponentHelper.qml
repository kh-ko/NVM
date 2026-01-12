pragma Singleton
import QtQuick 2.15

Item {
    id: root

    property var integerInput : null
    property var comboBox     : null

    Component.onCompleted: {
        integerInput = Qt.createComponent("qrc:/pm_private/control/PmIntegerInput.qml");
        comboBox     = Qt.createComponent("qrc:/pm_private/control/PmComboBox.qml"    );

        // [추천] 컴포넌트 로딩 에러 체크
        if (integerInput.status === Component.Error) {
            console.error("Error loading IntegerInput:", integerInput.errorString());
        }
        if (comboBox.status === Component.Error) {
            console.error("Error loading ComboBox:", comboBox.errorString());
        }
    }

    function createCustomControl( parent, itemModel)
    {
        var qmlUrl = "";

        if( itemModel.UiType === "IntegerInput" )
        {
            console.debug("Create integerInput");
            integerInput.createObject(parent, {itemModel : itemModel});
        }
        else if( itemModel.UiType === "ComboBox" )
        {
            console.debug("Create ComboBox");
            comboBox.createObject(parent, {itemModel : itemModel});
        }
        else
        {
            console.debug("Unknow Ui type = " + itemModel.UiType);
            return;
        }
    }
}
