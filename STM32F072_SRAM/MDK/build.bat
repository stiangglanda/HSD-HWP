@echo off
setlocal
rem Usage: build.bat ["C:\Keil_v5\UV4\UV4.exe"]
set "SRAM_UV4=%~1"
if not defined SRAM_UV4 set "SRAM_UV4=C:\Keil_v5\UV4\UV4.exe"
if not exist "%SRAM_UV4%" (
    echo UV4.exe not found. Pass its full path as the first argument.
    exit /b 2
)
pushd "%~dp0"
"%SRAM_UV4%" -r "STM32F072_SRAM.uvprojx" -t "SRAM_Debug_AC6" -o "build.log"
set "SRAM_BUILD_RESULT=%ERRORLEVEL%"
if exist "build.log" type "build.log"
popd
exit /b %SRAM_BUILD_RESULT%
