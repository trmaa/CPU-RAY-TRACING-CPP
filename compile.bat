@echo off
setlocal

:: https://dotnet.microsoft.com/en-us/download/dotnet/thank-you/sdk-8.0.101-windows-x64-installer

:: Definir variables para las rutas de los archivos .dll
set dotnet_framework=%SystemRoot%\Microsoft.NET\Framework64\v4.0.30319
set windows_forms_dll=%dotnet_framework%\System.Windows.Forms.dll
set drawing_dll=%dotnet_framework%\System.Drawing.dll
set opentk_dll=.\libs\sopentk.dll

:: Ruta al compilador de C#
set csc_path="%dotnet_framework%\csc.exe"

:: Compile
call :compile
if %errorlevel% equ 0 (
    echo Compilación exitosa. Ejecutando...
    start "" "%CD%\renderer.exe"
) else (
    echo Error durante la compilación.
)

exit /b %errorlevel%

:compile
:: Compilación usando el compilador de C# de .NET
:: Asegúrate de que el compilador está en el PATH o provee la ruta completa
:: Si los ensamblados .dll necesarios no están en el GAC, debes proveer la ruta completa o relativa a ellos
"%csc_path%" /out:renderer.exe /reference:%windows_forms_dll% /reference:%drawing_dll% .\src\*.cs
exit /b %errorlevel%
