@echo off
setlocal enabledelayedexpansion

:: Optional: predefine the executable name here
:: Example: set exeName=MyProgram
:: Leave blank to prompt the user
set "exeName=main"

:: If no exe name is preset, ask the user
if "%exeName%"=="" (
    set /p "exeName=Enter name for the output executable (without .exe): "
)

:: Initialize source file list
set "sources="

:: Recursively collect all .cpp files from current folder and subfolders
for /r %%f in (*.cpp) do (
    set "sources=!sources! "%%f""
)

:: Show the command before running it
echo.
echo Running: g++ !sources! -o "!exeName!.exe"
echo.

:: Run the command
g++ !sources! -o "!exeName!.exe" -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lwinmm

:: Check for errors
if errorlevel 1 (
    echo.
    echo Compilation failed.
) else (
    echo.
    echo Compilation successful. Running "!exeName!.exe"...
    echo.
    echo ======================================== OUTPUT RESULT ========================================
    echo.
    "!exeName!.exe"
)

pause
