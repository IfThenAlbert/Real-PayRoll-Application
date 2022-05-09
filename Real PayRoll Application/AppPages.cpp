#include "AppPages.h"
// import all libraries needed ========================================================================================
#include <iostream>
#include <iomanip>
#include <Math.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <Windows.h>
#include "User.h"

using namespace std;
// ======================================================================================================================

AppPages::AppPages(string name) {
	this->appName = name;
	this->showMainPage();
};

// this  screen is for the main screen
void AppPages::showMainPage() {
	int userChoice = 0;
	
	while (userChoice <1 || userChoice > 2) {
		system("CLS");
		cout << "@@=================================================@@" << endl;
		cout << setw(35) << this->appName << endl;
		cout << "(1): LogIn" << endl;
		
		cout << "(2): Register" << endl;
		
		cin >> userChoice;
		cout << "" << endl;
	}
	
	system("CLS");
	if (userChoice == 1) {
		this->showLogInPage();
	}else {
		this->showRegisterPage();
	}
};

// this screen is for the login screen
void AppPages::showLogInPage() {
	
	// gather all data from user logging in
	string userName;
	string passWord;

	// open the file that contains all the user credentials
	ifstream userFilesReader;
	ifstream employeeFilesReader;

	userFilesReader.open("users_rpa.txt");
	employeeFilesReader.open("tmp_users_rpa.txt");

	cout << "@@=================================================@@" << endl;
	cout << setw(35) << this->appName << " LOGIN" << endl;
	
	cout << "Username: ";
	cin >> userName;
	cout << "Password: ";
	cin >> passWord;

	system("CLS");
	if (userFilesReader.is_open()) {
		string lined; // store the value of each line


		while (getline(userFilesReader, lined)) {
			vector<string> targetUser = this->commaDelimetedString(lined,',');  // store all the user creds here
			
			if ((userName._Equal(targetUser.at(4)) ) && (passWord._Equal(targetUser.at(5)))) {
				this->currentUser = targetUser;


				if (targetUser.at(2) == "manager") {
					this->showManagerPage();
				}else {
					this->showEmployeePage();
				};
				return;
			};
		};

		while (getline(employeeFilesReader, lined)) {
			vector<string> targetUser = this->commaDelimetedString(lined,',');  // store all the user creds here

			if ((userName._Equal(targetUser.at(4))) && (passWord._Equal(targetUser.at(5)))) {
				this->currentUser = targetUser;
				if (passWord == "app123") {
					this->showOneTime();
					return;
				};
			};

		};
		this->showMainPage();
	};

};

// this screen is for first time employee login
void AppPages::showOneTime() {
	vector<string> archive;
	string passy = "app123";
	string lineToChange = this->currentUser[0] + "," + this->currentUser[1] + "," + this->currentUser[2] + "," +
		this->currentUser[3] + "," + this->currentUser[4] + "," + this->currentUser[5] + "," + this->currentUser[6];
	string newData = this->currentUser[0] + "," + this->currentUser[1] + "," + this->currentUser[2] + "," +
		this->currentUser[3] + "," + this->currentUser[4] + ",";
	string line = "";
	ofstream usersFile;
	ofstream temporaryFileWrite;

	ifstream temporaryFile;

	// opens the text file that contains all users creds (users_rpa.txt) to add the change password
	usersFile.open("users_rpa.txt",ios::app);

	// opens temporary text file to read whats in it
	temporaryFile.open("tmp_users_rpa.txt");

	// opens the text file that will be use to change values
	temporaryFileWrite.open("tmp_users_rpa.txt");

	// ask user to change password
	while (passy == "app123") {
		system("CLS");
		cout << "@@=================================================@@" << endl;
		cout << this->currentUser[0] << " please create your own password." << endl;
		cout << "Create Password: ";
		cin >> passy;
	};

	// add the new password to the new data
	newData += passy + "," + this->currentUser[6];

	// store all old infos to vector except for the line we are changing
	while (getline(temporaryFile, line)) {
		if (line != lineToChange) {
			archive.push_back(line);
		};
	};
	temporaryFile.close();

	// check the temporaary infos
	if (archive.size() <= 0) {
		temporaryFileWrite << "";
	}else {
		for (int i = 0; i < archive.size(); i++) {
			temporaryFileWrite << archive.at(i) << endl;
		};
	};

	usersFile << newData << endl;
	this->showMainPage();

}

// this screen is for the register screen
void AppPages::showRegisterPage() {
	string nManagerFirst, nManagerLast, nManagerUser, nManagerPass,dummy;
	double hourlyPay;
	ofstream generalManagerWriter;
	generalManagerWriter.open("users_rpa.txt",ios::app);

	cout << "@@=================================================@@" << endl;
	cout << "NOTE: ONLY MANAGERS CAN REGISTER " << endl;
	cout << "\n";
	cout << "Please enter your first name: ";
	cin >> nManagerFirst;
	cout << "Please enter your last name: ";
	cin >> nManagerLast;
	cout << "Create a username: ";
	cin >> nManagerUser;
	cout << "Create a password: ";
	cin >> nManagerPass;

	cout << "Hourly pay: ";
	cin >> hourlyPay;


	system("CLS");
	if (generalManagerWriter.is_open()) {
		generalManagerWriter << nManagerFirst << "," << nManagerLast << "," << "manager," << hourlyPay << "," << nManagerUser << ","
			<< nManagerPass << ",M123M" << endl;
		cout << "YOU ARE NOW REGISTERED !!!" << endl;
		system("pause");
		this->showMainPage();
	};
	
	 
}

// this screeen is for the logged in manager screen
void AppPages::showManagerPage() {
	int managerChoice = 0;
	string dummy;

	while (managerChoice < 1 || managerChoice > 3) {
		system("CLS");
		cout << "@@=================================================@@" << endl;
		cout << setw(35) << currentUser[0] << endl;
		cout << "(1): ADD EMPLOYEE" << endl;
		cout << "(2): VIEW MY EMPLOYEES" << endl;
		cout << "(3): LOG OUT" << endl;
		cin >> managerChoice;
		cout << "" << endl;
	};

	system("CLS");
	if (managerChoice == 1) {
		int isFinish = 1;
		string employeeFirst;
		string employeeLast;
		double employeeHourlyRate;
		string newEmpUser = "";
		string employeeTitle;
		string employeeUser, employeePass;
		int paidOption;
		string vv;
		
		ofstream createEmployee;
		createEmployee.open("tmp_users_rpa.txt",ios::app);

		while (isFinish == 1) {
			int weekDay, monthlyPayDay;
			system("CLS");
			cout << "@@=================================================@@" << endl;
			cout << setw(35) << "ADD NEW EMPLOYEE" << endl;
			cout << "First name: ";
			cin >> employeeFirst;

			cout << "Last name: ";
			cin >> employeeLast;

			//cout << "Create username for this employee: ";
			//cin >> employeeUser;
			employeeUser = employeeFirst + employeeLast;
			cout << "Employee Username: " << employeeUser << endl; 
			cout << "Temporrary Log In Password: app123" << endl;
			employeePass = "app123";

			cout << "Employee Title: ";
			cin >> employeeTitle;


			cout << "Hourly rate ($ per hour): $";
			cin >> employeeHourlyRate;

			while (paidOption > 2 || paidOption < 1) {
				cout << "Weekly = 1 / Monthly = 2";
				cin >> paidOption;
			}


			if (paidOption == 1) {
				while (weekDay > 7 || weekDay < 1) {
					cout << "Enter day this employee will get paid (monday 1 - sunday 7)";
					cin >> weekDay;
				}

			}else {
				while (monthlyPayDay < 1 || monthlyPayDay > 30 ) {
					cout << "Enter date this employee will get paid 1 - 30)";
					cin >> monthlyPayDay;
				}
			};

			if (weekDay != 0) {
				vv = weekDay;
			}else {
				vv = monthlyPayDay;
			};

			cout << "@@=================================================@@" << endl;
			cout << "enter 1 to edit or enter 0 to add this employee: ";
			cin >> isFinish;
		};



		if (createEmployee.is_open()) {
			// Manager under,First,Last,hourly,username,password
			
			createEmployee << employeeFirst << "," << employeeLast << "," << employeeTitle << "," <<
				employeeHourlyRate << "," << paidOption << "," << vv << "," << employeeUser << "," << employeePass << "," << this->currentUser[0] << endl;
			createEmployee.close();
			system("CLS");
			cout << "AN EMPLOYEE HAS BEEN ADDED!!!" << endl;
			system("pause");
			this->showManagerPage();
		};

	}else if (managerChoice ==2) {
		ifstream employeeView;
		employeeView.open("tmp_users_rpa.txt");

		if (employeeView.is_open()) {
			string data;
			while (getline(employeeView, data)) {
				vector<string> employeeInfo = commaDelimetedString(data,',');
				if (employeeInfo[6] == currentUser[0]) {
					cout << "Employee Name: " << employeeInfo[0] << " Last Name: " << employeeInfo[1] << " [" << employeeInfo[2] << "] $" << employeeInfo[3] << endl;
				};
			};
		};
		employeeView.close();
		cout << "------------> " << endl;
		system("pause");
		this->showManagerPage();
	}
	else {
		this->currentUser.clear();
		this->showMainPage();
	};


}

/*
	DEVELOP BY: ENMANUEL, ALBERT
	This method is to show the screen for the logged in employee
*/
void AppPages::showEmployeePage() { 

	int choice = 0;
	int exitChoice = 0;
	bool isClockedIn = false;
	string passwordCheck;
	string newPassword;
	string newPasswordCheck;
	string oldPassword = currentUser[5];


	while (choice != 1 && choice != 2) { // shows employee information
		vector<int> cd = this->getCurrentDate();
		system("CLS");
		cout << "@@=================================================@@" << endl;
		cout << setw(35) << "Employee Page" << endl;
		cout << endl;
		cout << "\tEmployee name: " << currentUser[0] << " " << currentUser[1] << endl;
		cout << "\tEmployee title: " << currentUser[2] << endl;
		cout << "\tEmployee Hourly Wage: $" << currentUser[3] << endl;
		cout << "\tEmployee Username: " << currentUser[4] << endl;
		cout << endl;
		cout << endl;

		cout << "(1). CLOCK IN" << endl;
		cout << "(2). CLOCK OUT" << endl;
		

		cout << "(3). Change Password" << endl;
		cout << "(4). Quit" << endl;
		cin >> choice;
	}


	if (choice == 1) {
		this->clockInInfo = getCurrentDate(); //commaDelimetedInt(commaDelimetedString(str, ' ').at(4), ':');
		isClockedIn = true;
	};

	if (choice == 2) {
		if (isClockedIn != false) {
			this->clockOutInfo = getCurrentDate();
			double earnedTHisShift = stod(currentUser[3]) * 5;
			
			isClockedIn = false;
		};
	};

	if (choice == 3) {


		do { // changing password algorithm
			system("CLS");
			cout << "Enter old password: ";
			cin >> passwordCheck;

			if (passwordCheck.compare(oldPassword) != 0) {

				cout << "Passwords do not match, try again." << endl;
				cout << endl;
				system("pause");
			}

		} while (passwordCheck.compare(oldPassword) != 0);



		do {

			cout << endl;
			cout << "Enter new password: ";
			cin >> newPassword;

			cout << "Re-enter new password: ";
			cin >> newPasswordCheck;

			if (newPassword.compare(newPasswordCheck) != 0) {
				cout << "Passwords do not match, try again." << endl;
				cout << endl;
				system("pause");
			}

			if (newPassword.compare(oldPassword) == 0) {
				cout << "New password cannot be the same as the old!" << endl;
				cout << endl;
				system("pause");
			}

		} while (newPassword.compare(newPasswordCheck) != 0 && newPassword.compare(oldPassword) == 0);

		cout << "Passwords have been changed! Don't forget it!" << endl;
		this->showEmployeePage();
	}

	if (choice == 4) { // exit choice

		cout << "Are you sure you want to exit?" << endl;
		cout << "(1). Yes" << endl;
		cout << "(2). No" << endl;
		cin >> exitChoice;

		if (exitChoice == 1) {
			this->showMainPage();
		}
		if (exitChoice == 2) {
			this->showEmployeePage();
		}

	};
};


// <OTHERS> 
vector<string> AppPages::commaDelimetedString(string ll, char limit) {
	vector<string> res;
	stringstream s_stream(ll);

	while (s_stream.good()) {
		string s;
		getline(s_stream, s, limit);
		res.push_back(s);
	};
	return res;
};

vector<int> AppPages::commaDelimetedInt(string ll, char limit) {
	vector<int> res;
	stringstream s_stream(ll);

	while (s_stream.good()) {
		string s;
		getline(s_stream, s, limit);
		res.push_back(stoi(s));
	};
	return res;
};

vector<int> AppPages::getCurrentDate() {
	vector<int> results;
	char str[26];
	time_t result = time(NULL);
	ctime_s(str, sizeof str, &result);
	results = commaDelimetedInt(commaDelimetedString(str,' ').at(4), ':');
}


void AppPages::updateField(string lineToChange, int pos, string data, string  fromF, string toF) {

};