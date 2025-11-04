@echo off
setlocal enabledelayedexpansion

echo ========================================
echo NVM Version Release Builder
echo ========================================
echo.

REM 1. Get version name from user
set /p VERSION="Input version name >> "
if "%VERSION%"=="" (
    echo No version name input.
    pause
    exit /b 1
)

echo.
echo Input version: %VERSION%
echo.

echo Creating folders...
REM make_version 폴더가 이미 있으면 모든 내용 삭제 후 새로 생성
if exist "..\..\Binary\build_cursor\make_version" (
    echo make_version already exists.
    rmdir /s /q "..\..\Binary\build_cursor\make_version"
    echo make_version folder deleted.
)
mkdir "..\..\Binary\build_cursor\make_version"
echo make_version folder created.

REM 각 회사별 폴더 생성
mkdir "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-none" 2>nul
mkdir "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-apsys" 2>nul
mkdir "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-nova" 2>nul
mkdir "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-soao" 2>nul

echo make_version folder created.
echo   - NVM(%VERSION%)-none
echo   - NVM(%VERSION%)-apsys
echo   - NVM(%VERSION%)-nova
echo   - NVM(%VERSION%)-soao

REM 3. Modify mBuildVersion in localsettingsprovider.h
echo.
echo Modifying localsettingsprovider.h...
if exist "..\source\service\localsetting\localsettingsprovider.h" (
    REM --- This is the modified part ---
    REM Create and execute a temporary PowerShell script to avoid cmd.exe parsing issues.
    (
        echo $path = '..\source\service\localsetting\localsettingsprovider.h'
        echo $versionString = '%VERSION%'
        echo $fileContent = Get-Content -Path $path -Encoding UTF8 -Raw
        echo $regex = 'QString mBuildVersion\s*=\s*\"[^\"]+\"'
        echo $replacement = 'QString mBuildVersion          = "' + $versionString + '"'
        echo $newContent = $fileContent -replace $regex, $replacement
        echo Set-Content -Path $path -Encoding UTF8 -Value $newContent
    ) > temp_modifier.ps1

    powershell -ExecutionPolicy Bypass -File temp_modifier.ps1
    del temp_modifier.ps1

    echo mBuildVersion is now %VERSION% 
) else (
    echo Warning: localsettingsprovider.h not found!
)

REM 4. Replace content of static_resource\config\ui\version.txt
echo.
echo Modifying version.txt...
if exist "..\static_resource\config\ui\version.txt" (
    echo %VERSION% > "..\static_resource\config\ui\version.txt"
    echo version.txt is now %VERSION%
) else (
    echo Warning: version.txt not found!
)

REM 5. Execute build_xxx.bat files sequentially
echo.
echo ========================================
echo Starting build...
echo ========================================

echo.
echo 1. Running build_apsystem.bat...
call build_apsys.bat
if %ERRORLEVEL% NEQ 0 (
    echo build_apsys.bat failed!
    pause
    exit /b 1
)

echo.
echo 2. Running build_none.bat...
call build_none.bat
if %ERRORLEVEL% NEQ 0 (
    echo build_none.bat failed!
    pause
    exit /b 1
)

echo.
echo 3. Running build_nova.bat...
call build_nova.bat
if %ERRORLEVEL% NEQ 0 (
    echo build_nova.bat failed!
    pause
    exit /b 1
)

echo.
echo 4. Running build_soao.bat...
call build_soao.bat
if %ERRORLEVEL% NEQ 0 (
    echo build_soao.bat failed!
    pause
    exit /b 1
)

echo.
echo ========================================
echo All builds have been completed!
echo ========================================

REM 6. Copy NVM.exe from each release folder to the version folder
echo.
echo Configuring deployment folder...

REM apsystem
if exist "..\..\Binary\build_cursor\release_apsys\release\NVM.exe" (
    copy "..\..\Binary\build_cursor\release_apsys\release\NVM.exe" "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-apsys\"
    echo release_apsys\release\NVM.exe copied to "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-apsys"
    
    REM Qt 배포 파일 생성
    echo Creating Qt deployment package for apsystem...
    "C:\Qt\5.15.2\mingw81_32\bin\windeployqt.exe" "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-apsys\NVM.exe" --qmldir "..\qml"
    echo Qt deployment package created for apsystem.
    
    REM static_resource 복사
    xcopy "..\static_resource\*" "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-apsys\" /E /I /Y /Q
    echo Static resources copied successfully.
) else (
    echo Warning: release_apsys\release\NVM.exe not found!
)

REM none
if exist "..\..\Binary\build_cursor\release_none\release\NVM.exe" (
    copy "..\..\Binary\build_cursor\release_none\release\NVM.exe" "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-none\"
    echo release_none\release\NVM.exe copied to "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-none"
    
    REM Qt 배포 파일 생성
    echo Creating Qt deployment package for none...
    "C:\Qt\5.15.2\mingw81_32\bin\windeployqt.exe" "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-none\NVM.exe" --qmldir "..\qml"
    echo Qt deployment package created for none.
    
    REM static_resource 복사
    xcopy "..\static_resource\*" "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-none\" /E /I /Y /Q
    echo Static resources copied successfully.
) else (
    echo Warning: release_none\release\NVM.exe not found!
)

REM novasen
if exist "..\..\Binary\build_cursor\release_nova\release\NVM.exe" (
    copy "..\..\Binary\build_cursor\release_nova\release\NVM.exe" "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-nova\"
    echo release_nova\release\NVM.exe copied to "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-nova"
    
    REM Qt 배포 파일 생성
    echo Creating Qt deployment package for nova...
    "C:\Qt\5.15.2\mingw81_32\bin\windeployqt.exe" "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-nova\NVM.exe" --qmldir "..\qml"
    echo Qt deployment package created for nova.
    
    REM static_resource 복사
    xcopy "..\static_resource\*" "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-nova\" /E /I /Y /Q
    echo Static resources copied successfully.
) else (
    echo Warning: release_nova\release\NVM.exe not found!
)

REM soao
if exist "..\..\Binary\build_cursor\release_soao\release\NVM.exe" (
    copy "..\..\Binary\build_cursor\release_soao\release\NVM.exe" "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-soao\"
    echo release_soao\release\NVM.exe copied to "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-soao"
    
    REM Qt 배포 파일 생성
    echo Creating Qt deployment package for soao...
    "C:\Qt\5.15.2\mingw81_32\bin\windeployqt.exe" "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-soao\NVM.exe" --qmldir "..\qml"
    echo Qt deployment package created for soao.
    
    REM static_resource 복사
    xcopy "..\static_resource\*" "..\..\Binary\build_cursor\make_version\NVM(%VERSION%)-soao\" /E /I /Y /Q
    echo Static resources copied successfully.
) else (
    echo Warning: release_soao\release\NVM.exe not found!
)

echo.
echo ========================================
echo Version %VERSION% deployment package created successfully!
echo ========================================
echo.
echo Created folder structure:
dir "..\..\Binary\build_cursor\make_version" /b
echo.
echo Task completed!

call copy_src.bat

endlocal

pause

