#include <list>
#include <iostream>

using namespace std;

int main() {
        list<int> numbers;
        numbers.push_back(1);
        numbers.push_back(2);
        for (int i : numbers) {
                cout << i << endl;
        }
}
