@echo off
set "VCVARS=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat"

if not exist "%VCVARS%" (
    echo [ERROR] Could not find Visual Studio vcvarsall.bat at expected path.
    echo Please ensure Visual Studio 2022 Community is installed.
    pause
    exit /b
)

echo Setting up Visual Studio Environment...
call "%VCVARS%" x64

echo Compiling Flappy Bird...
cl main.cpp /Fe:flappybird.exe /EHsc

if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Compilation failed.
    pause
    exit /b
)

echo.
echo Compilation Successful!
echo Run 'flappybird.exe' to play.
pause
