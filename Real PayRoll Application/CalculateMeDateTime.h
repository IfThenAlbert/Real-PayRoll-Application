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
	long getDifference(int monthFirst, int dayFirst, int yearFirst, int monthSecond, int daySecond, int yearSecond);
};

