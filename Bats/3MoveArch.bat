@echo off

::Deberia ejecutarlo bien si teneis ese nombre en ogre y habeis generado ogre con cmake en una carpeta "build"
echo ---------------------------------------------------
echo Moviendo .dll a \Proyecto\exes
echo ---------------------------------------------------
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\debug\OgreMain_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\release\OgreMain.dll ..\WeirdEngine\exes
::RenderSystem
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\debug\RenderSystem_GL_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\release\RenderSystem_GL.dll ..\WeirdEngine\exes
::Para cargar imagenes .jpg
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\debug\Codec_STBI_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\release\Codec_STBI.dll ..\WeirdEngine\exes
::OIS
copy ..\WeirdEngine\Dependencias\OIS\Build\debug\OIS_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\OIS\Build\release\OIS.dll ..\WeirdEngine\exes
::SDL
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\SDL2-2.0.10\VisualC\x64\Debug\SDL2.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\SDL2-2.0.10\VisualC\x64\Debug\SDL2.pdb ..\WeirdEngine\exes
::FMOD
copy ..\WeirdEngine\Dependencias\fmod-2.00.07\fmodL.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\fmod-2.00.07\fmod.dll ..\WeirdEngine\exes

PAUSE