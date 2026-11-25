@echo off
setlocal
set "GENUS_BUILD=%~dp0..\build\windows"
set "GENUS_CMAKE="

if exist "%GENUS_BUILD%\CMakeCache.txt" (
    for /f "usebackq tokens=1,* delims==" %%A in ("%GENUS_BUILD%\CMakeCache.txt") do (
        if "%%A"=="CMAKE_COMMAND:INTERNAL" set "GENUS_CMAKE=%%B"
    )
)

if not defined GENUS_CMAKE (
    echo Configure build/windows with LLVM-MinGW first. See md/DEVELOPING.md. 1>&2
    exit /b 1
)

"%GENUS_CMAKE%" --build "%GENUS_BUILD%" --target Genus
if errorlevel 1 exit /b %ERRORLEVEL%

"%GENUS_BUILD%\Genus.exe"
exit /b %ERRORLEVEL%

