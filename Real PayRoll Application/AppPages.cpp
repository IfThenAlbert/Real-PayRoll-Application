#define __STDC_WANT_LIB_EXT1__ 1
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
			
			if ((userName._Equal(targetUser.at(6)) ) && (passWord._Equal(targetUser.at(7)))) {
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

			if ((userName._Equal(targetUser.at(6))) && (passWord._Equal(targetUser.at(7)))) {
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
		string employeeFirst = "";
		string employeeLast = "";
		double employeeHourlyRate = .0;
		string newEmpUser = "";
		string employeeTitle = "";
		string employeeUser = "", employeePass = "";
		int paidOption = 0;
		string marriedSingle = "";
		string vv = "";
		
		ofstream createEmployee;
		createEmployee.open("tmp_users_rpa.txt",ios::app);

		while (isFinish == 1) {
			int weekDay = 0, monthlyPayDay = 0;
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
		
			cout << "Married or Single: ";
			cin >> marriedSingle;


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
			
			// FIRST NAME, LAST NAME, MARRIED/SINGLE, TITLE, RATE, M/W, USERNAME, PASSWORD
			
			createEmployee << employeeFirst << "," << employeeLast << "," << marriedSingle << "," <<
				employeeTitle << "," << employeeHourlyRate << "," << vv << "," << employeeUser << "," << employeePass << "," << currentUser[0];
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
				//if (employeeInfo[6] == currentUser[0]) {
				//	cout << "Employee Name: " << employeeInfo[0] << " Last Name: " << employeeInfo[1] << " [" << employeeInfo[2] << "] $" << employeeInfo[3] << endl;
				//};
			};
		};
		employeeView.close();
		cout << "------------> " << endl;
		system("pause");
		this->showManagerPage();
	}
	else {
		//this->currentUser.clear();
		this->showMainPage();
	};


}

/*
	DEVELOP BY: ENMANUEL, ALBERT
	This method is to show the screen for the logged in employee
*/
void AppPages::showEmployeePage() {
	system("CLS");

	int choice = 0;
	int exitChoice = 0;
	bool isClockedIn = false;
	string passwordCheck;
	string newPassword;
	string newPasswordCheck;
	//string oldPassword = currentUser[5];


	while (choice != 1 && choice != 2) { // shows employee information
		//vector<int> cd = this->getCurrentDate();
		system("CLS");
		cout << "@@=================================================@@" << endl;
		cout << setw(35) << "Employee Page" << endl;
		cout << endl;
		cout << "\tEmployee name: " << currentUser[0] << " " << currentUser[1] << endl;
		cout << "\tEmployee title: " << currentUser[3] << endl;
		cout << "\tEmployee Hourly Wage: $" << currentUser[4] << endl;
		cout << "\tEmployee Username: " << currentUser[6] << endl;
		cout << endl;
		
		cout << "SALARY EVERY: " << currentUser[2] << " - " << currentUser[5] << endl;
		cout << "HOURS: " << stod(currentUser[9]) << endl;
		cout << "Current Gross: $" << (stod(currentUser[9]) * stod(currentUser[4])) << endl;
		cout << endl;

		cout << "(1). CLOCK IN" << endl;
		cout << "(2). VIEW PAY" << endl;
		cout << "(3). Change Password" << endl;
		cout << "(4). Quit" << endl;
		cin >> choice;
	}


	if (choice == 1) {
		this->clockInScreen();
	};

	if (choice == 2) {
		this->paySalaryScreen();
	}
	
	if (choice == 3) {
		string oldPassword = "C";

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

void AppPages::paySalaryScreen() {
	system("CLS");

	cout << "THIS SCREEN SHOWS YOUR SALARY" << endl;
	cout << "HOURS: " << currentUser[9] << endl;

	cout << "PAYMENT EVERY: ";
	if (currentUser[2] == "M") {
		cout << "MONTH => " << currentUser[5] << " of the month" << endl;
	}else {
		cout << currentUser[5] << " of the week" << endl;
	};

	cout << "SALARY DAY/DATE: " << "d" << endl;
	cout << "GROSS AS OF NOW: $" << (stod(currentUser[9]) * stod(currentUser[4])) << endl;
	

};

// =====================================================================================
void AppPages::clockInScreen() {
	system("CLS");

	time_t clockinTime;
	time_t clockOutTime;
	time(&clockinTime);

	cout << "YOU ARE NOW CLOCKED IN !!!!" << endl;
	cout << "Press any keys to clock out" << endl;
	system("pause");

	time(&clockOutTime);
	double hours = difftime(clockOutTime, clockinTime) / 3600;

	double total = hours + stod(currentUser.at(9));
	string f = "" + to_string(total);
	string employeeInfo = currentUser.at(0) + "," + currentUser.at(1) + "," + currentUser.at(2) + "," + currentUser.at(3) +
		"," + currentUser.at(4) + "," + currentUser.at(5) + "," + currentUser.at(6) + "," + currentUser.at(7) + "," + currentUser.at(8) +
		"," + currentUser.at(9);

	string newEmployeeInfo = currentUser.at(0) + "," + currentUser.at(1) + "," + currentUser.at(2) + "," + currentUser.at(3) +
		"," + currentUser.at(4) + "," + currentUser.at(5) + "," + currentUser.at(6) + "," + currentUser.at(7) + "," + currentUser.at(8) +
		"," + f;


	ifstream employeeReder;
	vector<string> archive;
	employeeReder.open("users_rpa.txt");
	string line = "";
	while (getline(employeeReder, line)) {
		if (line != employeeInfo) {
			archive.push_back(line);
		};
	};
	employeeReder.close();
	ofstream employeeReWriter;
	employeeReWriter.open("users_rpa.txt");
	for (int i = 0; i < archive.size(); i++) {
		employeeReWriter << archive.at(i) << endl;
	};
	employeeReWriter << newEmployeeInfo << endl;
	employeeReWriter.close();


	this->showEmployeePage();
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

vector<int> AppPages::getCurrentTime() {
	
	vector<int> results;
	char str[26];
	time_t result = time(NULL);
	ctime_s(str, sizeof str, &result);
	results = commaDelimetedInt(commaDelimetedString(str,' ').at(3), ':');
	return results;
}

double AppPages::computeWorkedHours(vector<int> clockOut, vector<int> clockIn) {
	int result;
	vector<int> diffResult;
	// hh mm ss
	if (clockIn.at(2) > clockOut.at(2)) // sec
	{
		--clockOut.at(1); // min
		clockOut.at(2) += 60; //sec
	}

	diffResult.push_back(clockOut.at(2) - clockIn.at(2));
	if (clockIn.at(1) > clockOut.at(1))
	{
		--clockOut.at(0);
		clockOut.at(1) += 60;
	}
	diffResult.push_back(clockOut.at(1) - clockIn.at(1));
	diffResult.push_back(clockOut.at(0) - clockIn.at(0));
	result = diffResult.at(2) +  (diffResult.at(1) * (1 / 60)) + (diffResult.at(0) * (1 / 3600));
	return result;
};

void AppPages::calcuteNetPay(bool isMarried) {
	double calculatedGross = 200.00;
	double calculatedNet = 0.0;
	double IncomePercent, incomeO;
	double FederalPercent, federalO;
	const double  SOCIALPERCENT = 0.062;
	const double  MEDICAREPERCENT = 0.0145;
	const double FAMILYLEAVE = .00511;
	const double DIS = .005;

	// logic for income tax
	if ((calculatedGross >= 0.0) && (calculatedGross <= 8500.00)) {
		IncomePercent = 0.04;
		incomeO = calculatedGross - (IncomePercent * calculatedGross);

	}
	else if ((calculatedGross >= 8501.0) && (calculatedGross <= 11700.00)) {
		IncomePercent = .045; //350 + 4.5% of  (gross - 8500 )
		incomeO = calculatedGross - (350 + (IncomePercent * (calculatedGross - 8500)));
	}
	else if ((calculatedGross >= 11701.0) && (calculatedGross <= 13900.00)) {
		IncomePercent = 0.0525; // 484 + 5.25% of (gross - 11700)
		incomeO = calculatedGross - (484 + (IncomePercent * (calculatedGross - 11700)));
	}
	else if ((calculatedGross >= 13901.0) && (calculatedGross <= 21400.00)) {
		IncomePercent = .059; // 600 + 5.9% of (gross - 13900)
		incomeO = calculatedGross - (600 + (IncomePercent * (calculatedGross - 13900)));
	}
	else if ((calculatedGross >= 21401.0) && (calculatedGross <= 80650.00)) {
		IncomePercent = .0597; // 1042 + 5.97% of (gross - 21400)
		incomeO = calculatedGross - (1042 + (IncomePercent * (calculatedGross - 21400)));
	}
	else if ((calculatedGross >= 80651.0) && (calculatedGross <= 215400.00)) {
		IncomePercent = .0633; // 4579 + 6.33% of  (gross - 80650)
		incomeO = calculatedGross - (4579 + (IncomePercent * (calculatedGross - 80650)));
	}
	else if ((calculatedGross >= 215401.0) && (calculatedGross <= 1077550.00)) {
		IncomePercent = 0.0685; // 13109 + 6.85% of (gross - 215400)
		incomeO = calculatedGross - (13109 + (IncomePercent * (calculatedGross - 215400)));
	}
	else if ((calculatedGross >= 1077550.0) && (calculatedGross <= 5000000.00)) {
		IncomePercent = .0965; // 72166 + 9.65% of  (gross - 1077550)
		incomeO = calculatedGross - (72166 + (IncomePercent * (calculatedGross - 1077550)));
	}
	else if ((calculatedGross >= 5000001.0) && (calculatedGross <= 25000000.00)) {
		IncomePercent = .1030; //  450683 + 10.30% of (gross - 5000000)
		incomeO = calculatedGross - (450683 + (IncomePercent * (calculatedGross - 5000000)));
	}
	else if ((calculatedGross >= 25000001.0)) {
		IncomePercent = .1090; // 2510683 +  10.90% of  (grss - 25000000)
		incomeO = calculatedGross - (2510683 + (IncomePercent * (calculatedGross - 25000000)));
	};

	//logic for federal tax  SINGLE
	if (isMarried == false) {
		if (calculatedGross < 10275.00) {
			FederalPercent = 0.10;
			federalO = (calculatedGross - (FederalPercent * calculatedGross));
		}
		else if ((calculatedGross > 10275.00) && (calculatedGross < 41775.00)) {
			FederalPercent = 0.12; // 995 + 12% of (gross - 9950)
			federalO = (calculatedGross - (1027.50 + (FederalPercent * (calculatedGross - 10275.00))));
		}
		else if ((calculatedGross > 41775.00) && (calculatedGross < 89075.00)) {
			FederalPercent = 0.22; // 4664 + 22% of (gross - 40525)
			federalO = (calculatedGross - (4807.50 + (FederalPercent * (calculatedGross - 41775.00))));
		}
		else if ((calculatedGross > 89075.00) && (calculatedGross < 170050.00)) {
			FederalPercent = 0.24; // 14751 + 24% of (gross - 86375)
			federalO = (calculatedGross - (15213.50 + (FederalPercent * (calculatedGross - 89075.00))));
		}
		else if ((calculatedGross > 170050.00) && (calculatedGross < 215950.00)) {
			FederalPercent = 0.32; // 33603 + 32% of  (gross - 164925)
			federalO = (calculatedGross - (34647.50 + (FederalPercent * (calculatedGross - 170050.00))));
		}
		else if ((calculatedGross > 215950.00) && (calculatedGross < 539900.00)) {
			FederalPercent = .35; // 47843 + 35% of (gross - 209425)
			federalO = (calculatedGross - (49335.50 + (FederalPercent * (calculatedGross - 215950.00))));
		}
		else {
			if (calculatedGross > 539900.00) {
				FederalPercent = .37; // 157804.25 +  37% of (gross - 523600)
				federalO = (calculatedGross - (162718.00 + (FederalPercent * (calculatedGross - 539900.00))));
			};
		};
	}


	// MARRIED
	if (isMarried) {
		if (calculatedGross < 10275.00) {
			FederalPercent = 0.10;
			federalO = (calculatedGross - (FederalPercent * calculatedGross));
		}
		else if ((calculatedGross > 10275.00) && (calculatedGross < 41775)) {
			FederalPercent = 0.12; // 995 + 12% of (gross - 9950)
			federalO = (calculatedGross - (1027.50 + (FederalPercent * (calculatedGross - 10275.00))));
		}
		else if ((calculatedGross > 41775.00) && (calculatedGross < 89075.00)) {
			FederalPercent = 0.22; // 4664 + 22% of (gross - 40525)
			federalO = (calculatedGross - (4807.50 + (FederalPercent * (calculatedGross - 41775.00))));
		}
		else if ((calculatedGross > 89075) && (calculatedGross < 170050)) {
			FederalPercent = 0.24; // 14751 + 24% of (gross - 86375)
			federalO = (calculatedGross - (15213.50 + (FederalPercent * (calculatedGross - 89075))));
		}
		else if ((calculatedGross > 170050.00) && (calculatedGross < 215950.00)) {
			FederalPercent = 0.32; // 33603 + 32% of  (gross - 164925)
			federalO = (calculatedGross - (34647.50 + (FederalPercent * (calculatedGross - 170050))));
		}
		else if ((calculatedGross > 215950.00) && (calculatedGross < 323925.00)) {
			FederalPercent = .35; // 47843 + 35% of (gross - 209425)
			federalO = (calculatedGross - (49335.50 + (FederalPercent * (calculatedGross - 215950.00))));
		}
		else {
			if (calculatedGross > 323925.00) {
				FederalPercent = .37; // 157804.25 +  37% of (gross - 523600)
				federalO = (calculatedGross - (86127.00 + (FederalPercent * (calculatedGross - 323925.00))));
			};
		};
	}

	double ss = calculatedGross - (calculatedGross * SOCIALPERCENT);
	double mm = (calculatedGross * MEDICAREPERCENT);
	double nfl = calculatedGross - (calculatedGross * FAMILYLEAVE);
	double dd = calculatedGross - (calculatedGross * DIS);
	double tax = IncomePercent + FederalPercent + SOCIALPERCENT + MEDICAREPERCENT + FAMILYLEAVE + DIS;
	calculatedNet = calculatedGross - (calculatedGross * tax);

}