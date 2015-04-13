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

int main() {
        Stash intStash(sizeof(int));
        for(int i = 0; i < 10; i++)
                intStash.add(&i);
        for(int j = 0; j < intStash.count(); j++)
                cout << "intStash.fetch(" << j << ") = " << *(int*)intStash.fetch(j)
                     << endl;
        const int bufsize = 10;
        Stash stringStash(sizeof(char) * bufsize, 10);
        ifstream in("class-test.cpp");
        string line;
        while(getline(in, line))
                stringStash.add((char*) line.c_str());
        int k = 0;
        char* cp;
        while((cp = (char *)stringStash.fetch(k++)) != 0)
                cout << "stringStash.fetch(" << k << ") = "
                    << cp << endl;
}
