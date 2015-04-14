#include <iostream>

using namespace std;

void func() {
        cout << "func called..." << endl;
}

int main() {
        void (*fp) ();
        fp = func;
        (*fp) ();
        void (*fp2) () = func;
        (*fp2) ();
}
