@echo off

:: Determine the architecture
set ARCH=
for /f "tokens=2 delims==" %%A in ('"wmic os get osarchitecture /value"') do set ARCH=%%A

if "%ARCH%"=="32-bit" (
    set ARCH=amd64
) else if "%ARCH%"=="64-bit" (
    set ARCH=amd64
) else if "%ARCH%"=="ARM64" (
    set ARCH=arm64
) else (
    echo Unsupported architecture: %ARCH%
    exit /b 1
)

:: Construct the path to the Bazelisk binary
set OS=windows
set BAZELISK_BINARY=.bazelw\bazelisk-%OS%-%ARCH%.exe

:: Check if the binary exists
if not exist "%BAZELISK_BINARY%" (
    echo Bazelisk binary not found: %BAZELISK_BINARY%
    exit /b 1
)

:: Run the Bazelisk binary
"%BAZELISK_BINARY%" %*
