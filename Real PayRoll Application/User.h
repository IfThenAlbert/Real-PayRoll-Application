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

class User{
private:
	string firstName;
	string lastName;
	string userName;
	string passWord;


	vector<string>specialDelimetedString(string ll, char limit);
	vector<int>specialDelimetedInt(string ll, char limit);
	vector<int> clockInInfo;
	vector<int> clockOutInfo;
	

public:
	void setFirstName(string nfn);
	void setLastName(string nln);
	void setPassWord(string npw);
	void clockIn();
	void clockOut();


	string getFirstName();
	string getLastName();
	string getUserName();
	string getPassWord();
	double getWorkTimeDay();
	void updateField(string fromFile,string toFile);
};

