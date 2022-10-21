#include <iostream>

using namespace std;

char *match(char *s, char ch) {
    while (*s != '\0') {
        if (*(s++) == ch) {
            return s - 1;
        }
    }
    return NULL;
}

int main() {
    char *chs = "Never gonna give you up, never gonna let you down.";
    char ch = 'u';

    char *p = match(chs, ch);
    if (p != NULL) {
        cout << "Found." << endl;
    } else {
        cout << "Not found." << endl;
    }
}