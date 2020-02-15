@echo off

:: Poner vuestra direccion de destino dentro del proyecto dependencias
echo ---------------------------------------------------
echo Add CMake al proyecto
echo Darle la opcion de directorio "D"
echo ---------------------------------------------------
xcopy ..\cmake-3.17.0-rc1-win64-x64 ..\ProyectoBasico\Dependencias\cmake /E

:: Poned la ubicacion del exe en el proyecto
echo ---------------------------------------------------
echo ejecucion del exe de CMake
echo ---------------------------------------------------
start ..\ProyectoBasico\Dependencias\cmake\bin\cmake-gui.exe