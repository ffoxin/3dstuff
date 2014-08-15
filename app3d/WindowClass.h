#ifndef WINDOWCLASS_H
#define WINDOWCLASS_H

#include <windows.h>
#include <map>

class WindowClass
{
public:
    WindowClass(wchar_t* class_name, WNDPROC wnd_proc);
    virtual ~WindowClass();

private:
    static std::map<std::wstring, WNDCLASS> _registered;
public:
    bool Register();
};

#endif // WINDOWCLASS_H
