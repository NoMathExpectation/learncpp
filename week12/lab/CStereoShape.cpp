#include <iostream>
#ifndef _SHAPE_
#define _SHAPE_
class CStereoShape
{
private:
    static int numberOfObject;

public:
    virtual double getArea() const noexcept
    {
        std::cout << "CStereoShape::getArea() is called." << std::endl;
        return 0.0;
    }

    virtual double getVolume() const noexcept
    {
        std::cout << "CStereoShape::getVolume() is called." << std::endl;
        return 0.0;
    }

    virtual void show() const noexcept
    {
        std::cout << "CStereoShape::show() is called." << std::endl;
    }

    static int getNumberOfObject() noexcept
    {
        return numberOfObject;
    }

    CStereoShape()
    {
        numberOfObject++;
    }
};

int CStereoShape::numberOfObject = 0;
#endif