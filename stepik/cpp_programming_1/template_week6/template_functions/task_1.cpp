#include <iostream>

template <typename T1, typename T2>
void copy_n(T1 *t1, T2 *t2, size_t size)
{
    for (size_t i = 0; i < size; i++)
        *(t1 +i ) = static_cast<T1>(*(t2 + i));
}

int main(int argc, char * argv[])
{
    int ints[] = {1, 2, 3, 4};
    double doubles[4] = {};
    copy_n(doubles, ints, 4); // теперь в массиве doubles содержатся элементы 1.0, 2.0, 3.0 и 4.0

    return 0;
}