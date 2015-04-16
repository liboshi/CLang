#include <iostream>

class Stash {
        int size;
        int quantity;
        int next;
        unsigned char* storage;
        void inflate(int increase);
public:
        Stash(int size);
        Stash(int size, int initQuantity);
        ~Stash();
        int add(void* element);
        void* fetch(int index);
        int count();
};

class X {
        int i;
public:
        X(int ii);
        int f() const;
};

class A {
public:
        A();
        void a();
        ~A();
}

class B {
        B();
        void b();
        ~B();
}
