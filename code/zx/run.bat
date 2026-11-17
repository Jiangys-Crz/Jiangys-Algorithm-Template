@echo off
setlocal EnableExtensions DisableDelayedExpansion
if /i not "%~x1"==".cpp" goto usage
if "%~2"=="" goto usage
if not "%~3"=="" goto usage
for /f "eol=| delims=0123456789" %%i in ("%~2") do goto usage

set "answer=%~2.out"
if not exist "%answer%" set "answer=%~2.ans"
for %%f in ("%~f1" "%~2.in" "%answer%") do if not exist "%%~f" (
    echo Missing file: "%%~f" 1>&2
    exit /b 2
)
set "work=%TEMP%\xcpc-run-%RANDOM%-%RANDOM%"
md "%work%" || exit /b 2
set "result=2"

g++ -x c++ -std=c++23 -O2 -DLOCAL "%~f1" -o "%work%\sol.exe"
if errorlevel 1 goto cleanup
"%work%\sol.exe" < "%~2.in" > "%work%\actual.txt"
if errorlevel 1 (
    echo Runtime error. 1>&2
    goto cleanup
)
echo === Expected output ===
type "%answer%"
echo.
echo === Actual output ===
type "%work%\actual.txt"
echo.
echo === Differences ===

set "diff=%work%\diff.txt"
fc.exe /L /N /T /LB100000 "%answer%" "%work%\actual.txt" > "%diff%"
set "result=%errorlevel%"
if "%result%"=="0" echo Accepted
if "%result%"=="1" (
    powershell.exe -NoProfile -Command ^
        "gc -LiteralPath $env:diff | %% { Write-Host $_ -ForegroundColor Red }"
    if errorlevel 1 type "%diff%"
    echo Wrong Answer
)
if "%result%"=="2" echo Comparison failed. 1>&2

:cleanup
rd /s /q "%work%"
exit /b %result%

:usage
echo Usage: %~nx0 a.cpp sample-number 1>&2
exit /b 2
