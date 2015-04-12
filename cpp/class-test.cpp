 #include <iostream>

using namespace std;

class A {
private:
        int i;
public:
        int j;
protected:
        int k;
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

int main() {
        Tree t(12);
        t.printsize();
        t.grow(4);
}
