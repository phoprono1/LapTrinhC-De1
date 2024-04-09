#include <iostream>

#include "include/function.h"

using namespace std;

int main()
{
    int input;

    do
    {
        menu();
        cin >> input;
        switch (input)
        {
        case 0:
            cout << "Thoát chương trình." << endl;
            break;

        default:
            break;
        }

    } while (input != 0);
}