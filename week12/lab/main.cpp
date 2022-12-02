#include <iostream>
#include "CCube.cpp"
#include "CSphere.cpp"

int main() {
    CCube a_cube(4, 5, 6);
    CSphere c_sphere(7.9);

    CStereoShape *p = &a_cube;
    p->show();

    p = &c_sphere;
    p->show();

    std::cout << "Number of objects: " << CStereoShape::getNumberOfObject() << std::endl;

    return 0;
}