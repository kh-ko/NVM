#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCursor>
#include <QtQuickControls2/QQuickStyle>
#include <QStyleHints>
#include <QIcon>
#include "source/logger/nsdebug.h"
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/service/coreservice.h"
#include "source/qmlmodel/control/nchartcanvasmodel.h"
#include "source/qmlmodel/qmlcoremodel.h"
#include "source/qmlmodel/debuggingmodel.h"
#include "source/qmlmodel/searchdevicedlgmodel.h"
#include "source/qmlmodel/valveidentificationexdlgmodel.h"
#include "source/qmlmodel/valvesetupdlgmodel.h"
#include "source/qmlmodel/changeaccessdlgmodel.h"
#include "source/qmlmodel/valveparamexdlgmodel.h"
#include "source/qmlmodel/valverecoverydlgmodel.h"
#include "source/qmlmodel/sensorsetupdlgmodel.h"
#include "source/qmlmodel/sensorsetupexdlgmodel.h"
#include "source/qmlmodel/sensoranalysisdlgmodel.h"
#include "source/qmlmodel/pressurectrlsetupdlgmodel.h"
#include "source/qmlmodel/pressurectrlfloatsetupdlgmodel.h"
#include "source/qmlmodel/pressurectrllearnparamdlgmodel.h"
#include "source/qmlmodel/pressurectrllearnlistdlgmodel.h"
#include "source/qmlmodel/ncpasettingsdlgmodel.h"
#include "source/qmlmodel/interfacesetupdevnetdlgmodel.h"
#include "source/qmlmodel/interfacesetuplogicdlgmodel.h"
#include "source/qmlmodel/interfacesetupethercatdlgmodel.h"
#include "source/qmlmodel/interfacesetuprs232dlgmodel.h"
#include "source/qmlmodel/interfacesetupethernetdlgmodel.h"
#include "source/qmlmodel/interfacesetupprofibusdlgmodel.h"
#include "source/qmlmodel/interfacestatuslogicdlgmodel.h"
#include "source/qmlmodel/interfacestatusethercatdlgmodel.h"
#include "source/qmlmodel/interfacestatusdnetdlgmodel.h"
#include "source/qmlmodel/interfacestatusrs232dlgmodel.h"
#include "source/qmlmodel/interfacestatusprofibusdlgmodel.h"
#include "source/qmlmodel/interfacetracedlgmodel.h"
#include "source/qmlmodel/valvecyclecounterdlgmodel.h"
#include "source/qmlmodel/valvecaribrationdlgmodel.h"
#include "source/qmlmodel/valvecalibrationexdlgmodel.h"
#include "source/qmlmodel/controlzerodlgmodel.h"
#include "source/qmlmodel/controllearndlgmodel.h"
#include "source/qmlmodel/fatalerrordlgmodel.h"
#include "source/qmlmodel/setpointpositiondlgmodel.h"
#include "source/qmlmodel/sequencerdlgmodel.h"
#include "source/qmlmodel/firmwareupdatedlgmodel.h"
#include "source/qmlmodel/firmwareupdateexdlgmodel.h"
#include "source/qmlmodel/firmwareupdatevianetworkdlgmodel.h"
#include "source/qmlmodel/valvepowerfailstatusdlgmodel.h"
#include "source/qmlmodel/advancedtooltestdlgmodel.h"
#include "source/qmlmodel/advancedtoolbackupnrestoredlgmodel.h"
#include "source/qmlmodel/advencedtooldiskhoricalibdlgmodel.h"
#include "source/qmlmodel/graphanalyzedlgmodel.h"
#include "source/nchart/nchartview.h"
//#include "source/nchart/nvoltchartview.h"
//#include "source/nchart/nanalyzechartview.h"

int main(int argc, char *argv[])
{
    int resultExec = 0;

    //qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));


    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("qrc:/image/icon-novasen.png"));

#if defined(Q_OS_WIN)
    //QGuiApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
#else
    QGuiApplication::setOverrideCursor(Qt::BlankCursor);
#endif

    //QGuiApplication::styleHints()->setMousePressAndHoldInterval(200);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/ui/BaseWindow.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qmlRegisterUncreatableType<QmlEnumDef>("QmlEnumDef", 1, 0, "QmlEnumDef", "");
    qmlRegisterUncreatableType<ValveEnumDef>("ValveEnumDef", 1, 0, "ValveEnumDef", "");
    qmlRegisterUncreatableType<FirmwareUpdateUiStepDef>("FirmwareUpdateUiStepDef", 1, 0, "FirmwareUpdateUiStepDef", "");
    qmlRegisterUncreatableType<FirmwareUpdateViaNetworkUiStepDef>("FirmwareUpdateViaNetworkUiStepDef", 1, 0, "FirmwareUpdateViaNetworkUiStepDef", "");
    //sqmlRegisterUncreatableType<PressureCtrlLearnParamEnumDef>("PressureCtrlLearnParamEnumDef", 1, 0, "PressureCtrlLearnParamEnumDef", "");

    qRegisterMetaType<ValveRequestDto>();
    qRegisterMetaType<ValveResponseDto>();
    qRegisterMetaType<ValveResponseHWConfigDto>();
    qRegisterMetaType<ValveResponseFirmwareVersionDto>();
    qRegisterMetaType<ValveResponseValveIdDto>();
    qRegisterMetaType<ValveResponseSensorConfigDto>();
    qRegisterMetaType<ValveResponsePressureCtrlConfigDto>();
    qRegisterMetaType<ValveResponseSelControlModeDto>();
    qRegisterMetaType<ValveResponseGainFactorDto>();
    qRegisterMetaType<ValveResponsePGainDto>();
    qRegisterMetaType<ValveResponseIGainDto>();
    qRegisterMetaType<ValveResponseSensorDelayDto>();
    qRegisterMetaType<ValveResponseRampTimeDto>();
    qRegisterMetaType<ValveResponseRampModeDto>();
    qRegisterMetaType<ValveResponseCtrlDirDto>();
    qRegisterMetaType<ValveResponseValveSetupDto>();
    qRegisterMetaType<ValveResponseInterfaceConfigLogicDto>();
    qRegisterMetaType<ValveResponseInterfaceConfigEthCATDiDto>();
    qRegisterMetaType<ValveResponseInterfaceConfigEthCATDoDto>();
    qRegisterMetaType<ValveResponseInterfaceConfigEthCATDevIDDto>();
    qRegisterMetaType<ValveResponseInterfaceConfigEthCATPDODataTypeDto>();
    qRegisterMetaType<ValveResponseInterfaceConfigEthCATPDORangeDto>();
    qRegisterMetaType<ValveResponseInterfaceConfigDNetMacDto>();
    qRegisterMetaType<ValveResponseInterfaceConfigDNetBaudrateDto>();
    qRegisterMetaType<ValveResponseInterfaceConfigDNetDiDto>();
    qRegisterMetaType<ValveResponseInterfaceConfigDNetDoDto>();
    qRegisterMetaType<ValveResponseInterfaceConfigRS232Dto>();
    qRegisterMetaType<ValveResponseInterfaceConfigRS232RangeDto>();
    qRegisterMetaType<ValveResponseInterfaceConfigFieldbusNodeAddrDto>();
    qRegisterMetaType<ValveResponseInterfaceStatusRS232Dto>();
    qRegisterMetaType<ValveResponseLearnStatusDto>();
    qRegisterMetaType<ValveResponseLearnPressureLimitDto>();
    qRegisterMetaType<ValveResponseFatalErrStatusDto>();
    qRegisterMetaType<ValveResponseWarningsDto>();
    qRegisterMetaType<ValveResponseSensorOffsetDto>();
    qRegisterMetaType<ValveResponseControlCyclesDto>();
    qRegisterMetaType<ValveResponseIsolationCyclesDto>();
    qRegisterMetaType<ValveResponseSensorScaleDto>();
    qRegisterMetaType<ValveResponseSetPointDto>();
    qRegisterMetaType<ValveResponseDisplayConfigDto>();
    qRegisterMetaType<ValveResponseValveParamDto>();
    qRegisterMetaType<ValveResponseTotalControlCyclesDto>();
    qRegisterMetaType<ValveResponseTotalIsolationCyclesDto>();
    qRegisterMetaType<ValveResponsePFOPerformedCyclesDto>();
    qRegisterMetaType<ValveResponsePFOCurrentVoltageDto>();
    qRegisterMetaType<ValveResponseFatalErrPosDto>();
    qRegisterMetaType<ValveResponseLearnParamDto>();
    qRegisterMetaType<ValveResponseValveStatusDto>();
    qRegisterMetaType<ValveResponseInterfaceStatusLogicDto>();
    qRegisterMetaType<ValveResponseInterfaceStatusEtherCATDto>();
    qRegisterMetaType<NChartPointData>();

    qmlRegisterType<QmlCoreModel>("QmlCoreModel", 1, 0, "QmlCoreModel");
    qmlRegisterType<DebuggingModel>("DebuggingModel", 1, 0, "DebuggingModel");
    qmlRegisterType<SearchDeviceDlgModel>("SearchDeviceDlgModel", 1, 0, "SearchDeviceDlgModel");
    qmlRegisterType<ValveIdentificationExDlgModel>("ValveIdentificationExDlgModel", 1, 0, "ValveIdentificationExDlgModel");
    qmlRegisterType<ValveSetupDlgModel>("ValveSetupDlgModel", 1, 0, "ValveSetupDlgModel");
    qmlRegisterType<ChangeAccessDlgModel>("ChangeAccessDlgModel", 1, 0, "ChangeAccessDlgModel");
    qmlRegisterType<ValveParamExItemModel>("ValveParamExItemModel", 1, 0, "ValveParamExItemModel");
    qmlRegisterType<ValveParamExDlgModel>("ValveParamExDlgModel", 1, 0, "ValveParamExDlgModel");
    qmlRegisterType<ValveRecoveryDlgModel>("ValveRecoveryDlgModel", 1, 0, "ValveRecoveryDlgModel");
    qmlRegisterType<SensorSetupDlgModel>("SensorSetupDlgModel", 1, 0, "SensorSetupDlgModel");
    qmlRegisterType<SensorSetupExDlgModel>("SensorSetupExDlgModel", 1, 0, "SensorSetupExDlgModel");
    qmlRegisterType<SensorAnalysisDlgModel>("SensorAnalysisDlgModel", 1, 0, "SensorAnalysisDlgModel");
    qmlRegisterType<PressureCtrlSetupDlgModel>("PressureCtrlSetupDlgModel", 1, 0, "PressureCtrlSetupDlgModel");
    qmlRegisterType<PressureCtrlFloatSetupDlgModel>("PressureCtrlFloatSetupDlgModel", 1, 0, "PressureCtrlFloatSetupDlgModel");
    qmlRegisterType<PressureCtrlLearnParamDlgModel>("PressureCtrlLearnParamDlgModel", 1, 0, "PressureCtrlLearnParamDlgModel");
    qmlRegisterType<PressureCtrlLearnParamItemModel>("PressureCtrlLearnParamItemModel", 1, 0, "PressureCtrlLearnParamItemModel");
    qmlRegisterType<PressureCtrlLearnListItemModel>("PressureCtrlLearnListItemModel", 1, 0, "PressureCtrlLearnListItemModel");
    qmlRegisterType<PressureCtrlLearnListDlgModel>("PressureCtrlLearnListDlgModel", 1, 0, "PressureCtrlLearnListDlgModel");
    qmlRegisterType<NCPASettingsDlgModel>("NCPASettingsDlgModel", 1, 0, "NCPASettingsDlgModel");
    qmlRegisterType<InterfaceSetupDevNetDlgModel>("InterfaceSetupDevNetDlgModel", 1, 0, "InterfaceSetupDevNetDlgModel");
    qmlRegisterType<InterfaceSetupDevNetAssemblyItemModel>("InterfaceSetupDevNetAssemblyItemModel", 1, 0, "InterfaceSetupDevNetAssemblyItemModel");
    qmlRegisterType<InterfaceSetupLogicDlgModel>("InterfaceSetupLogicDlgModel", 1, 0, "InterfaceSetupLogicDlgModel");
    qmlRegisterType<InterfaceSetupEtherCATDlgModel>("InterfaceSetupEtherCATDlgModel", 1, 0, "InterfaceSetupEtherCATDlgModel");
    qmlRegisterType<InterfaceSetupEthCATItemModel>("InterfaceSetupEthCATItemModel", 1, 0, "InterfaceSetupEthCATItemModel");
    qmlRegisterType<InterfaceSetupRS232DlgModel>("InterfaceSetupRS232DlgModel", 1, 0, "InterfaceSetupRS232DlgModel");
    qmlRegisterType<InterfaceSetupEtherNETDlgModel>("InterfaceSetupEtherNETDlgModel", 1, 0, "InterfaceSetupEtherNETDlgModel");
    qmlRegisterType<InterfaceSetupProfibusDlgModel>("InterfaceSetupProfibusDlgModel", 1, 0, "InterfaceSetupProfibusDlgModel");
    qmlRegisterType<InterfaceSetupProfibusItemModel>("InterfaceSetupProfibusItemModel", 1, 0, "InterfaceSetupProfibusItemModel");
    qmlRegisterType<InterfaceStatusLogicDlgModel>("InterfaceStatusLogicDlgModel", 1, 0, "InterfaceStatusLogicDlgModel");
    qmlRegisterType<InterfaceStatusEtherCATDlgModel>("InterfaceStatusEtherCATDlgModel", 1, 0, "InterfaceStatusEtherCATDlgModel");
    qmlRegisterType<InterfaceStatusDNetDlgModel>("InterfaceStatusDNetDlgModel", 1, 0, "InterfaceStatusDNetDlgModel");
    qmlRegisterType<InterfaceStatusRS232DlgModel>("InterfaceStatusRS232DlgModel", 1, 0, "InterfaceStatusRS232DlgModel");
    qmlRegisterType<InterfaceStatusProfibusDlgModel>("InterfaceStatusProfibusDlgModel", 1, 0, "InterfaceStatusProfibusDlgModel");
    qmlRegisterType<InterfaceTraceDlgModel>("InterfaceTraceDlgModel", 1, 0, "InterfaceTraceDlgModel");
    qmlRegisterType<ValveCycleCounterDlgModel>("ValveCycleCounterDlgModel", 1, 0, "ValveCycleCounterDlgModel");
    qmlRegisterType<ValveCariblationDlgModel>("ValveCariblationDlgModel", 1, 0, "ValveCariblationDlgModel");
    qmlRegisterType<ValveCalibrationExDlgModel>("ValveCalibrationExDlgModel", 1, 0, "ValveCalibrationExDlgModel");
    qmlRegisterType<ControlZeroDlgModel>("ControlZeroDlgModel", 1, 0, "ControlZeroDlgModel");
    qmlRegisterType<ControlLearnDlgModel>("ControlLearnDlgModel", 1, 0, "ControlLearnDlgModel");
    qmlRegisterType<FatalErrorDlgModel>("FatalErrorDlgModel", 1, 0, "FatalErrorDlgModel");
    qmlRegisterType<NChartCanvasModel>("NChartCanvasModel", 1, 0, "NChartCanvasModel");
    qmlRegisterType<NChartView>("NChartView", 1, 0, "NChartView");
    //qmlRegisterType<NVoltChartView>("NVoltChartView", 1, 0, "NVoltChartView");
    //qmlRegisterType<NAnalyzeChartView>("NAnalyzeChartView", 1, 0, "NAnalyzeChartView");
    qmlRegisterType<SetPointPositionDlgModel>("SetPointPositionDlgModel", 1, 0, "SetPointPositionDlgModel");
    qmlRegisterType<SequencerDlgModel>("SequencerDlgModel", 1, 0, "SequencerDlgModel");
    qmlRegisterType<SeqTestItemModel>("SeqTestItemModel", 1, 0, "SeqTestItemModel");
    qmlRegisterType<FirmwareUpdateDlgModel>("FirmwareUpdateDlgModel", 1, 0, "FirmwareUpdateDlgModel");
    qmlRegisterType<FirmwareUpdateExDlgModel>("FirmwareUpdateExDlgModel", 1, 0, "FirmwareUpdateExDlgModel");
    qmlRegisterType<FirmwareUpdateViaNetworkDlgModel>("FirmwareUpdateViaNetworkDlgModel", 1, 0, "FirmwareUpdateViaNetworkDlgModel");
    qmlRegisterType<ValvePowerFailStatusDlgModel>("ValvePowerFailStatusDlgModel", 1, 0, "ValvePowerFailStatusDlgModel");
    qmlRegisterType<AdvancedToolTestDlgModel>("AdvancedToolTestDlgModel", 1, 0, "AdvancedToolTestDlgModel");
    qmlRegisterType<AdvancedToolBackupNRestoreDlgModel>("AdvancedToolBackupNRestoreDlgModel", 1, 0, "AdvancedToolBackupNRestoreDlgModel");
    qmlRegisterType<AdvancedToolDiskHoriCalibDlgModel>("AdvancedToolDiskHoriCalibDlgModel", 1, 0, "AdvancedToolDiskHoriCalibDlgModel");
    qmlRegisterType<GraphAnalyzeDlgModel>("GraphAnalyzeDlgModel", 1, 0, "GraphAnalyzeDlgModel");

    //qmlRegisterType<LineChartData>("LineChartData", 1, 0, "LineChartData");

    qmlRegisterSingletonType(QUrl("qrc:/uiengine/FontManager.qml"), "FontManager", 1, 0, "FontManager");
    qmlRegisterSingletonType(QUrl("qrc:/uiengine/UnitUtil.qml"), "UnitUtil", 1, 0, "UnitUtil");
    qmlRegisterSingletonType(QUrl("qrc:/uiengine/MathUtil.qml"), "MathUtil", 1, 0, "MathUtil");
    qmlRegisterSingletonType(QUrl("qrc:/uiengine/StrUtil.qml"), "StrUtil", 1, 0, "StrUtil");
    qmlRegisterSingletonType(QUrl("qrc:/uiengine/GUISetting.qml"), "GUISetting", 1, 0, "GUISetting");
    qmlRegisterSingletonType(QUrl("qrc:/ui/GlobalUiValue.qml"), "GlobalUiValue", 1, 0, "GlobalUiValue");

    NSDebug::startService();

    qInstallMessageHandler(NSDebug::debugMessageHandler);

    engine.load(url);
    resultExec = app.exec();

    qInstallMessageHandler(nullptr);
    NSDebug::stopService();

    return resultExec;
}
