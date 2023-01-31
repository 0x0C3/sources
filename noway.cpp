#include <windows.h>
#include <iostream>

void one()
{
    std::cout << "function 1" << std::endl;
}

void two(const char * text)
{
    std::cout << text << std::endl;
}
int main()
{
    while (true)
    {
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            one();
            two("AAAA");
        }
    }
    return 0;
    
}

