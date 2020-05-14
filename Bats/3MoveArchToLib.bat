@echo off

::Deberia ejecutarlo bien si teneis ese nombre en ogre y habeis generado ogre con cmake en una carpeta "build"
echo ---------------------------------------------------
echo Moviendo .dll a \Proyecto\exes
echo ---------------------------------------------------
echo moviendo OGRE
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\debug\OgreMain_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\release\OgreMain.dll ..\WeirdEngine\build\libs\x64\Release
::RenderSystem
echo moviendo RenderSystem
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\debug\RenderSystem_GL_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\release\RenderSystem_GL.dll ..\WeirdEngine\build\libs\x64\Release
::Para cargar imagenes .jpg
echo moviendo CODEC
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\debug\Codec_STBI_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\release\Codec_STBI.dll ..\WeirdEngine\build\libs\x64\Release
::OIS
echo moviendo OIS
copy ..\WeirdEngine\Dependencias\OIS\Build\debug\OIS_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\OIS\Build\release\OIS.dll ..\WeirdEngine\build\libs\x64\Release
::SDL
echo moviendo SDL
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\SDL2-2.0.10\VisualC\x64\Debug\SDL2.dll ..\WeirdEngine\build\libs\x64\Release
::FMOD
echo moviendo FMOD
copy ..\WeirdEngine\Dependencias\fmod\bin\fmodL.dll ..\WeirdEngine\x64\Debug
copy ..\WeirdEngine\Dependencias\fmod\bin\fmod.dll ..\WeirdEngine\x64\Release
::Cegui
echo moviendo CEGUI
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUICoreWindowRendererSet.dll ..\WeirdEngine\build\libs\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUICoreWindowRendererSet_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUIExpatParser.dll ..\WeirdEngine\build\libs\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUIExpatParser_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUISILLYImageCodec.dll ..\WeirdEngine\build\libs\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUISILLYImageCodec_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUIBase-0.dll ..\WeirdEngine\build\libs\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUIBase-0_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUICoreWindowRendererSet.dll ..\WeirdEngine\build\libs\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUICoreWindowRendererSet_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUIOpenGlRenderer-0.dll ..\WeirdEngine\build\libs\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUIOpenGlRenderer-0_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\jpeg.dll ..\WeirdEngine\build\libs\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\jpeg_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\libexpat.dll ..\WeirdEngine\build\libs\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\libexpat_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\libpng.dll ..\WeirdEngine\build\libs\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\libpng_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\lua.dll ..\WeirdEngine\build\libs\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\lua_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\pcre.dll ..\WeirdEngine\build\libs\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\pcre_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\SILLY.dll ..\WeirdEngine\build\libs\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\SILLY_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\tinyxml.dll ..\WeirdEngine\build\libs\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\tinyxml_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\toluapp.dll ..\WeirdEngine\build\libs\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\toluapp_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\zlib.dll ..\WeirdEngine\build\libs\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\zlib_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\freetype.dll ..\WeirdEngine\build\libs\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\freetype_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\glew.dll ..\WeirdEngine\build\libs\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\glew_d.dll ..\WeirdEngine\build\libs\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\glfw.dll ..\WeirdEngine\build\libs\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\glfw_d.dll ..\WeirdEngine\build\libs\x64\Debug

PAUSE