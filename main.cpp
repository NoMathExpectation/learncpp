#include <iostream>

using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    string str = "aaaa";
    cout << str << endl;

    str += "b";

    cout << str << endl;

    for (const auto &item: str) {
        cout<<item<<endl;
    }

    string *ptr = &str;

    cout << str << " " << ptr << endl;


    return 0;
}
