#include <iostream>

using namespace std;

#define FUNCTION(name, a) \
        int fun_##name() { \
                return a;\
        }

FUNCTION(abcd, 12)
FUNCTION(fff, 2)
FUNCTION(qqq, 23)

#undef FUNCTION
#define FUNCTION 34
#define OUTPUT(a) cout << #a << endl;

int
main()
{
        cout << "abcd: " << fun_abcd() << endl;;
        cout << "fff: " << fun_fff() << endl;
        cout << "qqq: " << fun_qqq() << endl;
        cout << FUNCTION << endl;
        OUTPUT(million);
}
