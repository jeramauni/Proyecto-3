@echo off

::Deberia ejecutarlo bien si teneis ese nombre en ogre y habeis generado ogre con cmake en una carpeta "build"
echo ---------------------------------------------------
echo Moviendo .dll a \Proyecto\exes
echo ---------------------------------------------------
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\debug\OgreMain_d.dll ..\ProyectoBasico\exes
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\release\OgreMain.dll ..\ProyectoBasico\exes
::RenderSystem
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\debug\RenderSystem_GL_d.dll ..\ProyectoBasico\exes
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\release\RenderSystem_GL.dll ..\ProyectoBasico\exes
::Para cargar imagenes .jpg
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\debug\Codec_STBI_d.dll ..\ProyectoBasico\exes
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\release\Codec_STBI.dll ..\ProyectoBasico\exes
::Input
::OIS
copy ..\ProyectoBasico\Dependencias\OIS\Build\debug\OIS_d.dll ..\ProyectoBasico\exes
copy ..\ProyectoBasico\Dependencias\OIS\Build\release\OIS.dll ..\ProyectoBasico\exes

PAUSE