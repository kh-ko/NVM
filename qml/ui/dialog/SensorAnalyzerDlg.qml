import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import "../../control/."
import ValveEnumDef 1.0
import FontManager 1.0
import NChartView 1.0
import SensorAnalysisDlgModel 1.0
import GUISetting 1.0

NWindow{ // khko_todo
    id : dialog

    property var connectInfo : ""
    property var valveID     : ""
    property string strUnit : dlgModel.mDpUnit === ValveEnumDef.PRESSURE_UNIT_PA    ? "[pa]"      :
                              dlgModel.mDpUnit === ValveEnumDef.PRESSURE_UNIT_BAR   ? "[bar]"     :
                              dlgModel.mDpUnit === ValveEnumDef.PRESSURE_UNIT_MBAR  ? "[mbar]"    :
                              dlgModel.mDpUnit === ValveEnumDef.PRESSURE_UNIT_UBAR  ? "[ubar]"    :
                              dlgModel.mDpUnit === ValveEnumDef.PRESSURE_UNIT_TORR  ? "[Torr]"    :
                              dlgModel.mDpUnit === ValveEnumDef.PRESSURE_UNIT_MTORR ? "[mTorr]"   :
                              dlgModel.mDpUnit === ValveEnumDef.PRESSURE_UNIT_ATM   ? "[atm]"     :
                              dlgModel.mDpUnit === ValveEnumDef.PRESSURE_UNIT_PSI   ? "[psi]"     :
                              dlgModel.mDpUnit === ValveEnumDef.PRESSURE_UNIT_PSF   ? "[psf]"     :
                              dlgModel.mDpUnit === ValveEnumDef.PRESSURE_UNIT_VOLT  ? "[voltage]" :
                              dlgModel.mDpUnit === ValveEnumDef.PRESSURE_UNIT_MVOLT ? "[mv]" :""

    contentHeight: contentContainer.height; contentWidth: contentContainer.width

    SensorAnalysisDlgModel{
        id :dlgModel

        onSignalEventAddSensorValue: {
            chart.onCommandAddPoint(msec * 0.001, sensor01Value, 1, sensor02Value, 1)
        }

        onSignalEventChangedProgress: {
            if(mProgress == 100)
            {
                unitCombo.currentIndex = dlgModel.mDpUnit
                scaleCombo.currentIndex = dlgModel.mAutoScale ? 0 : 1
                timeCombo.currentIndex = 0

                sensor01Min.setValue(dlgModel.mSensor01Min);
                sensor01Max.setValue(dlgModel.mSensor01Max);
                sensor02Min.setValue(dlgModel.mSensor02Min);
                sensor02Max.setValue(dlgModel.mSensor02Max);

                onCommandSetIsEdit(false);
                chart.onCommandInit(FontManager.nanumGothicName, 8, "#0000FF", "#ED1C24", true, false, true, true, dlgModel.mS01Selction, false, dlgModel.mS02Selction, false);
            }
        }

        onSignalEventChangedGraphSetting: {
            if(dlgModel.mS01Selction)
            {
                chart.mYAxis01Min = dlgModel.mSensor01Min
                chart.mYAxis01Max = dlgModel.mSensor01Max
            }
            if(dlgModel.mS02Selction)
            {
                chart.mYAxis02Min = dlgModel.mSensor02Min
                chart.mYAxis02Max = dlgModel.mSensor02Max
            }
        }
    }

    Item {
        id : contentContainer
        height: titleBox.height + body.height + statusBar.height; width: body.width
        anchors.centerIn: parent

        NPopupTilte{
            id : titleBox
            root: dialog
            enableMinimizeBtn: true
            title: qsTr("Sensor analysis")

            onClickClose: {
                dialog.close();
            }

            onClickMinimized: {
                dialog.showMinimized()
            }
        }

        Rectangle{
            id : body
            height: (GUISetting.line_margin + generalStatusItem.height) + (GUISetting.line_margin + s01StatusItem.height) + (GUISetting.line_margin + graphSettingItem.height) + GUISetting.line_margin;
            width: 900 * GUISetting.scale
            anchors.left: parent.left; anchors.top: titleBox.bottom

            color : "#E4E4E4"

            Rectangle{
                id : generalStatusItem
                height:   (GUISetting.margin + generalStatusTitle.height)
                        + (GUISetting.margin + sensorFullScale.height   )
                        + (GUISetting.margin + sensorFactor.height      ) + GUISetting.margin;
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : generalStatusTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("general sensor status")
                }

                Rectangle{
                    id : sensorFullScale
                    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                    anchors.top: generalStatusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    color : "#E4E4E4"

                    NText{
                        anchors.verticalCenter: sensorFullScale.verticalCenter; anchors.left: sensorFullScale.left; anchors.leftMargin: GUISetting.margin
                        text : dlgModel.mIsS01HighSensor ? dlgModel.mStrS01FullScale : dlgModel.mStrS02FullScale
                    }
                }

                NText{
                    anchors.verticalCenter: sensorFullScale.verticalCenter; anchors.left: sensorFullScale.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("sensor full scale") + dialog.strUnit
                }

                Rectangle{
                    id : sensorFactor
                    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                    anchors.top: sensorFullScale.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    color : "#E4E4E4"
                }

                NText{
                    anchors.verticalCenter: sensorFactor.verticalCenter; anchors.left: sensorFactor.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("sensor factor")
                }

                Rectangle{
                    id : zeroAdjust
                    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                    anchors.top: generalStatusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: (parent.width/2) + GUISetting.margin

                    NText{
                        anchors.verticalCenter: zeroAdjust.verticalCenter; anchors.left: zeroAdjust.left; anchors.leftMargin: GUISetting.margin
                        text : dlgModel.mIsEnableZero ? qsTr("enabled") : qsTr("disabled")
                    }

                    color : "#E4E4E4"
                }

                NText{
                    anchors.verticalCenter: zeroAdjust.verticalCenter; anchors.left: zeroAdjust.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("zero adjust")
                }

                Rectangle{
                    id : resultingPressure
                    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                    anchors.top: zeroAdjust.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: (parent.width/2) + GUISetting.margin

                    color : "#E4E4E4"

                    NText{
                        anchors.verticalCenter: resultingPressure.verticalCenter; anchors.left: resultingPressure.left; anchors.leftMargin: GUISetting.margin
                        text : dlgModel.mStrResultingPressure
                    }
                }

                NText{
                    anchors.verticalCenter: resultingPressure.verticalCenter; anchors.left: resultingPressure.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("resulting pressure")  + dialog.strUnit
                }
            }

            Rectangle{
                id : s01StatusItem
                height:   (GUISetting.margin + s01StatusTitle.height  )
                        + (GUISetting.margin + s01Selection.height    )
                        + (GUISetting.margin + s01FullScale.height    )
                        + (GUISetting.margin + s01Processing.height   )
                        + (GUISetting.margin + s01MeasuredValue.height)
                        + (GUISetting.line_margin + s01Offset.height  )
                        + (GUISetting.line_margin + s01Value.height   ) + GUISetting.margin;
                width: (parent.width - (GUISetting.line_margin * 3))/2
                anchors.top: generalStatusItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : s01StatusTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("sensor port 1")
                }

                Rectangle{
                    id : s01Selection
                    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                    anchors.top: s01StatusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    NText{
                        anchors.verticalCenter: s01Selection.verticalCenter; anchors.left: s01Selection.left; anchors.leftMargin: GUISetting.margin
                        text : dlgModel.mS01Selction ? qsTr("selected") : qsTr("not selected")
                    }

                    color : "#E4E4E4"
                }

                NText{
                    anchors.verticalCenter: s01Selection.verticalCenter; anchors.left: s01Selection.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("selection")
                }

                Rectangle{
                    id : s01FullScale
                    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                    anchors.top: s01Selection.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    NText{
                        anchors.verticalCenter: s01FullScale.verticalCenter; anchors.left: s01FullScale.left; anchors.leftMargin: GUISetting.margin
                        text : dlgModel.mStrS01FullScale
                    }

                    color : "#E4E4E4"
                }

                NText{
                    anchors.verticalCenter: s01FullScale.verticalCenter; anchors.left: s01FullScale.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("full scale") + dialog.strUnit
                }

                Rectangle{
                    id : s01Processing
                    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                    anchors.top: s01FullScale.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    color : dlgModel.mS01IsProcessing ? "#24A7FF" : "#E4E4E4"

                    NText{
                        anchors.verticalCenter: s01Processing.verticalCenter; anchors.left: s01Processing.left; anchors.leftMargin: GUISetting.margin
                        text : dlgModel.mS01ProcessingPct
                    }
                }

                NText{
                    anchors.verticalCenter: s01Processing.verticalCenter; anchors.left: s01Processing.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("processing")
                }

                Rectangle{
                    id : s01MeasuredValue
                    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                    anchors.top: s01Processing.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    NText{
                        anchors.verticalCenter: s01MeasuredValue.verticalCenter; anchors.left: s01MeasuredValue.left; anchors.leftMargin: GUISetting.margin
                        text : dlgModel.mStrS01MeasuredValue
                    }

                    color : "#E4E4E4"
                }

                NText{
                    anchors.verticalCenter: s01MeasuredValue.verticalCenter; anchors.left: s01MeasuredValue.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("measured value") + dialog.strUnit
                }

                Rectangle{
                    id : s01Offset
                    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                    anchors.top: s01MeasuredValue.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    color : "#E4E4E4"

                    NText{
                        anchors.verticalCenter: s01Offset.verticalCenter; anchors.left: s01Offset.left; anchors.leftMargin: GUISetting.margin
                        text : dlgModel.mStrS01OffsetValue
                    }
                }

                NText{
                    anchors.verticalCenter: s01Offset.verticalCenter; anchors.left: s01Offset.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("offset") + dialog.strUnit
                }

                Rectangle{
                    id : s01Value
                    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                    anchors.top: s01Offset.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    color : "#E4E4E4"

                    NText{
                        anchors.verticalCenter: s01Value.verticalCenter; anchors.left: s01Value.left; anchors.leftMargin: GUISetting.margin
                        text : dlgModel.mStrS01Value
                    }
                }

                NText{
                    anchors.verticalCenter: s01Value.verticalCenter; anchors.left: s01Value.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("value(offset considered)") + dialog.strUnit
                }
            }

            Rectangle{
                id : s02StatusNotSupportItem
                height: s02StatusItem.height;
                width: (parent.width - (GUISetting.line_margin * 3))/2
                anchors.top: generalStatusItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"
                visible: !dlgModel.mIsSensor02Support

                NText{
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("sensor port 2")
                }

                Image{
                    id : warningImg
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin * 2
                    source: "/image/icon-warning.png"
                }

                NText{
                    anchors.verticalCenter: warningImg.verticalCenter; anchors.left: warningImg.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("Sensor 2 is not supported")
                }
            }

            Rectangle{
                id : s02StatusItem
                height:   (GUISetting.margin + s02StatusTitle.height  )
                        + (GUISetting.margin + s02Selection.height    )
                        + (GUISetting.margin + s02FullScale.height    )
                        + (GUISetting.margin + s02Processing.height   )
                        + (GUISetting.margin + s02MeasuredValue.height)
                        + (GUISetting.line_margin + s02Offset.height       )
                        + (GUISetting.line_margin + s02Value.height        ) + GUISetting.margin;
                width: (parent.width - (GUISetting.line_margin * 3))/2
                anchors.top: generalStatusItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"
                visible: dlgModel.mIsSensor02Support

                NText{
                    id : s02StatusTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("sensor port 2")
                }

                Rectangle{
                    id : s02Selection
                    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                    anchors.top: s02StatusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    color : "#E4E4E4"

                    NText{
                        anchors.verticalCenter: s02Selection.verticalCenter; anchors.left: s02Selection.left; anchors.leftMargin: GUISetting.margin
                        text : dlgModel.mS02Selction ? qsTr("selected") : qsTr("not selected")
                    }
                }

                NText{
                    anchors.verticalCenter: s02Selection.verticalCenter; anchors.left: s02Selection.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("selection")
                }

                Rectangle{
                    id : s02FullScale
                    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                    anchors.top: s02Selection.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    color : "#E4E4E4"

                    NText{
                        anchors.verticalCenter: s02FullScale.verticalCenter; anchors.left: s02FullScale.left; anchors.leftMargin: GUISetting.margin
                        text : dlgModel.mStrS02FullScale
                    }
                }

                NText{
                    anchors.verticalCenter: s02FullScale.verticalCenter; anchors.left: s02FullScale.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("full scale") + dialog.strUnit
                }

                Rectangle{
                    id : s02Processing
                    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                    anchors.top: s02FullScale.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    color : dlgModel.mS02IsProcessing ? "#24A7FF" : "#E4E4E4"

                    NText{
                        anchors.verticalCenter: s02Processing.verticalCenter; anchors.left: s02Processing.left; anchors.leftMargin: GUISetting.margin
                        text : dlgModel.mS02ProcessingPct
                    }
                }

                NText{
                    anchors.verticalCenter: s02Processing.verticalCenter; anchors.left: s02Processing.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("processing")
                }

                Rectangle{
                    id : s02MeasuredValue
                    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                    anchors.top: s02Processing.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    color : "#E4E4E4"

                    NText{
                        anchors.verticalCenter: s02MeasuredValue.verticalCenter; anchors.left: s02MeasuredValue.left; anchors.leftMargin: GUISetting.margin
                        text : dlgModel.mStrS02MeasuredValue
                    }
                }

                NText{
                    anchors.verticalCenter: s02MeasuredValue.verticalCenter; anchors.left: s02MeasuredValue.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("measured value") + dialog.strUnit
                }

                Rectangle{
                    id : s02Offset
                    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                    anchors.top: s02MeasuredValue.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    color : "#E4E4E4"

                    NText{
                        anchors.verticalCenter: s02Offset.verticalCenter; anchors.left: s02Offset.left; anchors.leftMargin: GUISetting.margin
                        text : dlgModel.mStrS02OffsetValue
                    }
                }

                NText{
                    anchors.verticalCenter: s02Offset.verticalCenter; anchors.left: s02Offset.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("offset") + dialog.strUnit
                }

                Rectangle{
                    id : s02Value
                    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                    anchors.top: s02Offset.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    color : "#E4E4E4"

                    NText{
                        anchors.verticalCenter: s02Value.verticalCenter; anchors.left: s02Value.left; anchors.leftMargin: GUISetting.margin
                        text : dlgModel.mStrS02Value
                    }
                }

                NText{
                    anchors.verticalCenter: s02Value.verticalCenter; anchors.left: s02Value.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("value(offset considered)") + dialog.strUnit
                }
            }

            Rectangle{
                id : graphSettingItem
                height: graphItem.height; width: 200 * GUISetting.scale
                anchors.verticalCenter: graphItem.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : graphSettingTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("graph settings")
                }

                NComboBox{
                    id : unitCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: graphSettingTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mIsEditDpUnit ? "#24A7FF" : "#000000"

                    model: ["pa","bar","mbar","ubar", "Torr", "mTorr", "atm", "psi", "psf","voltage", "mv"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetIsEditDpUnit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: unitCombo.verticalCenter; anchors.left: unitCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("unit")
                }

                NComboBox{
                    id : timeCombo

                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: unitCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mIsEditXMsec ? "#24A7FF" : "#000000"

                    model: ["30 seconds","1 minute","2 minutes","5 minutes"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetIsEditXMsec(true)
                    }

                }

                NText{
                    anchors.verticalCenter: timeCombo.verticalCenter; anchors.left: timeCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("time interval")
                }

                NComboBox{
                    id : scaleCombo

                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: timeCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mIsEditAutoScale ? "#24A7FF" : "#000000"

                    model: ["auto","fixed"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetIsEditAutoScale(true)
                    }
                }

                NText{
                    anchors.verticalCenter: scaleCombo.verticalCenter; anchors.left: scaleCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("scale")
                }

                NInputNumber{
                    id : sensor01Min
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: scaleCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: scaleCombo.currentIndex == 1 && dlgModel.mS01Selction

                    textField.validator: DoubleValidator{}
                    textField.color:  dlgModel.mIsEditSensor01Min ? "#24A7FF" : dlgModel.mIsErrSensor01MinMax ? "#FF0000" : "#000000"
                    stepValue : 0.0001; minValue: -100000000; maxValue: 100000000
                    fixedN : dlgModel.mS01GraphPrecN

                    onChangedText: {
                        dlgModel.onCommandSetIsEditSensor01Min(true)
                    }
                }
                NText{
                    anchors.verticalCenter: sensor01Min.verticalCenter; anchors.left: sensor01Min.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("sensor 01 min")
                }

                NInputNumber{
                    id : sensor01Max
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: sensor01Min.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: scaleCombo.currentIndex == 1 && dlgModel.mS01Selction

                    textField.validator: DoubleValidator{}
                    textField.color:  dlgModel.mIsEditSensor01Max ? "#24A7FF" : dlgModel.mIsErrSensor01MinMax ? "#FF0000" : "#000000"
                    stepValue : 0.0001; minValue: -100000000; maxValue: 100000000
                    fixedN : dlgModel.mS01GraphPrecN

                    onChangedText: {
                        dlgModel.onCommandSetIsEditSensor01Max(true)
                    }
                }
                NText{
                    anchors.verticalCenter: sensor01Max.verticalCenter; anchors.left: sensor01Max.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("sensor 01 max")
                }

                NInputNumber{
                    id : sensor02Min
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: sensor01Max.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: scaleCombo.currentIndex == 1 && dlgModel.mS02Selction

                    textField.validator: DoubleValidator{}
                    textField.color:  dlgModel.mIsEditSensor02Min ? "#24A7FF" : dlgModel.mIsErrSensor02MinMax ? "#FF0000" : "#000000"
                    stepValue : 0.0001; minValue: -100000000; maxValue: 100000000
                    fixedN : dlgModel.mS02GraphPrecN

                    onChangedText: {
                        dlgModel.onCommandSetIsEditSensor02Min(true)
                    }
                }
                NText{
                    anchors.verticalCenter: sensor02Min.verticalCenter; anchors.left: sensor02Min.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("sensor 02 min")
                }

                NInputNumber{
                    id : sensor02Max
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: sensor02Min.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: scaleCombo.currentIndex == 1 && dlgModel.mS02Selction

                    textField.validator: DoubleValidator{}
                    textField.color:  dlgModel.mIsEditSensor02Max ? "#24A7FF" : dlgModel.mIsErrSensor02MinMax ? "#FF0000" : "#000000"
                    stepValue : 0.0001; minValue: -100000000; maxValue: 100000000
                    fixedN : dlgModel.mS02GraphPrecN

                    onChangedText: {
                        dlgModel.onCommandSetIsEditSensor02Max(true)
                    }
                }
                NText{
                    anchors.verticalCenter: sensor02Max.verticalCenter; anchors.left: sensor02Max.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("sensor 02 max")
                }

                NButton{
                    height: 24 * GUISetting.scale
                    anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    enabled: dlgModel.mIsEdit
                    bgColor: "#24A7FF"
                    text.color: "#FFFFFF"

                    text.text: qsTr("Apply")

                    onClick: {
                        var isAutoScale = scaleCombo.currentIndex == 0 ? true : false
                        dlgModel.onCommandSetGraphSetting(unitCombo.currentIndex, timeCombo.currentIndex, isAutoScale, parseFloat(sensor01Min.textField.text), parseFloat(sensor01Max.textField.text), parseFloat(sensor02Min.textField.text), parseFloat(sensor02Max.textField.text))
                    }
                }
            }


            Rectangle{
                id : graphItem
                height:   (GUISetting.margin + graphTitle.height  )
                        + (GUISetting.margin + sensorChart.height ) + GUISetting.margin;
                anchors.top: s01StatusItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: graphSettingItem.right; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : graphTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("sensor chart")
                }

                Item{
                    id : sensorChart
                    height: 270 * GUISetting.scale
                    anchors.top: graphTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    NChartView{
                        id : chart

                        property int graphPrecN : dlgModel.mS01GraphPrecN < dlgModel.mS02GraphPrecN ? dlgModel.mS01GraphPrecN : dlgModel.mS02GraphPrecN

                        anchors.fill : parent

                        mYAxis01Title      : qsTr("Sensor 1")
                        mYAxis01Min        : 0
                        mYAxis01Max        : parseFloat(dlgModel.mStrS01FullScale)
                        mYAxis01LogDecades : 1
                        mYAxis01Factor     : dlgModel.mS01GraphConvertFactor
                        mYAxis01Precision  : dlgModel.mS01GraphPrecN
                        mYAxis01AutoScale  : dlgModel.mAutoScale
                        mYAxis01Log        : false
                        mY01Draw           : true
                        mY01DashDraw       : false

                        mYAxis02Title      : qsTr("Sensor 2")
                        mYAxis02Min        : 0
                        mYAxis02Max        : parseFloat(dlgModel.mStrS02FullScale)
                        mYAxis02LogDecades : 2
                        mYAxis02Factor     : dlgModel.mS02GraphConvertFactor
                        mYAxis02Precision  : dlgModel.mS02GraphPrecN
                        mYAxis02AutoScale  : dlgModel.mAutoScale
                        mYAxis02Log        : false
                        mY02Draw           : true
                        mY02DashDraw       : false

                        mMiniumScale       : Math.pow(10, (graphPrecN * -1)) * 10
                        mXRange            : dlgModel.mXMsec * 0.001

                        mPause             : false//panel.isPause

                        mDebug             : false

                        Component.onCompleted: {

                        }
                    }
                }
            }
        }

        NPopupStatusBar{
            id : statusBar

            height: 40 * GUISetting.scale; width: parent.width
            anchors.bottom: parent.bottom; anchors.left: parent.left

            progress   : dlgModel.mProgress
            status     : dlgModel.mStrStatus
            errMsg     : dlgModel.mErrMsg
            connectInfo: dialog.connectInfo
            valveID    : dialog.valveID
        }
    }
}

/*

*/
