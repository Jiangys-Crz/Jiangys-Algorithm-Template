@echo off
setlocal EnableExtensions DisableDelayedExpansion
if /i not "%~x1"==".cpp" goto usage
if "%~2"=="" goto usage
if not "%~3"=="" goto usage

set "work=%TEMP%\xcpc-%RANDOM%-%RANDOM%"
md "%work%" || exit /b 2
set "result=2"
g++ -x c++ -std=c++23 -O2 -DLOCAL "%~f1" -o "%work%\sol.exe" || goto cleanup
"%work%\sol.exe" < "%~2.in" > "%work%\actual" || goto cleanup

echo === Expected output ===
type "%~2.out" || goto cleanup
echo. & echo === Actual output ===
type "%work%\actual" || goto cleanup
echo.
fc.exe /L /T /LB100000 "%~2.out" "%work%\actual" >nul
set "result=%errorlevel%"
if "%result%"=="0" echo Accepted
if "%result%"=="1" echo Wrong Answer

:cleanup
rd /s /q "%work%"
exit /b %result%
:usage
echo Usage: %~nx0 a.cpp sample-number 1>&2
exit /b 2
