#include <iostream>
using namespace std;

template <typename T>
T Max(T a, T b)
{
        return a > b ? a: b;
}

int
main()
{
        cout << Max(3, 7) << endl;
        cout << Max(3.0, 7.0) << endl;
        return 0;
}
