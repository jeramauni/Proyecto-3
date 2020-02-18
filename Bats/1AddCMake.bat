@echo off

:: Poner vuestra direccion de destino dentro del proyecto dependencias
echo ---------------------------------------------------
echo Add CMake al proyecto
echo Darle la opcion de directorio "D"
echo ---------------------------------------------------
xcopy ..\cmake-3.17.0-rc1-win64-x64 ..\ProyectoBasico\Dependencias\cmake /E

echo ---------------------------------------------------
echo Creando la carpeta "Build"
echo ---------------------------------------------------
MD ..\ProyectoBasico\Dependencias\ogre-1.12.4\Build

:: Poned la ubicacion del exe en el proyecto
echo ---------------------------------------------------
echo ejecucion del exe de CMake
echo Si os da problema al hacer el "generate" -> buscar "imgui" desmarcarlo y volver a generar
echo ---------------------------------------------------
start ..\ProyectoBasico\Dependencias\cmake\bin\cmake-gui.exe

PAUSE