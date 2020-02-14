#include <OgreRoot.h>

#ifdef _DEBUG
int main()
#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	Ogre::Root* root;
#ifdef _DEBUG
	root = new Ogre::Root("plugins_d.cfg");
#else
	root = new Ogre::Root("plugins.cfg");
#endif
	return 0;
}
//Diseño de uno e idea básica del otro y arquitectura