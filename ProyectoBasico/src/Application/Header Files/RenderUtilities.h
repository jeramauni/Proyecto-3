#ifndef __RenderUtilities_H__
#define __RenderUtilities_H__

#include "OgrePrerequisites.h"
#include "OgrePlatform.h"
#include "OgreHeaderPrefix.h"
#include "OgreHeaderSuffix.h"
#include "OgreCommon.h"

#include <Windows.h>

#ifdef OGREBITES_STATIC_DEFINE
#  define _RenderUtilsExport
#  define RENDERUTILS_NO_EXPORT
#else
#  ifndef _RenderUtilsExport
#    ifdef RenderUtils_EXPORTS
/* We are building this library */
#      define _WRenderUtils __declspec(dllexport)
#    else
/* We are using this library */
#      define _WRenderUtils __declspec(dllimport)
#    endif
#  endif

#  ifndef RENDERUTILS_NO_EXPORT
#    define RENDERUTILS_NO_EXPORT 
#  endif
#endif

namespace RenderUtils {
	/*
		Clase para comunicarse con Windows.
	*/
	class _WRenderUtils WindowEventListener {
	public:
		virtual ~WindowEventListener() {}
        /**
    @remarks
        Window has moved position
    @param rw
        The RenderWindow which created this events
    */
        virtual void windowMoved(Ogre::RenderWindow* rw) { (void)rw; }

        /**
        @remarks
            Window has resized
        @param rw
            The RenderWindow which created this events
        */
        virtual void windowResized(Ogre::RenderWindow* rw) { (void)rw; }

        /**
        @remarks
            Window is closing (Only triggered if user pressed the [X] button)
        @param rw
            The RenderWindow which created this events
        @return True will close the window(default).
        */
        virtual bool windowClosing(Ogre::RenderWindow* rw) { return true; }

        /**
        @remarks
            Window has been closed (Only triggered if user pressed the [X] button)
        @param rw
            The RenderWindow which created this events
        @note
            The window has not actually close yet when this event triggers. It's only closed after
            all windowClosed events are triggered. This allows apps to deinitialise properly if they
            have services that needs the window to exist when deinitialising.
        */
        virtual void windowClosed(Ogre::RenderWindow* rw) { (void)rw; }

        /**
        @remarks
            Window has lost/gained focus
        @param rw
            The RenderWindow which created this events
        */
        virtual void windowFocusChange(Ogre::RenderWindow* rw) { (void)rw; }

	};


    // ESTAS UTILIDADES HABRA QUE CAMBIARLAS IMPLEMENTANDO SDL2
    //---------------------------------------------
    /**
       Utility class to handle Window Messages

       This only provides a minimal implementation for moving/ resizing windows.
       For input handling and proper platform integration rather use SDL2/ Qt/ whatever.
       @see ApplicationContext
   */
    class _WRenderUtils WindowEventUtilities
    {
    public:
        /**
            Call this once per frame. This will update all registered RenderWindows.
        */
        static void messagePump();

        /**
        @remarks
            Add a listener to listen to renderwindow events (multiple listener's per renderwindow is fine)
            The same listener can listen to multiple windows, as the Window Pointer is sent along with
            any messages.
        @param window
            The RenderWindow you are interested in monitoring
        @param listener
            Your callback listener
        */
        static void addWindowEventListener(Ogre::RenderWindow* window, WindowEventListener* listener);

        /**
        @remarks
            Remove previously added listener
        @param window
            The RenderWindow you registered with
        @param listener
            The listener registered
        */
        static void removeWindowEventListener(Ogre::RenderWindow* window, WindowEventListener* listener);

        /**
        @remarks
            Call upon creation of Ogre windows. You are free to add your
            external windows here too if needed.
        @param window
            The RenderWindow to monitor
        */
        static void _addRenderWindow(Ogre::RenderWindow* window);

        /**
        @remarks
            Called upon deletion of previously registered windows.
        @param window
            The RenderWindow to remove from list
        */
        static void _removeRenderWindow(Ogre::RenderWindow* window);

        //! Internal winProc (RenderWindow's use this when creating the Win32 Window)
        static LRESULT CALLBACK _WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    };
}

namespace Ogre {
    // backwards compatibility
    typedef OGRE_DEPRECATED RenderUtils::WindowEventListener WindowEventListener;
    typedef OGRE_DEPRECATED RenderUtils::WindowEventUtilities WindowEventUtilities;
}

#endif 
