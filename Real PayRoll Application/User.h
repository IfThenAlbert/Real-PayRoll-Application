#pragma once
// import all libraries needed ========================================================================================
#include <iostream>
#include <iomanip>
#include <Math.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <sstream>
#include "User.h"
using namespace std;
// ======================================================================================================================

class User{
private:
	string firstName;
	string lastName;
	char mariedSingle;
	string title;
	double hourlyRate;
	char monthlyWeeklyOption;
	string userName;
	string passWord;
	string managerBy;

	vector<int> clockInInfo;
	vector<int> clockOutInfo;

	string redirectTo;
	vector<string>specialDelimetedString(string ll, char limit);
	vector<int>specialDelimetedInt(string ll, char limit);
	

public:
	User(string username,string pass);
	User(const User &uu);
	User();
	void setFirstName(string nfn);
	void setLastName(string nln);
	void setPassWord(string npw);
	void setRedirectTo(string scrr);
	void clockIn();
	void clockOut();

	double getNetPay(); // This method contains all tax info from NEW YORK CITY ONLY
	double calculateGross();
	string getFirstName();
	string getLastName();
	string getUserName();
	string getPassWord();

	string getRedirectTo();
	double getWorkTimeDay();
	void updateField(string fromFile,string toFile);
};

