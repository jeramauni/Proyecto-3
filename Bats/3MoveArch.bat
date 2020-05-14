@echo off

::Deberia ejecutarlo bien si teneis ese nombre en ogre y habeis generado ogre con cmake en una carpeta "build"
echo ---------------------------------------------------
echo Moviendo .dll a \Proyecto\exes
echo ---------------------------------------------------
echo moviendo OGRE
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\debug\OgreMain_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\release\OgreMain.dll ..\WeirdEngine\exes
::RenderSystem
echo moviendo RenderSystem
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\debug\RenderSystem_GL_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\release\RenderSystem_GL.dll ..\WeirdEngine\exes
::Para cargar imagenes .jpg
echo moviendo CODEC
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\debug\Codec_STBI_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\release\Codec_STBI.dll ..\WeirdEngine\exes
::OIS
echo moviendo OIS
copy ..\WeirdEngine\Dependencias\OIS\Build\debug\OIS_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\OIS\Build\release\OIS.dll ..\WeirdEngine\exes
::SDL
echo moviendo SDL
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\SDL2-2.0.10\VisualC\x64\Debug\SDL2.dll ..\WeirdEngine\exes
::FMOD
echo moviendo FMOD
copy ..\WeirdEngine\Dependencias\fmod\bin\fmodL.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\fmod\bin\fmod.dll ..\WeirdEngine\exes
::Cegui
echo moviendo CEGUI
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUICoreWindowRendererSet.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUICoreWindowRendererSet_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUIExpatParser.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUIExpatParser_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUISILLYImageCodec.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUISILLYImageCodec_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUIBase-0.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUIBase-0_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUICoreWindowRendererSet.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUICoreWindowRendererSet_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUIOpenGlRenderer-0.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUIOpenGlRenderer-0_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\jpeg.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\jpeg_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\libexpat.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\libexpat_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\libpng.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\libpng_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\lua.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\lua_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\pcre.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\pcre_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\SILLY.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\SILLY_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\tinyxml.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\tinyxml_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\toluapp.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\toluapp_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\zlib.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\zlib_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\freetype.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\freetype_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\glew.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\glew_d.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\glfw.dll ..\WeirdEngine\exes
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\glfw_d.dll ..\WeirdEngine\exes

PAUSE