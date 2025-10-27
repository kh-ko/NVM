@echo off
echo Running NVM.exe from novasen configuration...
cd ..\build_cursor\release_nova

echo Setting up Qt environment...
set PATH=C:\Qt\5.15.2\mingw81_32\bin;%PATH%

echo Running NVM.exe...
cd release
NVM.exe

echo Program finished.
cd ..\..\tool_bat
pause
