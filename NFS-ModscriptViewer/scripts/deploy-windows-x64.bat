@echo off
setlocal

echo Loading Qt environment...
call "C:\Qt\6.11.1\msvc2022_64\bin\qtenv2.bat"

cd /d %~dp0..

set BUILD_DIR=build\release-windows-x64
set DEPLOY_DIR=deploy\release-windows-x64
set EXE=%BUILD_DIR%\NFS-ModscriptViewer.exe

echo Cleaning deploy folder...
if exist %DEPLOY_DIR% rmdir /S /Q %DEPLOY_DIR%
mkdir %DEPLOY_DIR%

echo Copying .exe to the folder...
copy "%EXE%" "%DEPLOY_DIR%\NFS-ModscriptViewer.exe" /Y

echo Running windeployqt...
windeployqt "%EXE%" --dir "%DEPLOY_DIR%"

echo Done!
pause