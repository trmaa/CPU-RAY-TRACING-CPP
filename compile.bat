@echo off
setlocal

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
csc /out:renderer.exe /reference:System.Windows.Forms.dll /reference:System.Drawing.dll *.cs
exit /b %errorlevel%