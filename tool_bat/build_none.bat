@echo off
echo Building for none configuration...

REM ..(NVM)/
echo.
echo Modifying company setting to COMPANY_NONE...
if exist "..\source\service\localsetting\localsettingsprovider.h" (
    powershell -Command "(Get-Content '..\source\service\localsetting\localsettingsprovider.h') -replace '^(\s*int\s+mCompany\s*=\s*\(int\)ValveEnumDef::)[^;]+;', '    int     mCompany               = (int)ValveEnumDef::COMPANY_NONE;' | Set-Content '..\source\service\localsetting\localsettingsprovider.h'"
    echo Company setting updated to COMPANY_NONE successfully.
) else (
    echo Warning: localsettingsprovider.h file not found!
)

echo.
echo Updating resource file...
if exist "..\NVM_resource.rc" (
    del "..\NVM_resource.rc"
    echo NVM_resource.rc file deleted.
) else (
    echo NVM_resource.rc file not found, skipping deletion.
)

if exist "..\NVM_resource_no_icon.rc" (
    copy "..\NVM_resource_no_icon.rc" "..\NVM_resource.rc" 
    echo NVM_resource_no_icon.rc copied to NVM_resource.rc successfully.
) else (
    echo Warning: NVM_resource_no_icon.rc file not found!
)

cd ..\build_cursor\release_none

echo.
echo Cleaning previous build files...
if exist release rmdir /s /q release
if exist debug rmdir /s /q debug
del /Q * 2>nul
echo Clean completed.
echo.
echo Setting up build environment...

REM MinGW 환경 설정
set MINGW_COMPILER_PATH=C:\Qt\5.15.2\Tools\mingw810_32\bin
set MINGW_QT_PATH=C:\Qt\5.15.2\5.15.2\mingw81_32\bin
set PATH=%MINGW_COMPILER_PATH%;%MINGW_QT_PATH%;%PATH%

REM 환경변수로 경로 설정 현재 경로 NVM/build_cursor/release_none/
set QT_PATH="C:\Qt\5.15.2\5.15.2\mingw81_32\bin\qmake.exe"
set PRO_PATH="..\..\NVM.pro"

call %QT_PATH% %PRO_PATH%
if %ERRORLEVEL% EQU 0 (
    echo qmake completed successfully
    echo Starting build in Release mode...
    mingw32-make release
    if %ERRORLEVEL% EQU 0 (
        echo Build completed successfully!
    ) else (
        echo Build failed with error code %ERRORLEVEL%
    )
) else (
    echo qmake failed with error code %ERRORLEVEL%
)

echo Copying static resources...
if exist "..\..\static_resource" (
    echo Copying static_resource files to none folder...
    xcopy "..\..\static_resource\*" ".\release" /E /I /Y /Q
    echo Static resources copied successfully.
) else (
    echo Warning: static_resource folder not found!
)

cd ..\..\tool_bat
