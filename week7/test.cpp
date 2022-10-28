#include <iostream>

template <typename T>
void swap(T &a, T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

struct Point
{
    int x, y;
};

template <typename T>
T sum(T x, T y)
{
    std::cout << "The input type is " << typeid(T).name() << std::endl;
    return x + y;
}

template<> Point sum<Point>(Point pt1, Point pt2) {
    std::cout << "The input type is " << typeid(pt1).name() << std::endl;
    Point pt;
    pt.x = pt1.x + pt2.x;
    pt.y = pt1.y + pt2.y;
    return pt;
}

int main()
{
    Point x, y;
    swap(x, y);
}