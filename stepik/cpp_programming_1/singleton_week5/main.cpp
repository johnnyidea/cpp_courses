
#include "singleton.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{

    Singleton & s = Singleton::instance();
    cout << argv[1];
    return 0;
}

