@echo off

echo ---------------------------------------------------
echo Moviendo .dll a \Proyecto\exes
echo ---------------------------------------------------
echo moviendo OGRE
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\debug\OgreMain_d.dll ..\WeirdEngine\exes\x64\Debug
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\release\OgreMain.dll ..\WeirdEngine\exes\x64\Release
::RenderSystem
echo moviendo RenderSystem
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\debug\RenderSystem_GL_d.dll ..\WeirdEngine\exes\x64\Debug
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\release\RenderSystem_GL.dll ..\WeirdEngine\exes\x64\Release
::Para cargar imagenes .jpg
echo moviendo CODEC
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\debug\Codec_STBI_d.dll ..\WeirdEngine\exes\x64\Debug
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\bin\release\Codec_STBI.dll ..\WeirdEngine\exes\x64\Release
::OIS
echo moviendo OIS
copy ..\WeirdEngine\Dependencias\OIS\Build\debug\OIS_d.dll ..\WeirdEngine\exes\x64\Debug
copy ..\WeirdEngine\Dependencias\OIS\Build\release\OIS.dll ..\WeirdEngine\exes\x64\Release
::SDL
echo moviendo SDL
copy ..\WeirdEngine\Dependencias\ogre-1.12.5\Build\SDL2-2.0.10\VisualC\x64\Debug\SDL2.dll ..\WeirdEngine\exes\x64\Release
::FMOD
echo moviendo FMOD
copy ..\WeirdEngine\Dependencias\fmod\bin\fmodL.dll ..\WeirdEngine\exes\x64\Debug
copy ..\WeirdEngine\Dependencias\fmod\bin\fmod.dll ..\WeirdEngine\exes\x64\Release
::Cegui
echo moviendo CEGUI
echo CeguiBase
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUIBase-0.dll ..\WeirdEngine\exes\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUIBase-0_d.dll ..\WeirdEngine\exes\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUICommonDialogs-0.dll ..\WeirdEngine\exes\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUICommonDialogs-0_d.dll ..\WeirdEngine\exes\x64\Debug
echo CeguiCoreWindowRenderer
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUICoreWindowRendererSet.dll ..\WeirdEngine\exes\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUICoreWindowRendererSet_d.dll ..\WeirdEngine\exes\x64\Debug
echo CeguiOgreRenderer
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUIOgreRenderer-0.dll ..\WeirdEngine\exes\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUIOgreRenderer-0_d.dll ..\WeirdEngine\exes\x64\Debug
echo tinyXML
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUITinyXMLParser.dll ..\WeirdEngine\exes\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\build\bin\CEGUITinyXMLParser_d.dll ..\WeirdEngine\exes\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\tinyxml.dll ..\WeirdEngine\exes\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\tinyxml_d.dll ..\WeirdEngine\exes\x64\Debug
echo CeguiLua
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\lua.dll ..\WeirdEngine\exes\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\lua_d.dll ..\WeirdEngine\exes\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\toluapp.dll ..\WeirdEngine\exes\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\toluapp_d.dll ..\WeirdEngine\exes\x64\Debug
echo freeType
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\freetype.dll ..\WeirdEngine\exes\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\freetype_d.dll ..\WeirdEngine\exes\x64\Debug
echo OtherDependencies
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\jpeg.dll ..\WeirdEngine\exes\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\jpeg_d.dll ..\WeirdEngine\exes\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\glew.dll ..\WeirdEngine\exes\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\glew_d.dll ..\WeirdEngine\exes\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\glfw.dll ..\WeirdEngine\exes\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\glfw_d.dll ..\WeirdEngine\exes\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\libexpat.dll ..\WeirdEngine\exes\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\libexpat_d.dll ..\WeirdEngine\exes\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\libpng.dll ..\WeirdEngine\exes\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\libpng_d.dll ..\WeirdEngine\exes\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\pcre.dll ..\WeirdEngine\exes\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\pcre_d.dll ..\WeirdEngine\exes\x64\Debug
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\zlib.dll ..\WeirdEngine\exes\x64\Release
copy ..\WeirdEngine\Dependencias\cegui\dependencies\bin\zlib_d.dll ..\WeirdEngine\exes\x64\Debug

PAUSE