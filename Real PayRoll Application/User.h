#pragma once
// import all libraries needed ========================================================================================
#include <iostream>
#include <iomanip>
#include <Math.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <sstream>
#include "AppPages.h"
using namespace std;
// ======================================================================================================================

class User{
private:
	string firstName;
	string lastName;
	string userName;
	string passWord;
	double userHourlyRate;

public:

	User(string fn, string ln);
	void setFirstName(string nf);
	void setLastName(string nl);
	void setUserName();
	void setPassWord(string np);

	//string getFirstName();
	//string getLastName();
	//string getUserName();
	//string getPassword();

	// others
	//string generatePassWord();
	string generateUserName();
};

