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
    access      : dlgModel.mAccessMode
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

        dlgModel.onCommandApply(valveModel, valveType, sealingType, flangeSize, methodOfContract, bodyMaterial, commInterface, powerOption, quantifyOfSensor, version01, version02, version03, productNumber)
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = GUISetting.popup_nor_width
    }

    ValveIdentificationExDlgModel{
        id : dlgModel

        onSignalEventCompletedLoad: {
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

            onCommandSetEdit(false);
        }
    }

    Component{
        id : bodyImpl

        Rectangle{
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
                    text : dlgModel.mSerialNumber
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

                    model: ["Unknow", "A : APC"]

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

                    model: ["Unknow", "B : Butterfly", "P : Pendulum"]

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

                    model: ["Unknow", "N : Non-Sealing", "S : Sealing"]

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

                    model: ["Unknow", "040 : DN40", "050 : DN50", "063 : DN63" , "080 : DN80" , "100 : DN100" , "160 : DN160" , "200 : DN200" , "250 : DN250"]

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

                    model: ["Unknow", "K : ISO-KF", "ISO : F"]

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

                    model: ["Unknow", "A : Aluminum", "S : SUS"]

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

                    model: ["Unknow", "R2 : RS-232", "R3 : RS-232 with analog outputs", "R4 : RS-485", "LO : Logic", "DN : DeviceNet", "PB : Profibus", "EN : Ethernet", "CC : CC-Link", "EC : EtherCAT"]

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

                    model: ["Unknow", "B : Basic", "S : SPS", "P : with PFO", "D : with SPS and PFO", "U : with UPS", "A : with SPS & UPS"]

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

                    model: ["Unknow", "1 : 1 Sensor", "2 : 2 Sensor"]

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
                    text : _productNumberInput.textField.text
                }

                NInputNumber{
                    id : _productNumberInput
                    anchors.verticalCenter: productNumber.verticalCenter; anchors.left: productNumber.left;
                    height: 24 * GUISetting.scale; width : productNumber.width

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
                    text : dlgModel.mFirmwareVersion
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
