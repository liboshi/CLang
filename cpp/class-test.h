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
public:
        X();
        virtual void println();
        ~X();
};

class Y : public X {
public:
        Y();
        void println();
        ~Y();
};
