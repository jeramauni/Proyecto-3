#include <TinyOgre.h>
#include <OgreRoot.h>
#include <Windows.h>

// Window Procedure function
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_DESTROY:PostQuitMessage(0); return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 5));
        EndPaint(hwnd, &ps);
    }return 0;
    case WM_CLOSE:
    {
        if (MessageBox(hwnd, L"Do you want to exit?", L"EXIT", MB_OKCANCEL) == IDOK)
            DestroyWindow(hwnd);
    }return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam); // Default Message Handling
};

#ifdef _DEBUG
int main(HINSTANCE hInstance, HINSTANCE, PWSTR nCmdLine, int nCmdShow)
#else
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR nCmdLine, int nCmdShow)
#endif // DEBUG
{
    /*
    Ogre::Root* root;
#ifdef _DEBUG
    root = new Ogre::Root("plugins_d.cfg");
#else
    root = new Ogre::Root("plugins.cfg");
#endif
    */
    // Inicializacion de Ogre y su ventana
    TinyOgre app;

#ifdef _DEBUG
    try {
        app.go();
    }
    catch (Ogre::Exception & e) {
        printf(e.getFullDescription().c_str(), "An exception has occured!");
    }
#else
    // Register the window class
    const wchar_t CLASS_NAME[] = L"WindowClass";
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.lpszClassName = CLASS_NAME;
    wc.hInstance = hInstance;
    RegisterClass(&wc);
    // Create the window
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"MyFirstWindow",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL);

    if (hwnd == 0) return 0;
    // Show the window
    ShowWindow(hwnd, nCmdShow);
    nCmdShow = 1;
    // The Message loop
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

#endif

    system("Pause");
    
    return 0;
};
//Diseño de uno e idea básica del otro y arquitectura