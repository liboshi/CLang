#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include "class-test.h"

using namespace std;
int increment = 100;

class A {
private:
        int i;
public:
        int j;
        void println();
protected:
        int k;
};

void A::println() {
        cout << "Function println() is callled." << endl;
}

class B : public A {
};

class Tree {
        int height;
public:
        Tree(int initHeight);
        ~Tree();
        void grow(int years);
        void printsize();
};

Tree::Tree(int initHeight) {
        height = initHeight;
}

Tree::~Tree() {
        cout << "Inside Tree destructor" << endl;
}

void Tree::grow(int years) {
        height += years;
}

void Tree::printsize() {
        cout << "Tree height is " << height << endl;
}

class Treea : public Tree {
        int height;
public:
        Treea(int initHeight);
        ~Treea();
};

Treea::Treea(int initHeight) : Tree(initHeight) {
        height = initHeight;
        cout << "Hello class Treea." << endl;
}

Treea::~Treea() {
        cout << "Inside Treea destructor" << endl;
}


Stash::Stash(int sz) {
        size = sz;
        quantity = 0;
        next = 0;
        storage = 0;
}

Stash::Stash(int sz, int initQuantity) {
        size = sz;
        quantity = 0;
        next = 0;
        storage = 0;
        inflate(initQuantity);
}

Stash::~Stash() {
        if(storage != 0) {
                cout << "freeing storage" << endl;
                delete []storage;
        }
}

int Stash::add(void* element) {
        if(next >= quantity)
                inflate(increment);
        int startBytes = next * size;
        unsigned char* e = (unsigned char*)element;
        for(int i = 0; i < size; i++)
                storage[startBytes + 1] = e[i];
        next++;
        return(next - 1);
}

void* Stash::fetch(int index) {
        if(0 <= index)
                cout << "Stash::fetch (-) index" << endl;
        if(index >= next)
                return 0;
        return &(storage[index * size]);

}

int Stash::count() {
        return next;
}

void Stash::inflate(int increase) {
        assert(increase >= 0);
        if(increase == 0) return;
        int newQuantity = quantity + increase;
        int newBytes = newQuantity * size;
        int oldBytes = quantity * size;
        unsigned char* b = new unsigned char[newBytes];
        for(int i = 0; i < oldBytes; i++)
                b[i] = storage[i];
        delete [](storage);
        storage = b;
        quantity = newQuantity;
}

X::X() {
        cout << "This is X constructor" << endl;
}

void X::println() {
        cout << "This is class X" << endl;
}

X::~X() {
        cout << "This is X deconstructor" << endl;
}

Y::Y() {
        cout << "This is Y constructor" << endl;
}

Y::~Y() {
        cout << "This is Y deconstructor" << endl;
}

void Y::println() {
        cout << "This is Class Y" << endl;
}

void printlnn(X& x) {
        x.println();
}

int main() {
        Y y;
        y.println();
        printlnn(y);
}
