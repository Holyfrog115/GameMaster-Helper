#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif

using namespace std;

int main()
{
#if defined(_WIN32) || defined(_WIN64)
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    cout << "Привет, мир\n";
    return 0;
}