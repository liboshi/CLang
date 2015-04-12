 #include <iostream>

using namespace std;

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

int main() {
        Tree t(12);
        t.printsize();
        t.grow(4);
        B b;
        b.println();
        Treea ta(10);
        ta.grow(5);
        ta.printsize();
}
