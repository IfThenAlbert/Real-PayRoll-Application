#pragma once
#include <iostream>
#include <iomanip>
#include <Math.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <Windows.h>

using namespace std;
class CalculateMeDateTime{
private:

public:
	string getCurrentDateTime();
	int no_of_days_in_month(int month, int year);
	int check_leap_year(int year);
	long getDifference(int monthFirst, int dayFirst, int yearFirst, int monthSecond, int daySecond, int yearSecond);
};

