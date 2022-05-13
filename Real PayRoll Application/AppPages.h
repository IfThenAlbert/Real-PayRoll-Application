#pragma once

// import all libraries needed ========================================================================================
#include <iostream>
#include <iomanip>
#include <Math.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <windows.h>

using namespace std;
// ======================================================================================================================

class AppPages{
private:
	string appName; // this is the tag name for the class
	vector<string> currentUser;
	vector<string> commaDelimetedString(string ll,char limit); // this method is use to get values from the text file
	vector<int> commaDelimetedInt(string ll, char limit); // this method is use to get values from the text file
	vector<int> clockInInfo;
	vector<int> clockOutInfo;
	vector<int> getCurrentTime();
	void calcuteNetPay(bool isMarried);
	//vector<double> computeTimeDifference(vector<int> clockOut, vector<int> clockIn);
	double computeWorkedHours(vector<int> clockOut, vector<int> clockIn);
	//User currentUser;
public:
	AppPages(string name);
	void showMainPage();
	void showLogInPage();
	void showRegisterPage();
	void showManagerPage();
	void showOneTime();
	void showEmployeePage();
	double computeWorkedHours(vector<double> clockOut, vector<double> clockIn);
	//void updateField(string lineToChange,int pos,string data,string  fromF, string toF);
};

