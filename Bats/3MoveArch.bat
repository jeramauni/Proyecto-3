@echo off

::Deberia ejecutarlo bien si teneis ese nombre en ogre y habeis generado ogre con cmake en una carpeta "build"
echo ---------------------------------------------------
echo Moviendo .dll a \Proyecto\exes
echo ---------------------------------------------------
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\debug\OgreMain_d.dll ..\ProyectoBasico\exes
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\release\OgreMain.dll ..\ProyectoBasico\exes
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\debug\RenderSystem_GL_d.dll ..\ProyectoBasico\exes
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\release\RenderSystem_GL.dll ..\ProyectoBasico\exes


echo ---------------------------------------------------
::echo Moviendo plugins.cfg a \Projects\Application
echo Teneis que cambiar las propiedades del proyecto para que funcione
echo Propiedades - Depuracion - Directorio de trabajo (todas las plataformas, x64) - $(TargetDir)
echo ---------------------------------------------------
::copy ..\ProyectoBasico\exes\plugins.cfg ..\ProyectoBasico\Projects\Application
::copy ..\ProyectoBasico\exes\plugins_d.cfg ..\ProyectoBasico\Projects\Application

PAUSE