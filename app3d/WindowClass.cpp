#include "WindowClass.h"
#include "System.h"

std::map<std::wstring, WNDCLASS> WindowClass::_registered;

WindowClass::WindowClass(wchar_t* class_name, WNDPROC wnd_proc)
{
    if (_registered.find(class_name) == _registered.end())
    {
        WNDCLASS wnd_class;

        wnd_class.style = CS_HREDRAW | CS_VREDRAW;
        wnd_class.lpfnWndProc = wnd_proc;
        wnd_class.cbClsExtra = 0;
        wnd_class.cbWndExtra = 0;
        wnd_class.hInstance = System::GetInstance();
        wnd_class.hIcon = ::LoadIconW(wnd_class.hInstance, MAKEINTRESOURCEW(IDI_APPLICATION));
        wnd_class.hCursor = ::LoadCursorW(NULL, IDC_ARROW);
        wnd_class.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
        wnd_class.lpszMenuName = NULL;
        wnd_class.lpszClassName = class_name;

        if (::RegisterClassW(&wnd_class))
        {
            _registered[class_name] = wnd_class;
        }
    }
}


WindowClass::~WindowClass()
{
}


bool WindowClass::Register()
{
    static bool registered = false;

    if (!registered)
    {
        if (!::RegisterClassW(&_window_class))
        {
            ::MessageBoxW(NULL, L"Call to RegisterClassEx failed!", L"Win32", NULL);

            return 1;
        }

    }
    return false;
}
