#pragma once

// import all libraries needed ========================================================================================
#include <iostream>
#include <iomanip>
#include <Math.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
// ======================================================================================================================

class AppPages{
private:
	string appName; // this is the tag name for the class
	vector<string> currentUser;
	vector<string> commaDelimetedString(string ll); // this method is use to get values from the text file 
public:
	AppPages(string name);
	void showMainPage();
	void showLogInPage();
	void showRegisterPage();
	void showManagerPage();
	void showOneTime();
	void showEmployeePage();
};

