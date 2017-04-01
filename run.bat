@echo off
cls
setlocal enabledelayedexpansion

::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


:: TALON ROOT DIRECTORY
set talonDir=%~dp0

:: TALON MAKEFILE DIRECTORIES
set makefilePaths[0]=%talonDir%lib\linkedListLibrary\lib\threadingProcessingLibrary\src
set makefilePaths[1]=%talonDir%lib\linkedListLibrary\src
set makefilePaths[2]=%talonDir%lib\threadingProcessingLibrary\src
set makefilePaths[3]=%talonDir%lib\runtimeLinkingLibrary\src
set makefilePaths[4]=%talonDir%modules\coreApi\src
set makefilePaths[5]=%talonDir%modules\coreCli\src

:: SIZE OF ARRAY DEFINED ABOVE
set makefilePathsSize=5

::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

cd %talonDir%

echo [*] Delete bin directory including its contents
rmdir /S /Q bin
echo [*] Delete obj directory including its contents
rmdir /S /Q obj

echo [*] Creating directory bin
mkdir bin
echo [*] Creating directory obj
mkdir obj

echo.
echo.

for /L %%a in (0,1,%makefilePathsSize%) do (
    echo [*] Navigating to !makefilePaths[%%a]!

    cd !makefilePaths[%%a]!

    echo [*] Delete bin directory including its contents
    rmdir /S /Q bin
    echo [*] Delete obj directory including its contents
    rmdir /S /Q obj

    echo [*] Creating directory bin
    mkdir bin
    echo [*] Creating directory obj
    mkdir obj

    echo [*] Starting build process...
    echo ============================================================
    mingw32-make.exe
    echo ============================================================
    echo [*] Build process has ended
    echo.
    echo.
)

cd %talonDir%

mingw32-make.exe

set talonBin=%talonDir%bin\talon.bin

echo.
echo.
set /P c=Would you like to run %talonBin%? [y/n]:

if "%c%" == "y" (
    echo [*] Starting Talon
    start %talonBin%
)

echo [*] Script has ended.
