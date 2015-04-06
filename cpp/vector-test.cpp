#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int get_words() {
        vector<string> words;
        string word;
        ifstream in("vector-test.cpp");
        while(in >> word)
                words.push_back(word);
        for(int i = 0; i < words.size(); i++)
                cout << words[i] << endl;
        return 0;
}

int get_line() {
        vector<string> v;
        ifstream in("vector-test.cpp");
        string line;
        while(getline(in, line))
                v.push_back(line);
        for(int i = 0; i < v.size(); i++)
                cout << i << ": " << v[i] << endl;
        return 0;
}

int get_int() {
        vector<int> v;
        for(int i = 0; i < 10; i++)
                v.push_back(i);
        for(int i = 0; i < v.size(); i++)
                cout << v[i] << endl;
        return 0;
}

int main() {
        get_int();
        return 0;
}
