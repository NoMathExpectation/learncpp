#include <iostream>
using namespace std;

struct point {
    float x;
    float y;
};

point middle(point *a, point *b) {
    point result;
    result.x = (a->x + b->x) / 2;
    result.y = (a->y + b->y) / 2;
    return result;
}

int main() {
    point a = {114, 514}, b = {1919, 810};
    point c = middle(&a, &b);
    cout << c.x << " " << c.y << endl;
}