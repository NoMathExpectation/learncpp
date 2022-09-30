enum Day { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };
enum Weather { Sunny, Rainy, Cloudy, Windy };
struct DayInfo
{
    Day day;
    Weather weather;
};

bool canTravel(DayInfo info);
