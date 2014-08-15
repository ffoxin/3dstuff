#ifndef SYSTEM_H
#define SYSTEM_H

#include <windows.h>

class System
{
public:
    System() = delete;
    ~System();

    
public:
    static HINSTANCE GetInstance();
    static void SetInstance(HINSTANCE instance);
private:
    static HINSTANCE _instance;
};

#endif // SYSTEM_H
