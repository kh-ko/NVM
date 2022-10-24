QT += quick widgets serialport printsupport

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        source/logger/nsdebug.cpp \
        source/main.cpp \
        source/nchart/nchartcontrol.cpp \
        source/util/etcutil.cpp

RESOURCES += qml/qml.qrc

RC_FILE = NVM_resource.rc

TRANSLATIONS += Lang_ko_KR.ts
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
target.path = /home/pi/apps/$${TARGET}
INSTALLS += target

HEADERS += \
    source/logger/nsdebug.h \
    source/nchart/nchartcontrol.h \
    source/nchart/nchartpointbuffer.h \
    source/nchart/nchartview.h \
    source/qmlmodel/advancedtooltestdlgmodel.h \
    source/qmlmodel/changeaccessdlgmodel.h \
    source/qmlmodel/control/nchartcanvasmodel.h \
    source/qmlmodel/controllearndlgmodel.h \
    source/qmlmodel/controlzerodlgmodel.h \
    source/qmlmodel/def/qmlenumdef.h \
    source/qmlmodel/fatalerrordlgmodel.h \
    source/qmlmodel/firmwareupdatedlgmodel.h \
    source/qmlmodel/graphanalyzedlgmodel.h \
    source/qmlmodel/interfacesetupdevnetassemblyitemmodel.h \
    source/qmlmodel/interfacesetupdevnetdlgmodel.h \
    source/qmlmodel/interfacesetupethercatdlgmodel.h \
    source/qmlmodel/interfacesetuplogicdlgmodel.h \
    source/qmlmodel/interfacesetuprs232dlgmodel.h \
    source/qmlmodel/interfacestatusdnetdlgmodel.h \
    source/qmlmodel/interfacestatusethercatdlgmodel.h \
    source/qmlmodel/interfacestatuslogicdlgmodel.h \
    source/qmlmodel/interfacestatusrs232dlgmodel.h \
    source/qmlmodel/ncpasettingsdlgmodel.h \
    source/qmlmodel/panelbaratrongraph.h \
    source/qmlmodel/pressurectrlfloatsetupdlgmodel.h \
    source/qmlmodel/pressurectrllearnparamdlgmodel.h \
    source/qmlmodel/pressurectrlsetupdlgmodel.h \
    source/qmlmodel/qmlcoremodel.h \
    source/qmlmodel/searchdevicedlgmodel.h \
    source/qmlmodel/sensoranalysisdlgmodel.h \
    source/qmlmodel/sensorsetupdlgmodel.h \
    source/qmlmodel/sensorsetupexdlgmodel.h \
    source/qmlmodel/sequencerdlgmodel.h \
    source/qmlmodel/setpointpositiondlgmodel.h \
    source/qmlmodel/valvecaribrationdlgmodel.h \
    source/qmlmodel/valvecyclecounterdlgmodel.h \
    source/qmlmodel/valveidentificationexdlgmodel.h \
    source/qmlmodel/valveparamexdlgmodel.h \
    source/qmlmodel/valvepowerfailstatusdlgmodel.h \
    source/qmlmodel/valverecoverydlgmodel.h \
    source/qmlmodel/valvesetupdlgmodel.h \
    source/service/config/configsprovider.h \
    source/service/coreservice.h \
    source/service/def/builddef.h \
    source/service/def/datetimeform.h \
    source/service/def/filedef.h \
    source/service/localsetting/localsettingsprovider.h \
    source/service/util/byteswap.h \
    source/service/util/exceptionutil.h \
    source/service/util/filewriterex.h \
    source/service/util/mathutil.h \
    source/service/util/unitutil.h \
    source/service/valve/device/ivalve.h \
    source/service/valve/device/serialvalve.h \
    source/service/valve/valveayncworker.h \
    source/service/valve/valveconnection.h \
    source/service/valve/valvefirmwareupgradeworker.h \
    source/service/valve/valvesprovider.h \
    source/service/valve/valvesproviderdto.h \
    source/service/valve/valvesproviderdtoex.h \
    source/util/etcutil.h

DISTFILES +=
