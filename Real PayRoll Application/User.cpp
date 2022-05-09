#define __STDC_WANT_LIB_EXT1__ 1
#include "User.h"
// import all libraries needed ========================================================================================
#include <iostream>
#include <iomanip>
#include <Math.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include "AppPages.h"
using namespace std;

// constructor


// PRIVATE:: methods
vector<string> User::specialDelimetedString(string ll, char limit) {
	vector<string> res;
	stringstream s_stream(ll);

	while (s_stream.good()) {
		string s;
		getline(s_stream, s, limit);
		res.push_back(s);
	};
	return res;
};

vector<int> User::specialDelimetedInt(string ll, char limit) {
	vector<int> res;
	stringstream s_stream(ll);

	while (s_stream.good()) {
		string s;
		getline(s_stream, s, limit);
		res.push_back(stoi(s));
	};
	return res;
};

// PUBLIC:: methods
double  User::getWorkTimeDay() {
	double result = 0.0;
	vector<int> diffResult;
	// hh mm ss
	if (this->clockInInfo.at(2) > clockOutInfo.at(2)) // sec
	{
		--clockOutInfo.at(1); // min
		clockOutInfo.at(2) += 60; //sec
	}

	diffResult.push_back(clockOutInfo.at(2) - this->clockInInfo.at(2));
	if (this->clockInInfo.at(1) > clockOutInfo.at(1))
	{
		--clockOutInfo.at(0);
		clockOutInfo.at(1) += 60;
	}
	diffResult.push_back(clockOutInfo.at(1) - this->clockInInfo.at(1));
	diffResult.push_back(clockOutInfo.at(0) - this->clockInInfo.at(0));
	result = diffResult.at(2) + (diffResult.at(1) * (1 / 60)) + (diffResult.at(0) * (1 / 3600));
	
	return result;
}

// methods for employee mger to clock in and out
void User::clockIn() {
	char str[26];
	time_t result = time(NULL);
	ctime_s(str, sizeof str, &result);
	this->clockInInfo = this->specialDelimetedInt(this->specialDelimetedString(str, ' ').at(4), ':');
	
}

void User::clockOut() {
	char str[26];
	time_t result = time(NULL);
	ctime_s(str, sizeof str, &result);
	this->clockOutInfo = this->specialDelimetedInt(this->specialDelimetedString(str, ' ').at(4), ':');
}


