import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import ValveIdentificationExDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    readonly property int emptyHeight : 24
    property var body : null
    property var unlock : false

    titleText   : qsTr("Valve identification")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    errMsg2     : dlgModel.mErrMsg2
    access      : ValveEnumDef.ACCESS_LOCAL // dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : dlgModel.mIsEdit

    function openPasswordDlg()
    {
        var popup = passwordDlg.createObject(dialog); // khko_test
        popup.open();
    }

    function commit()
    {
        var valveModel       = body.valveModelCombo.currentIndex
        var valveType        = body.valveTypeCombo.currentIndex
        var sealingType      = body.sealingTypeCombo.currentIndex
        var flangeSize       = body.flangeSizeCombo.currentIndex
        var methodOfContract = body.methodOfContractCombo.currentIndex
        var bodyMaterial     = body.bodyMaterialCombo.currentIndex
        var commInterface    = body.commInterfaceCombo.currentIndex
        var powerOption      = body.powerOptionCombo.currentIndex
        var quantifyOfSensor = body.quantifyOfSensorCombo.currentIndex
        var version01        = body.version01Combo.currentIndex
        var version02        = body.version02Combo.currentIndex
        var version03        = body.version03Combo.currentIndex
        var productNumber    = parseInt(body.productNumberInput.textField.text, 16)

        var productNumberEx  = 0;
        if(dlgModel.mIsSupportPdNumEx)
        {
            productNumberEx  = parseInt(body.productNumberExInput.textField.text, 16)
        }

        body.serialNumberInput.textField.text = dialog.buildSerialNumberByGUI();
        body.serialNumberInput.isInvalidValue = false


        dlgModel.onCommandApply(valveModel, valveType, sealingType, flangeSize, methodOfContract, bodyMaterial, commInterface, powerOption, quantifyOfSensor, version01, version02, version03, productNumber, productNumberEx)
    }

    function containModelValue(value, model, startIdx, len)
    {
        for(var mi = 0; mi  < model.length; mi++)
        {
            if(model[mi].toUpperCase() === "UNKNOWN")
                continue;

            if(value === model[mi].substr(startIdx,len))
                return mi;
        }
        return -1;
    }

    function getModelValue(index, model, startIdx, len)
    {
        return model[index].substr(startIdx,len)
    }

    function buildSerialNumberByGUI()
    {
        var retSerialNumber = "";

        retSerialNumber = retSerialNumber + getModelValue(body.valveModelCombo.currentIndex       , body.valveModelCombo.model      , 0, 1) + "-"
        retSerialNumber = retSerialNumber + getModelValue(body.valveTypeCombo.currentIndex        , body.valveTypeCombo.model       , 0, 1) + "-"
        retSerialNumber = retSerialNumber + getModelValue(body.sealingTypeCombo.currentIndex      , body.sealingTypeCombo.model     , 0, 1) + "-"
        retSerialNumber = retSerialNumber + getModelValue(body.flangeSizeCombo.currentIndex       , body.flangeSizeCombo.model      , 0, 3) + "-"
        retSerialNumber = retSerialNumber + getModelValue(body.methodOfContractCombo.currentIndex , body.methodOfContractCombo.model, 0, 1) + "-"
        retSerialNumber = retSerialNumber + getModelValue(body.bodyMaterialCombo.currentIndex     , body.bodyMaterialCombo.model    , 0, 1) + "-"
        retSerialNumber = retSerialNumber + getModelValue(body.commInterfaceCombo.currentIndex    , body.commInterfaceCombo.model   , 0, 2) + "-"
        retSerialNumber = retSerialNumber + getModelValue(body.powerOptionCombo.currentIndex      , body.powerOptionCombo.model     , 0, 1) + "-"
        retSerialNumber = retSerialNumber + getModelValue(body.quantifyOfSensorCombo.currentIndex , body.quantifyOfSensorCombo.model, 0, 1) + "-R"
        retSerialNumber = retSerialNumber + getModelValue(body.version01Combo.currentIndex        , body.version01Combo.model       , 0, 1)
        retSerialNumber = retSerialNumber + getModelValue(body.version02Combo.currentIndex        , body.version02Combo.model       , 0, 1)
        retSerialNumber = retSerialNumber + getModelValue(body.version03Combo.currentIndex        , body.version03Combo.model       , 0, 1) + "-"
        if(dlgModel.mIsSupportPdNumEx)
        {
            retSerialNumber = retSerialNumber + body.productNumberInput.textField.text + "-"
            retSerialNumber = retSerialNumber + body.productNumberExInput.textField.text
        }
        else
        {
            retSerialNumber = retSerialNumber + body.productNumberInput.textField.text
        }

        console.debug("[buildSerialNumberByGUI]mIsSupportPdNumEx" + retSerialNumber)

        return retSerialNumber;
    }

    function setValveIDBySerialNumber(inputValue)
    {
        if(inputValue.length < 20)
        {
            return false;
        }

        if(inputValue.substr(12, 1) !== "R")
        {
            return false;
        }

        //0 1 2 345 6 7 89 0 1 2 3 4 5 6789
        //A B N 080 F S DN D 2 R 0 0 F 000E

        var valveModelValue       = inputValue.substr( 0, 1)
        var valveTypeValue        = inputValue.substr( 1, 1)
        var sealingTypeValue      = inputValue.substr( 2, 1)
        var flangeSizeValue       = inputValue.substr( 3, 3)
        var methodOfContractValue = inputValue.substr( 6, 1)
        var bodyMaterialValue     = inputValue.substr( 7, 1)
        var commInterfaceValue    = inputValue.substr( 8, 2)
        var powerOptionValue      = inputValue.substr(10, 1)
        var quantifyOfSensorValue = inputValue.substr(11, 1)
        var version01Value        = inputValue.substr(13, 1)
        var version02Value        = inputValue.substr(14, 1)
        var version03Value        = inputValue.substr(15, 1)
        var productNumberValue    = inputValue.substr(16, 4)
        var productNumberExValue  = "0000";

        if(inputValue.length > 23)
        {
            productNumberExValue    = inputValue.substr(20, 6)
        }

        var valveModelIdx         = containModelValue(valveModelValue      , body.valveModelCombo.model      , 0, 1)
        var valveTypeIdx          = containModelValue(valveTypeValue       , body.valveTypeCombo.model       , 0, 1)
        var sealingTypeIdx        = containModelValue(sealingTypeValue     , body.sealingTypeCombo.model     , 0, 1)
        var flangeSizeIdx         = containModelValue(flangeSizeValue      , body.flangeSizeCombo.model      , 0, 3)
        var methodOfContractIdx   = containModelValue(methodOfContractValue, body.methodOfContractCombo.model, 0, 1)
        var bodyMaterialIdx       = containModelValue(bodyMaterialValue    , body.bodyMaterialCombo.model    , 0, 1)
        var commInterfaceIdx      = containModelValue(commInterfaceValue   , body.commInterfaceCombo.model   , 0, 2)
        var powerOptionIdx        = containModelValue(powerOptionValue     , body.powerOptionCombo.model     , 0, 1)
        var quantifyOfSensorIdx   = containModelValue(quantifyOfSensorValue, body.quantifyOfSensorCombo.model, 0, 1)
        var version01Idx          = containModelValue(version01Value       , body.version01Combo.model       , 0, 1)
        var version02Idx          = containModelValue(version02Value       , body.version02Combo.model       , 0, 1)
        var version03Idx          = containModelValue(version03Value       , body.version03Combo.model       , 0, 1)

        if(valveModelIdx       === -1) return false;
        if(valveTypeIdx        === -1) return false;
        if(sealingTypeIdx      === -1) return false;
        if(flangeSizeIdx       === -1) return false;
        if(methodOfContractIdx === -1) return false;
        if(bodyMaterialIdx     === -1) return false;
        if(commInterfaceIdx    === -1) return false;
        if(powerOptionIdx      === -1) return false;
        if(quantifyOfSensorIdx === -1) return false;
        if(version01Idx        === -1) return false;
        if(version02Idx        === -1) return false;
        if(version03Idx        === -1) return false;

        if((!(productNumberValue.charAt(0) >= '0' && productNumberValue.charAt(0) <= '9') && !(productNumberValue.charAt(0) >= 'A' && productNumberValue.charAt(0) <= 'F'))
         ||(!(productNumberValue.charAt(1) >= '0' && productNumberValue.charAt(1) <= '9') && !(productNumberValue.charAt(1) >= 'A' && productNumberValue.charAt(1) <= 'F'))
         ||(!(productNumberValue.charAt(2) >= '0' && productNumberValue.charAt(2) <= '9') && !(productNumberValue.charAt(2) >= 'A' && productNumberValue.charAt(2) <= 'F'))
         ||(!(productNumberValue.charAt(3) >= '0' && productNumberValue.charAt(3) <= '9') && !(productNumberValue.charAt(3) >= 'A' && productNumberValue.charAt(3) <= 'F')))
            return false;

        if((!(productNumberExValue.charAt(0) >= '0' && productNumberExValue.charAt(0) <= '9') && !(productNumberExValue.charAt(0) >= 'A' && productNumberExValue.charAt(0) <= 'F'))
         ||(!(productNumberExValue.charAt(1) >= '0' && productNumberExValue.charAt(1) <= '9') && !(productNumberExValue.charAt(1) >= 'A' && productNumberExValue.charAt(1) <= 'F'))
         ||(!(productNumberExValue.charAt(2) >= '0' && productNumberExValue.charAt(2) <= '9') && !(productNumberExValue.charAt(2) >= 'A' && productNumberExValue.charAt(2) <= 'F'))
         ||(!(productNumberExValue.charAt(3) >= '0' && productNumberExValue.charAt(3) <= '9') && !(productNumberExValue.charAt(3) >= 'A' && productNumberExValue.charAt(3) <= 'F')))
            return false;

        body.valveModelCombo.currentIndex       = valveModelIdx
        body.valveTypeCombo.currentIndex        = valveTypeIdx
        body.sealingTypeCombo.currentIndex      = sealingTypeIdx
        body.flangeSizeCombo.currentIndex       = flangeSizeIdx
        body.methodOfContractCombo.currentIndex = methodOfContractIdx
        body.bodyMaterialCombo.currentIndex     = bodyMaterialIdx
        body.commInterfaceCombo.currentIndex    = commInterfaceIdx
        body.powerOptionCombo.currentIndex      = powerOptionIdx
        body.quantifyOfSensorCombo.currentIndex = quantifyOfSensorIdx
        body.version01Combo.currentIndex        = version01Idx
        body.version02Combo.currentIndex        = version02Idx
        body.version03Combo.currentIndex        = version03Idx

        if(body.productNumberInput.textField.text  !== productNumberValue)
             dlgModel.onCommandSetEdit(true)

        body.productNumberInput.textField.text  = productNumberValue

        if(dlgModel.mIsSupportPdNumEx)
        {
            if(body.productNumberExInput.textField.text  !== productNumberExValue)
                 dlgModel.onCommandSetEdit(true)

            body.productNumberExInput.textField.text  = productNumberExValue
        }

        return true;
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = GUISetting.popup_nor_width
    }

    ValveIdentificationExDlgModel{
        id : dlgModel

        onSignalEventCompletedLoad: {
            console.debug("[onSignalEventCompletedLoad]mSerialNumber = " + dlgModel.mSerialNumber)

            body.serialNumberInput.textField.text   = dlgModel.mSerialNumber
            body.valveModelCombo.currentIndex       = dlgModel.mValveModel
            body.valveTypeCombo.currentIndex        = dlgModel.mValveType
            body.sealingTypeCombo.currentIndex      = dlgModel.mSealingType
            body.flangeSizeCombo.currentIndex       = dlgModel.mFlangeSize
            body.methodOfContractCombo.currentIndex = dlgModel.mMethodOfContract
            body.bodyMaterialCombo.currentIndex     = dlgModel.mBodyMaterial
            body.commInterfaceCombo.currentIndex    = dlgModel.mCommInterface
            body.powerOptionCombo.currentIndex      = dlgModel.mPowerOption
            body.quantifyOfSensorCombo.currentIndex = dlgModel.mQuantityOfSensors
            body.version01Combo.currentIndex        = dlgModel.mVersion01
            body.version02Combo.currentIndex        = dlgModel.mVersion02
            body.version03Combo.currentIndex        = dlgModel.mVersion03
            body.productNumberInput.setTextByValue(dlgModel.mProductNumber)

            if(dlgModel.mIsSupportPdNumEx)
            {
                body.productNumberExInput.setTextByValue(dlgModel.mProductNumberEx)
            }
            onCommandSetEdit(false);
        }
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias serialNumberInput     : _serialNumberInput
            property alias valveModelCombo       : _valveModelCombo
            property alias valveTypeCombo        : _valveTypeCombo
            property alias sealingTypeCombo      : _sealingTypeCombo
            property alias flangeSizeCombo       : _flangeSizeCombo
            property alias methodOfContractCombo : _methodOfContractCombo
            property alias bodyMaterialCombo     : _bodyMaterialCombo
            property alias commInterfaceCombo    : _commInterfaceCombo
            property alias powerOptionCombo      : _powerOptionCombo
            property alias quantifyOfSensorCombo : _quantifyOfSensorCombo
            property alias version01Combo        : _version01Combo
            property alias version02Combo        : _version02Combo
            property alias version03Combo        : _version03Combo
            property alias productNumberInput    : _productNumberInput
            property alias productNumberExInput  : _productNumberExInput
            property real  guiScale              : GUISetting.scale

            height: (GUISetting.line_margin + generalItem.height) + (GUISetting.line_margin + firmwareItem.height) + (GUISetting.line_margin + btnBox.height + GUISetting.line_margin);
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : generalItem

                height: (GUISetting.margin + generalTitle.height          )
                      + (GUISetting.margin + serialNumber.height          )
                      + (GUISetting.margin + _valveModelCombo.height      )
                      + (GUISetting.margin + _valveTypeCombo.height       )
                      + (GUISetting.margin + _sealingTypeCombo.height     )
                      + (GUISetting.margin + _flangeSizeCombo.height      )
                      + (GUISetting.margin + _methodOfContractCombo.height)
                      + (GUISetting.margin + _bodyMaterialCombo.height    )
                      + (GUISetting.margin + _commInterfaceCombo.height   )
                      + (GUISetting.margin + _powerOptionCombo.height     )
                      + (GUISetting.margin + _quantifyOfSensorCombo.height)
                      + (GUISetting.margin + _version01Combo.height       )
                      + (GUISetting.margin + _productNumberInput.height   )+ (GUISetting.margin);
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : generalTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("General")
                }

                NText{
                    id : serialNumberLabel
                    anchors.verticalCenter: serialNumber.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    width : 150 * GUISetting.scale
                    text : qsTr("serial number")
                }

                NText{
                    id : serialNumber
                    anchors.top: generalTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: serialNumberLabel.right; anchors.leftMargin: GUISetting.margin * 2
                    height: 24  * GUISetting.scale; width : parent.width - (GUISetting.margin + serialNumberLabel.width + (GUISetting.margin * 2) + GUISetting.margin)
                    verticalAlignment: Text.AlignVCenter
                    visible: !dialog.unlock
                    text : dlgModel.mSerialNumber
                }

                NInputText{
                    id : _serialNumberInput

                    property bool isInvalidValue : false
                    anchors.verticalCenter: serialNumber.verticalCenter; anchors.horizontalCenter: serialNumber.horizontalCenter
                    height: 24  * GUISetting.scale; width : serialNumber.width

                    textField.color: isInvalidValue ? "#FF0000" : "#000000" //textColor
                    enabled: dialog.progress === 100
                    visible: dialog.unlock
                    //textField.text: seqItem.seqItemModel.mCommand

                    onChangedValue: {

                        while(value.search("-") > -1)
                            value = value.replace("-","");

                        while(value.search(" ") > -1)
                            value = value.replace(" ","");

                        _serialNumberInput.isInvalidValue = !dialog.setValveIDBySerialNumber(value)

                        if( _serialNumberInput.isInvalidValue === false)
                            textField.text = dialog.buildSerialNumberByGUI()

                    }
                }

                NText{
                    id : valveModelLabel
                    anchors.verticalCenter: valveModel.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    width : 150 * GUISetting.scale
                    text : qsTr("valve model")
                }

                NText{
                    id : valveModel
                    anchors.top: serialNumber.bottom; anchors.topMargin: GUISetting.margin; anchors.left: valveModelLabel.right; anchors.leftMargin: GUISetting.margin * 2
                    height: 24  * GUISetting.scale; width : parent.width - (GUISetting.margin + valveModelLabel.width + (GUISetting.margin * 2) + GUISetting.margin)
                    verticalAlignment: Text.AlignVCenter
                    visible: !dialog.unlock
                    text : valveModelCombo.currentText
                }

                NComboBox{
                    id : _valveModelCombo
                    anchors.verticalCenter: valveModel.verticalCenter; anchors.horizontalCenter: valveModel.horizontalCenter
                    height: 24  * GUISetting.scale; width : valveModel.width

                    textColor: dlgModel.mErrValveModel ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100
                    visible: dialog.unlock

                    model: ["Unknown", "A : APC", "M : Manual", "G : Gate", "U : UHV Gate", "L : Low cost APC"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    id : valveTypeLabel
                    anchors.verticalCenter: valveType.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    width : 150  * GUISetting.scale
                    text : qsTr("valve type")
                }

                NText{
                    id : valveType
                    anchors.top: valveModel.bottom; anchors.topMargin: GUISetting.margin; anchors.left: valveTypeLabel.right; anchors.leftMargin: GUISetting.margin * 2
                    height: 24  * GUISetting.scale; width : parent.width - (GUISetting.margin + valveTypeLabel.width + (GUISetting.margin * 2) + GUISetting.margin)
                    verticalAlignment: Text.AlignVCenter
                    visible: !dialog.unlock
                    text : _valveTypeCombo.currentText
                }

                NComboBox{
                    id : _valveTypeCombo
                    anchors.verticalCenter: valveType.verticalCenter; anchors.horizontalCenter: valveType.horizontalCenter
                    height: 24 * GUISetting.scale; width : valveType.width

                    textColor: dlgModel.mErrValveType ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100
                    visible: dialog.unlock

                    model: ["Unknown", "B : Butterfly", "P : Pendulum", "C : Circular"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    id : sealingTypeLabel
                    anchors.verticalCenter: sealingType.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    width : 150 * GUISetting.scale
                    text : qsTr("sealing type")
                }

                NText{
                    id : sealingType
                    anchors.top: valveType.bottom; anchors.topMargin: GUISetting.margin; anchors.left: sealingTypeLabel.right; anchors.leftMargin: GUISetting.margin * 2
                    height: 24 * GUISetting.scale; width : parent.width - (GUISetting.margin + sealingTypeLabel.width + (GUISetting.margin * 2) + GUISetting.margin)
                    verticalAlignment: Text.AlignVCenter
                    visible: !dialog.unlock
                    text : sealingTypeCombo.currentText
                }

                NComboBox{
                    id : _sealingTypeCombo
                    anchors.verticalCenter: sealingType.verticalCenter; anchors.horizontalCenter: sealingType.horizontalCenter
                    height: 24 * GUISetting.scale; width : sealingType.width

                    textColor: dlgModel.mErrSealingType ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100
                    visible: dialog.unlock

                    model: ["Unknown", "N : Non-Sealing", "S : Sealing", "F : FCup-Sealing", "X : Multi-position"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    id : flangeSizeLabel
                    anchors.verticalCenter: flangeSize.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    width : 150 * GUISetting.scale
                    text : qsTr("flange size")
                }

                NText{
                    id : flangeSize
                    anchors.top: sealingType.bottom; anchors.topMargin: GUISetting.margin; anchors.left: flangeSizeLabel.right; anchors.leftMargin: GUISetting.margin * 2
                    height: 24 * GUISetting.scale; width : parent.width - (GUISetting.margin + flangeSizeLabel.width + (GUISetting.margin * 2) + GUISetting.margin)
                    verticalAlignment: Text.AlignVCenter
                    visible: !dialog.unlock
                    text : flangeSizeCombo.currentText
                }

                NComboBox{
                    id : _flangeSizeCombo
                    anchors.verticalCenter: flangeSize.verticalCenter; anchors.horizontalCenter: flangeSize.horizontalCenter
                    height: 24 * GUISetting.scale; width : flangeSize.width

                    textColor: dlgModel.mErrFlangeSize ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100
                    visible: dialog.unlock

                    model: ["Unknown", "040 : DN40", "050 : DN50", "063 : DN63" , "080 : DN80" , "100 : DN100" , "160 : DN160" , "200 : DN200" , "250 : DN250", "025 : DN25", "320 : DN320"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    id : methodOfContractLabel
                    anchors.verticalCenter: methodOfContract.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    width : 150 * GUISetting.scale
                    text : qsTr("method of contract")
                }

                NText{
                    id : methodOfContract
                    anchors.top: flangeSize.bottom; anchors.topMargin: GUISetting.margin; anchors.left: methodOfContractLabel.right; anchors.leftMargin: GUISetting.margin * 2
                    height: 24 * GUISetting.scale; width : parent.width - (GUISetting.margin + methodOfContractLabel.width + (GUISetting.margin * 2) + GUISetting.margin)
                    verticalAlignment: Text.AlignVCenter
                    visible: !dialog.unlock
                    text : methodOfContractCombo.currentText
                }

                NComboBox{
                    id : _methodOfContractCombo
                    anchors.verticalCenter: methodOfContract.verticalCenter; anchors.horizontalCenter: methodOfContract.horizontalCenter
                    height: 24 * GUISetting.scale; width : methodOfContract.width

                    textColor: dlgModel.mErrMethodOfContract ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100
                    visible: dialog.unlock

                    model: ["Unknown", "K : ISO-KF", "F : ISO", "C : CF-F", "P : ISO-K", "X : Multi-position"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    id : bodyMaterialLabel
                    anchors.verticalCenter: bodyMaterial.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    width : 150 * GUISetting.scale
                    text : qsTr("body material")
                }

                NText{
                    id : bodyMaterial
                    anchors.top: methodOfContract.bottom; anchors.topMargin: GUISetting.margin; anchors.left: bodyMaterialLabel.right; anchors.leftMargin: GUISetting.margin * 2
                    height: 24 * GUISetting.scale; width : parent.width - (GUISetting.margin + bodyMaterialLabel.width + (GUISetting.margin * 2) + GUISetting.margin)
                    verticalAlignment: Text.AlignVCenter
                    visible: !dialog.unlock
                    text : bodyMaterialCombo.currentText
                }

                NComboBox{
                    id : _bodyMaterialCombo
                    anchors.verticalCenter: bodyMaterial.verticalCenter; anchors.horizontalCenter: bodyMaterial.horizontalCenter
                    height: 24 * GUISetting.scale; width : bodyMaterial.width

                    textColor: dlgModel.mErrBodyMaterial ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100
                    visible: dialog.unlock

                    model: ["Unknown", "A : Aluminum", "S : SUS304", "L : SUS316L", "X : Multi-position"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    id : commInterfaceLabel
                    anchors.verticalCenter: commInterface.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    width : 150 * GUISetting.scale
                    text : qsTr("communication interface")
                }

                NText{
                    id : commInterface
                    anchors.top: bodyMaterial.bottom; anchors.topMargin: GUISetting.margin; anchors.left: commInterfaceLabel.right; anchors.leftMargin: GUISetting.margin * 2
                    height: 24 * GUISetting.scale; width : parent.width - (GUISetting.margin + commInterfaceLabel.width + (GUISetting.margin * 2) + GUISetting.margin)
                    verticalAlignment: Text.AlignVCenter
                    visible: !dialog.unlock
                    text : commInterfaceCombo.currentText
                }

                NComboBox{
                    id : _commInterfaceCombo
                    anchors.verticalCenter: commInterface.verticalCenter; anchors.horizontalCenter: commInterface.horizontalCenter
                    height: 24 * GUISetting.scale; width : commInterface.width

                    textColor: dlgModel.mErrCommInterface ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100
                    visible: dialog.unlock

                    model: ["Unknown", "R2 : RS-232", "R3 : RS-232 with analog outputs", "R4 : RS-485", "LO : Logic", "DN : DeviceNet", "PB : Profibus", "EN : Ethernet", "CC : CC-Link", "EC : EtherCAT", "LL : Legacy Logic", "LD : Legacy DeviceNet", "AD : AP DeviceNet", "RL : Retrofit Logic"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    id : powerOptionLabel
                    anchors.verticalCenter: powerOption.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    width : 150 * GUISetting.scale
                    text : qsTr("power option")
                }

                NText{
                    id : powerOption
                    anchors.top: commInterface.bottom; anchors.topMargin: GUISetting.margin; anchors.left: powerOptionLabel.right; anchors.leftMargin: GUISetting.margin * 2
                    height: 24 * GUISetting.scale; width : parent.width - (GUISetting.margin + powerOptionLabel.width + (GUISetting.margin * 2) + GUISetting.margin)
                    verticalAlignment: Text.AlignVCenter
                    visible: ! dialog.unlock
                    text : powerOptionCombo.currentText
                }

                NComboBox{
                    id : _powerOptionCombo
                    anchors.verticalCenter: powerOption.verticalCenter; anchors.horizontalCenter: powerOption.horizontalCenter
                    height: 24 * GUISetting.scale; width : powerOption.width

                    textColor: dlgModel.mErrPowerOption ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100
                    visible: dialog.unlock

                    model: ["Unknown", "B : Basic", "S : SPS", "P : with PFO", "D : with SPS and PFO", "U : with UPS", "A : with SPS & UPS"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    id : quantifyOfSensorLabel
                    anchors.verticalCenter: quantifyOfSensor.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    width : 150 * GUISetting.scale
                    text : qsTr("quantity of sensors")
                }

                NText{
                    id : quantifyOfSensor
                    anchors.top: powerOption.bottom; anchors.topMargin: GUISetting.margin; anchors.left: quantifyOfSensorLabel.right; anchors.leftMargin: GUISetting.margin * 2
                    height: 24 * GUISetting.scale; width : parent.width - (GUISetting.margin + quantifyOfSensorLabel.width + (GUISetting.margin * 2) + GUISetting.margin)
                    verticalAlignment: Text.AlignVCenter
                    visible: !dialog.unlock
                    text : quantifyOfSensorCombo.currentText
                }

                NComboBox{
                    id : _quantifyOfSensorCombo
                    anchors.verticalCenter: quantifyOfSensor.verticalCenter; anchors.horizontalCenter: quantifyOfSensor.horizontalCenter
                    height: 24  * GUISetting.scale; width : quantifyOfSensor.width

                    textColor: dlgModel.mErrQuantityOfSensors ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100
                    visible: dialog.unlock

                    model: ["0 : 0 Sensor", "1 : 1 Sensor", "2 : 2 Sensor"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    id : versionLabel
                    anchors.verticalCenter: version.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    width : 150  * GUISetting.scale
                    text : qsTr("version")
                }

                NText{
                    id : version
                    anchors.top: quantifyOfSensor.bottom; anchors.topMargin: GUISetting.margin; anchors.left: versionLabel.right; anchors.leftMargin: GUISetting.margin * 2
                    height: 24  * GUISetting.scale; width : parent.width - (GUISetting.margin + versionLabel.width + (GUISetting.margin * 2) + GUISetting.margin)
                    verticalAlignment: Text.AlignVCenter
                    visible: !dialog.unlock
                    text : "R" + version01Combo.currentText + version02Combo.currentText + version03Combo.currentText
                }

                NComboBox{
                    id : _version01Combo
                    anchors.verticalCenter: version.verticalCenter; anchors.left: version.left;
                    height: 24 * GUISetting.scale; width : (version.width / 3) - GUISetting.margin

                    textColor: dlgModel.mErrVersion01 ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100
                    visible: dialog.unlock

                    model: ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NComboBox{
                    id : _version02Combo
                    anchors.verticalCenter: version.verticalCenter; anchors.horizontalCenter: version.horizontalCenter;
                    height: 24 * GUISetting.scale; width : (version.width / 3) - GUISetting.margin

                    textColor: dlgModel.mErrVersion02 ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100
                    visible: dialog.unlock

                    model: ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NComboBox{
                    id : _version03Combo
                    anchors.verticalCenter: version.verticalCenter; anchors.right: version.right;
                    height: 24 * GUISetting.scale; width : (version.width / 3) - GUISetting.margin

                    textColor: dlgModel.mErrVersion03 ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100
                    visible: dialog.unlock

                    model: ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    id : productNumberLabel
                    anchors.verticalCenter: productNumber.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    width : 150 * GUISetting.scale
                    text : qsTr("product number")
                }

                NText{
                    id : productNumber
                    anchors.top: version.bottom; anchors.topMargin: GUISetting.margin; anchors.left: productNumberLabel.right; anchors.leftMargin: GUISetting.margin * 2
                    height: 24 * GUISetting.scale; width : parent.width - (GUISetting.margin + productNumberLabel.width + (GUISetting.margin * 2) + GUISetting.margin)
                    verticalAlignment: Text.AlignVCenter
                    visible: !dialog.unlock
                    text : dlgModel.mIsSupportPdNumEx ? _productNumberInput.textField.text + "-" + _productNumberExInput.textField.text : _productNumberInput.textField.text
                }

                NInputNumber{
                    id : _productNumberInput
                    anchors.verticalCenter: productNumber.verticalCenter; anchors.left: productNumber.left;
                    height: 24 * GUISetting.scale; width : (productNumber.width / 2) - (GUISetting.margin / 2)

                    textField.color: dlgModel.mErrProductNumber ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100
                    visible: dialog.unlock

                    isHexMode: true
                    padN : 4
                    textField.validator: RegExpValidator { regExp: /[0-9A-Fa-f]{0,4}/ }
                    stepValue : 1; minValue: 0; maxValue: 65535
                    fixedN : 0

                    onChangedValue: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NInputNumber{
                    id : _productNumberExInput
                    anchors.verticalCenter: productNumber.verticalCenter; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    height: 24 * GUISetting.scale; width : (productNumber.width / 2) - (GUISetting.margin / 2)

                    textField.color: dlgModel.mErrProductNumberEx ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100 && dlgModel.mIsSupportPdNumEx
                    visible: dialog.unlock

                    isHexMode: true
                    padN : 6
                    textField.validator: RegExpValidator { regExp: /[0-9A-Fa-f]{0,6}/ }
                    stepValue : 1; minValue: 0; maxValue: 16777215
                    fixedN : 0

                    onChangedValue: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }
            }

            Rectangle{
                id : firmwareItem

                height: (GUISetting.margin + firmwareTitle.height         )
                      + (GUISetting.margin + firmwareVersion.height       ) + GUISetting.margin;
                anchors.top: generalItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : firmwareTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Firmware")
                }

                NText{
                    id : firmwareVersionLabel
                    anchors.verticalCenter: firmwareVersion.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    width : 150 * GUISetting.scale
                    text : qsTr("firmware version")
                }

                NText{
                    id : firmwareVersion
                    anchors.top: firmwareTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: firmwareVersionLabel.right; anchors.leftMargin: GUISetting.margin * 2
                    height: 24 * GUISetting.scale; width : parent.width - (GUISetting.margin + firmwareVersionLabel.width + (GUISetting.margin * 2) + GUISetting.margin)
                    verticalAlignment: Text.AlignVCenter
                    text : dlgModel.mFirmwareVersion.slice(0, 6) + "-" + dlgModel.mFirmwareVersion.slice(6);
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: firmwareItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NButton{
                    id : editBtn
                    height: GUISetting.popup_btnbox_btn_height; width: parent.width / 2
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                    enabled: dialog.progress === 100
                    visible: !dialog.unlock

                    bgColor: "#24A7FF"
                    text.color: "#FFFFFF"
                    text.text: qsTr("Edit")

                    onClick: {
                        dialog.openPasswordDlg()
                    }
                }


                NButton{
                    id : applyBtn
                    height: GUISetting.popup_btnbox_btn_height; width: parent.width / 2
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                    enabled: dialog.progress === 100
                    visible: dialog.unlock

                    bgColor: "#24A7FF"
                    text.color: "#FFFFFF"
                    text.text: qsTr("Apply")

                    NCircleIndicator{
                        width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                        anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter

                        color: "#FF0000"
                        visible: dialog.isEdit
                    }

                    onClick: {
                        dialog.apply()
                    }
                }

            }
        }
    }

    Component{
        id : passwordDlg
        PasswordDlg
        {
            onResult: {
                dialog.unlock = true
            }
        }
    }
}
