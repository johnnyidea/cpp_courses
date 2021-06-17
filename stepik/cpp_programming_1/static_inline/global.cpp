#include <iostream>

using namespace std;

extern int global_1 = 1;

int global_2;


int main()
{
    cout << global_1 << endl;
    cout << global_2 << endl;

    return 0;
}

