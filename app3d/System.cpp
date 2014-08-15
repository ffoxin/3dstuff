#include "System.h"

HINSTANCE System::_instance;

System::~System()
{
}


HINSTANCE System::GetInstance()
{
    return _instance;
}


void System::SetInstance(HINSTANCE instance)
{
    static bool set = false;

    if (!set)
    {
        _instance = instance;
    }
}
