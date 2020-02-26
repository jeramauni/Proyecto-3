#include "RenderUtilities.h"
#include "OgreRenderWindow.h"

#include <Windows.h>

using namespace Ogre;

namespace RenderUtils {

    typedef std::multimap<RenderWindow*, WindowEventListener*> WindowEventListeners;
    static WindowEventListeners _msListeners;
    static RenderWindowList _msWindows;

    LRESULT CALLBACK WindowEventUtilities::_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        if (uMsg == WM_CREATE) {   
            // Store pointer in user data area
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)(((LPCREATESTRUCT)lParam)->lpCreateParams));
            return 0;
        }

        // look up window instance
        // note: it is possible to get a WM_SIZE before WM_CREATE
        RenderWindow* win = (RenderWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        if (!win)
            return DefWindowProc(hWnd, uMsg, wParam, lParam);

        //LogManager* log = LogManager::getSingletonPtr();
        //Iterator of all listeners registered to this RenderWindow
        WindowEventListeners::iterator index,
            start = _msListeners.lower_bound(win),
            end = _msListeners.upper_bound(win);

        switch (uMsg) {
        case WM_ACTIVATE: {
            bool active = (LOWORD(wParam) != WA_INACTIVE);
            if (active) {
                win->setActive(true);
            }
            else {
                if (win->isDeactivatedOnFocusChange()) {
                    win->setActive(false);
                }
            }

            for (; start != end; ++start)
                (start->second)->windowFocusChange(win);
            break;
        }
        case WM_SYSKEYDOWN:
            switch (wParam) {
            case VK_CONTROL:
            case VK_SHIFT:
            case VK_MENU: //ALT
                //return zero to bypass defProc and signal we processed the message
                return 0;
            }
            break;
        case WM_SYSKEYUP:
            switch (wParam) {
            case VK_CONTROL:
            case VK_SHIFT:
            case VK_MENU: //ALT
            case VK_F10:
                //return zero to bypass defProc and signal we processed the message
                return 0;
            }
            break;
        case WM_SYSCHAR:
            // return zero to bypass defProc and signal we processed the message, unless it's an ALT-space
            if (wParam != VK_SPACE)
                return 0;
            break;
        case WM_ENTERSIZEMOVE:
            //log->logMessage("WM_ENTERSIZEMOVE");
            break;
        case WM_EXITSIZEMOVE:
            //log->logMessage("WM_EXITSIZEMOVE");
            break;
        case WM_MOVE:
            //log->logMessage("WM_MOVE");
            win->windowMovedOrResized();
            for (index = start; index != end; ++index)
                (index->second)->windowMoved(win);
            break;
        case WM_DISPLAYCHANGE:
            win->windowMovedOrResized();
            for (index = start; index != end; ++index)
                (index->second)->windowResized(win);
            break;
        case WM_SIZE:
            //log->logMessage("WM_SIZE");
            win->windowMovedOrResized();
            for (index = start; index != end; ++index)
                (index->second)->windowResized(win);
            break;
        case WM_GETMINMAXINFO:
            // Prevent the window from going smaller than some minimu size
            ((MINMAXINFO*)lParam)->ptMinTrackSize.x = 100;
            ((MINMAXINFO*)lParam)->ptMinTrackSize.y = 100;
            break;
        case WM_CLOSE: {
            //log->logMessage("WM_CLOSE");
            bool close = true;
            for (index = start; index != end; ++index) {
                if (!(index->second)->windowClosing(win))
                    close = false;
            }
            if (!close) return 0;

            for (index = _msListeners.lower_bound(win); index != end; ++index)
                (index->second)->windowClosed(win);
            win->destroy();
            return 0;
        }
        }

        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    //--------------------------------------------------------------------------------//
    void WindowEventUtilities::addWindowEventListener(RenderWindow* window, WindowEventListener* listener) {
        _msListeners.insert(std::make_pair(window, listener));
    }

    //--------------------------------------------------------------------------------//
    void WindowEventUtilities::removeWindowEventListener(RenderWindow* window, WindowEventListener* listener) {
        WindowEventListeners::iterator i = _msListeners.begin(), e = _msListeners.end();

        for (; i != e; ++i) {
            if (i->first == window && i->second == listener) {
                _msListeners.erase(i);
                break;
            }
        }
    }

    //--------------------------------------------------------------------------------//
    void WindowEventUtilities::_addRenderWindow(RenderWindow* window) {
        _msWindows.push_back(window);
    }

    //--------------------------------------------------------------------------------//
    void WindowEventUtilities::messagePump() {
        // Windows Message Loop (NULL means check all HWNDs belonging to this context)
        MSG  msg;
        while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    //--------------------------------------------------------------------------------//
    void WindowEventUtilities::_removeRenderWindow(RenderWindow* window) {
        RenderWindowList::iterator i = std::find(_msWindows.begin(), _msWindows.end(), window);
        if (i != _msWindows.end())
            _msWindows.erase(i);
    }
}