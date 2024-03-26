@echo off
setlocal

set dotnet_framework=%SystemRoot%\Microsoft.NET\Framework64\v4.0.30319
set windows_forms_dll=%dotnet_framework%\System.Windows.Forms.dll
set drawing_dll=%dotnet_framework%\System.Drawing.dll
set opentk_dll=.\libs\sopentk.dll

set csc_path="%dotnet_framework%\csc.exe"

call :compile
if %errorlevel% equ 0 (
    echo Compilación exitosa. Ejecutando...
    start "" "%CD%\renderer.exe"
) else (
    echo Error durante la compilación.
)

exit /b %errorlevel%

:compile
"%csc_path%" /out:renderer.exe /reference:%windows_forms_dll% /reference:%drawing_dll% .\src\*.cs
exit /b %errorlevel%
