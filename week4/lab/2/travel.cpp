#include "date.hpp"

bool canTravel(DayInfo info)
{
    return (info.day == Saturday || info.day == Sunday) && info.weather != Rainy;
}