#include "User.h"
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

// constructor
User::User(string fn, string ln) {
	this->firstName = fn;
	this->lastName = ln;
}

// setters
void User::setFirstName(string nf) {
	this->firstName = nf;
};

void User::setLastName(string nl) {
	this->lastName = nl;
};


string User::generateUserName() {
	string result = "";
	result = this->firstName.substr(3) + "_000";
	return result;
};

void User::setUserName() {
	this->userName = this->generateUserName();
};

void User::setPassWord(string np) {
	this->passWord = np;
};


