@echo off
setlocal EnableExtensions DisableDelayedExpansion
if "%~1"=="" goto usage
if "%~2"=="" goto usage
if not "%~3"=="" goto usage
for /f "delims=0123456789" %%i in ("%~2") do goto usage
if /i not "%~x1"==".cpp" (
    echo Use a .cpp source file. 1>&2
    exit /b 2
)
set "src=%~f1"
set "input=%~2.in"
set "answer=%~2.out"
if not exist "%answer%" set "answer=%~2.ans"
for %%f in ("%src%" "%input%" "%answer%") do (
    if not exist "%%~f" (
        echo Missing file: "%%~f" 1>&2
        exit /b 2
    )
)
set "work=%TEMP%\xcpc-run-%RANDOM%-%RANDOM%"
md "%work%" || exit /b 2
set "result=2"

if not defined CXXSTD set "CXXSTD=c++23"
g++ -x c++ -std="%CXXSTD%" -O2 -Wall -Wextra -Wshadow -DLOCAL "%src%" -o "%work%\sol.exe"
if errorlevel 1 goto cleanup
"%work%\sol.exe" < "%input%" > "%work%\actual.txt"
set "runStatus=%errorlevel%"

echo === Expected output ===
type "%answer%"
echo.
echo === Actual output ===
type "%work%\actual.txt"
echo.
echo === Differences ===
fc.exe /L /N /T /LB100000 "%answer%" "%work%\actual.txt" > "%work%\diff.txt"
set "result=%errorlevel%"
if "%result%"=="0" echo No differences.
if "%result%"=="1" (
    powershell.exe -NoProfile -Command "Get-Content -LiteralPath (Join-Path $env:work 'diff.txt') | ForEach-Object { Write-Host $_ -ForegroundColor Red }"
    if errorlevel 1 type "%work%\diff.txt"
)
if not "%runStatus%"=="0" (
    echo Runtime error ^(exit %runStatus%^). 1>&2
    set "result=2"
    goto cleanup
)
if "%result%"=="0" echo Accepted
if "%result%"=="1" echo Wrong Answer
if "%result%"=="2" echo Comparison failed. 1>&2

:cleanup
rd /s /q "%work%"
exit /b %result%

:usage
echo Usage: %~nx0 a.cpp sample-number 1>&2
exit /b 2
