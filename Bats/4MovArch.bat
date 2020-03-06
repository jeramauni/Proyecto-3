@echo off

::Deberia ejecutarlo bien si teneis ese nombre en ogre y habeis generado ogre con cmake en una carpeta "build"
echo ---------------------------------------------------
echo Moviendo .dll a \Proyecto\exes\render
echo ---------------------------------------------------
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\debug\OgreMain_d.dll ..\ProyectoBasico\exes\render
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\release\OgreMain.dll ..\ProyectoBasico\exes\render
::RenderSystem
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\debug\RenderSystem_GL_d.dll ..\ProyectoBasico\exes\render
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\release\RenderSystem_GL.dll ..\ProyectoBasico\exes\render
::Para cargar imagenes .jpg
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\debug\Codec_STBI_d.dll ..\ProyectoBasico\exes\render
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\debug\Codec_STBI_d.ilk ..\ProyectoBasico\exes\render
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\debug\Codec_STBI_d.pdb ..\ProyectoBasico\exes\render
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\release\Codec_STBI.dll ..\ProyectoBasico\exes\render
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\release\Codec_STBI.ilk ..\ProyectoBasico\exes\render
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\bin\release\Codec_STBI.pdb ..\ProyectoBasico\exes\render
::SDL
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\SDL2-2.0.10\VisualC\x64\Debug\SDL2.dll ..\ProyectoBasico\exes\render
copy ..\ProyectoBasico\Dependencias\ogre-1.12.5\Build\SDL2-2.0.10\VisualC\x64\Debug\SDL2.pdb ..\ProyectoBasico\exes\render

PAUSE