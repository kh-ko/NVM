#include "ftdhelper.h"
#include "ftd2xx.h"
#include <QThread>
FTDHelper::FTDHelper()
{

}

bool FTDHelper::readyPort(long comport, QString errMsg)
{
    DWORD numDevs = 0;
    FT_STATUS ftStatus;
    FT_HANDLE ftHandle;

    // 1. 장치 개수 확인
    ftStatus = FT_CreateDeviceInfoList(&numDevs);
    if (ftStatus != FT_OK || numDevs == 0) {
        errMsg = "can not found device";
        return false;
    }

    // 2. 장치 정보 목록 확보
    FT_DEVICE_LIST_INFO_NODE *devInfo = new FT_DEVICE_LIST_INFO_NODE[numDevs];
    ftStatus = FT_GetDeviceInfoList(devInfo, &numDevs);

    if (ftStatus != FT_OK) {
        errMsg = "can not search device list";
        return false;
    }

    // 3. COM 포트 이름으로 검색 (예: "COM4")
    bool found = false;

    for (DWORD i = 0; i < numDevs; ++i) {
        FT_HANDLE tempHandle = nullptr;
        if (FT_Open(i, &tempHandle) != FT_OK) continue;

        long comPortNumber = -1;
        if (FT_GetComPortNumber(tempHandle, &comPortNumber) == FT_OK) {
            if (comPortNumber == comport) {
                // COM4 찾음
                found = true;
                ftHandle = tempHandle;
                break;
            }
        }

        FT_Close(tempHandle); // 아니면 닫기
    }

    if(found == false)
    {
        errMsg = "can not found target comport";
        return false;
    }

    ftStatus = FT_SetBitMode(ftHandle, 0x00, FT_BITMODE_RESET);

    if (ftStatus != FT_OK) {
        errMsg = "can not C BITBANG reset";
        return false;
    }

    QThread::msleep(1000);
    // c2: reset pin - 0b0100, c3 : bootmode pin - 0b1000
    // senario :
    //   c3 __|￣￣￣￣￣￣￣￣￣
    //   c2 ____|￣￣|__________
    ftStatus = FT_SetBitMode(ftHandle, 0xF0, FT_BITMODE_CBUS_BITBANG);

    if (ftStatus != FT_OK) {
        errMsg = "can not C3, C2 LOW";
        return false;
    }

    QThread::msleep(1000);

    ftStatus = FT_SetBitMode(ftHandle, 0xF8, FT_BITMODE_CBUS_BITBANG);

    if (ftStatus != FT_OK) {
        errMsg = "can not C3 HIGH";
        return false;
    }

    QThread::msleep(1000);

    ftStatus = FT_SetBitMode(ftHandle, 0xFC, FT_BITMODE_CBUS_BITBANG);

    if (ftStatus != FT_OK) {
        errMsg = "can not C3, C2 HIGH";
        return false;
    }

    QThread::msleep(1000);

    ftStatus = FT_SetBitMode(ftHandle, 0xF8, FT_BITMODE_CBUS_BITBANG);

    if (ftStatus != FT_OK) {
        errMsg = "can not remain C3 HIGH";
        return false;
    }

    QThread::msleep(1000);

    FT_Close(ftHandle); // 아니면 닫기
    return true;
}

bool FTDHelper::finishPort(long comport, QString errMsg)
{
    DWORD numDevs = 0;
    FT_STATUS ftStatus;
    FT_HANDLE ftHandle;

    // 1. 장치 개수 확인
    ftStatus = FT_CreateDeviceInfoList(&numDevs);
    if (ftStatus != FT_OK || numDevs == 0) {
        errMsg = "can not found device";
        return false;
    }

    // 2. 장치 정보 목록 확보
    FT_DEVICE_LIST_INFO_NODE *devInfo = new FT_DEVICE_LIST_INFO_NODE[numDevs];
    ftStatus = FT_GetDeviceInfoList(devInfo, &numDevs);

    if (ftStatus != FT_OK) {
        errMsg = "can not search device list";
        return false;
    }

    // 3. COM 포트 이름으로 검색 (예: "COM4")
    bool found = false;

    for (DWORD i = 0; i < numDevs; ++i) {
        FT_HANDLE tempHandle = nullptr;
        if (FT_Open(i, &tempHandle) != FT_OK) continue;

        long comPortNumber = -1;
        if (FT_GetComPortNumber(tempHandle, &comPortNumber) == FT_OK) {
            if (comPortNumber == comport) {
                // COM4 찾음
                found = true;
                ftHandle = tempHandle;
                break;
            }
        }

        FT_Close(tempHandle); // 아니면 닫기
    }

    if(found == false)
    {
        errMsg = "can not found target comport";
        return false;
    }

    ftStatus = FT_SetBitMode(ftHandle, 0x00, FT_BITMODE_RESET);

    if (ftStatus != FT_OK) {
        errMsg = "can not C BITBANG reset";
        return false;
    }

    QThread::msleep(1000);
    // c2: reset pin - 0b0100, c3 : bootmode pin - 0b1000
    // senario :
    //   c3 ___________________
    //   c2 ____|￣￣|__________
    ftStatus = FT_SetBitMode(ftHandle, 0xF0, FT_BITMODE_CBUS_BITBANG);

    if (ftStatus != FT_OK) {
        errMsg = "can not C3, C2 LOW";
        return false;
    }

    QThread::msleep(1000);

    ftStatus = FT_SetBitMode(ftHandle, 0xF4, FT_BITMODE_CBUS_BITBANG);

    if (ftStatus != FT_OK) {
        errMsg = "can not C3, C2 HIGH";
        return false;
    }

    QThread::msleep(1000);

    ftStatus = FT_SetBitMode(ftHandle, 0xF0, FT_BITMODE_CBUS_BITBANG);

    if (ftStatus != FT_OK) {
        errMsg = "can not remain C3 HIGH";
        return false;
    }

    QThread::msleep(1000);

    FT_Close(ftHandle); // 아니면 닫기
    return true;
}
