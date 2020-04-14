@echo off

:: Poner vuestra direccion de destino dentro del proyecto dependencias
echo ---------------------------------------------------
echo Add CMake al proyecto
echo Darle la opcion de directorio "D"
echo ---------------------------------------------------
xcopy ..\cmake-3.17.0-rc1-win64-x64 ..\WeirdEngine\Dependencias\cmake /E

echo ---------------------------------------------------
echo Creando la carpetas "Build" en Ogre y Ois
echo ---------------------------------------------------
MD ..\WeirdEngine\Dependencias\ogre-1.12.5\Build
MD ..\WeirdEngine\Dependencias\OIS\Build

echo ---------------------------------------------------
echo ejecucion del exe de CMake
echo Generar Ogre en su carpeta Build
echo Si os da problema al hacer el "generate" - buscar "imgui" desmarcarlo y volver a generar
echo Generar Ois en su carpeta Build (Descargar desde Github/OIS)
echo ---------------------------------------------------
start ..\WeirdEngine\Dependencias\cmake\bin\cmake-gui.exe

PAUSE