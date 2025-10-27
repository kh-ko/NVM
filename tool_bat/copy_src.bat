@echo off
REM Use the local environment from the calling script (make_release.bat)
REM setlocal enabledelayedexpansion

REM =================================================================
REM                          CONFIGURATION
REM =================================================================
REM Get the release version from make_release.bat
REM If VERSION is not set, use default value
if not defined VERSION (
    set "VERSION=1.9.97"
)


REM =================================================================
REM                        SCRIPT LOGIC START
REM =================================================================
echo.
echo =================== [ Start Release Script ] ===================
echo.

REM 1. Get the current date in YYYYMMDD format.
for /f "tokens=2 delims==" %%a in ('wmic os get localdatetime /value') do set "dt=%%a"
set "TODAY=%dt:~0,8%"

echo   - Release Version: %VERSION%
echo   - Release Date: %TODAY%

REM 2. Set source and destination paths.
REM This script (make_release.bat) is assumed to be in the "tool_bat" folder.
REM Source Path: ..\ (e.g., C:\Source\work\NVM)
REM Destination Base Path: ..\..\.. (e.g., C:\Source)

set "SOURCE_PATH=.."
set "DEST_BASE_PATH=..\..\.."
set "RELEASE_FOLDER_NAME=%TODAY%-v%VERSION%"
set "DEST_PATH=%DEST_BASE_PATH%\%RELEASE_FOLDER_NAME%\NVM"

echo   - Source Path (Absolute): %CD%\%SOURCE_PATH%
echo   - Destination Path (Absolute): %CD%\%DEST_PATH%
echo.

REM 3. Create the destination folder.
if exist "%DEST_PATH%" (
    echo   [INFO] Destination folder already exists.
) else (
    echo   [INFO] Creating destination folder...
    mkdir "%DEST_PATH%"
    if errorlevel 1 (
        echo   [ERROR] Failed to create destination folder. Exiting script.
        goto :eof
    )
    echo   [SUCCESS] Destination folder created.
)
echo.

REM 4. Copy top-level files from the source folder (subfolders are not copied).
echo   [TASK] Copying top-level files...
xcopy "%SOURCE_PATH%\*.*" "%DEST_PATH%\" /I /Y /Q >nul
echo   [DONE] Top-level file copy complete.
echo.

REM 5. Recursively copy all subfolders, excluding those starting with 'build'.
echo   [TASK] Copying subfolders (excluding folders starting with 'build')...
echo   ==================================================
for /d %%i in ("%SOURCE_PATH%\*") do (
    set "FOLDER_NAME=%%~nxi"
    
    REM Check if the folder name starts with "build" (case-insensitive) by checking the first 5 characters.
    set "prefix=!FOLDER_NAME:~0,5!"

    if /I "!prefix!"=="build" (
        echo     -> Skipping folder: "!FOLDER_NAME!"
    ) else (
        echo     -> Copying folder: "!FOLDER_NAME!"
        xcopy "%%i" "%DEST_PATH%\!FOLDER_NAME!\" /E /I /Y /Q >nul
    )
)
echo   ==================================================

echo.
echo =================== [ All Tasks Completed ] ===================
echo.
echo The release package has been created at the following path:
echo %CD%\%DEST_PATH%
echo.

REM endlocal - not needed when called from make_release.bat

