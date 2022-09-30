#include "date.hpp"
#include <iostream>
using namespace std;

int main()
{
    DayInfo info = {Sunday, Cloudy};
    if (canTravel(info))
    {
        cout << "We can travel on this day." << endl;
    }
    else
    {
        cout << "We can't travel on this day." << endl;
    }
}