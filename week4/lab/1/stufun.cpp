#include "stuinfo.hpp"
#include <iostream>

using namespace std;

void inputstu(stuinfo stu[], int n) {
    for (int i = 0; i < n; i++)
    {
        cout << endl << "Please input student" << i + 1 << "'s name: ";
        cin >> stu[i].name;
        cout << endl << "Please input student" << i + 1 << "'s three scores: ";
        cin >> stu[i].score[0] >> stu[i].score[1] >> stu[i].score[2];

        stu[i].ave = (stu[i].score[0] + stu[i].score[1] + stu[i].score[2]) / 3;
    }
}

void showstu(stuinfo stu[], int n) {
    for (int i = 0; i < n; i++)
    {
        cout << "Student " << stu[i].name << "'s scores are " << stu[i].score[0] << ' ' << stu[i].score[1] << ' ' << stu[i].score[2] << " with average of " << stu[i].ave << '.' << endl;
    }
}

void sortstu(stuinfo stu[], int n) {
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i; j < n - 1; j++)
        {
            if (stu[j].ave < stu[j + 1].ave) {
                stuinfo temp = stu[j];
                stu[j] = stu[j + 1];
                stu[j + 1] = temp; 
            }
        }
    }
}

bool findstu(stuinfo stu[], int n, char ch[]) {
    for (int i = 0; i < n; i++)
    {
        if (strcmp(stu[i].name, ch) == 0) {
            return true;
        }
    }
    return false;
}