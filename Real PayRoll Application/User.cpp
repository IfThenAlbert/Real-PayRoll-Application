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
User::User(const User &uu) {
	this->firstName = uu.firstName;
	this->lastName = uu.lastName;
	this->mariedSingle = uu.mariedSingle;
	this->title = uu.title;
	this->hourlyRate = uu.hourlyRate;
	this->monthlyWeeklyOption = uu.monthlyWeeklyOption;
	this->userName = uu.userName;
	this->passWord = uu.passWord;
	this->managerBy = uu.managerBy;

};
User::User(string username,string pass) {
	// open the file that contains all the user credentials
	ifstream userFilesReader;
	ifstream employeeFilesReader;

	userFilesReader.open("users_rpa.txt");
	employeeFilesReader.open("tmp_users_rpa.txt");

	if (userFilesReader.is_open()) {
		string lined; // store the value of each line


		while (getline(userFilesReader, lined)) {
			vector<string> targetUser = this->specialDelimetedString(lined, ',');// store all the user creds here

			if ((username._Equal(targetUser.at(6))) && (pass._Equal(targetUser.at(7)))) {
				//this->currentUser = targetUser;
				this->firstName = targetUser.at(0);
				this->lastName = targetUser.at(1);
				this->mariedSingle = targetUser.at(2)[0];
				this->title = targetUser.at(3);
				this->hourlyRate = stod(targetUser.at(4));
				this->monthlyWeeklyOption = targetUser.at(5)[0];
				this->userName = targetUser.at(6);
				this->passWord = targetUser.at(7);
				this->managerBy = targetUser.at(8);

				if (this->title == "manager") {
					//this->showManagerPage();
					this->setRedirectTo("managerpage");
					return;
				}
				else {
					//this->showEmployeePage();
					this->setRedirectTo("employeepage");
					return;
				};
				return;
			};
		};

		while (getline(employeeFilesReader, lined)) {
			vector<string> targetUser = this->specialDelimetedString(lined, ',');  // store all the user creds here

			if ((username._Equal(targetUser.at(6))) && (pass._Equal(targetUser.at(7)))) {
				//this->currentUser = targetUser;

				this->firstName = targetUser[0];
				this->lastName = targetUser[1];
				this->mariedSingle = targetUser[2][0];
				this->title = targetUser[3];
				this->hourlyRate = stod(targetUser[4]);
				this->monthlyWeeklyOption = targetUser[5][0];
				this->userName = targetUser[6];
				this->passWord = targetUser[7];
				this->managerBy = targetUser[8];

				if (passWord == "app123") {
					//this->showOneTime();
					this->setRedirectTo("onetime");
					return;
				};
			};

		};
		//this->showMainPage();
		this->setRedirectTo("mainpage");
	};
}


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

void User::setRedirectTo(string scrr) {
	this->redirectTo = scrr;
}

string User::getRedirectTo() {
	return this->redirectTo;
};

double User::getNetPay() {
	double calculatedGross = 0;

	double FederalPercent;
	double federalO;
	double IncomePercent;
	double incomeO;
	const double  SOCIALPERCENT = 0.062; // 6.2%% 
	const double  MEDICAREPERCENT = 0.0145; // 1.45%
	const double FAMILYLEAVE = .00511; //.511%
	const double DIS = .005; // .5%

	double totalTax = 0.0;

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
	if (this->mariedSingle == 'S') {
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
	}else {
		if (calculatedGross < 10275.00) {
			FederalPercent = 0.10;
			federalO = (calculatedGross - (FederalPercent * calculatedGross));
		}else if ((calculatedGross > 10275.00) && (calculatedGross < 41775)) {
			FederalPercent = 0.12; // 995 + 12% of (gross - 9950)
			federalO = (calculatedGross - (1027.50 + (FederalPercent * (calculatedGross - 10275.00))));
		}else if ((calculatedGross > 41775.00) && (calculatedGross < 89075.00)) {
			FederalPercent = 0.22; // 4664 + 22% of (gross - 40525)
			federalO = (calculatedGross - (4807.50 + (FederalPercent * (calculatedGross - 41775.00))));
		}else if ((calculatedGross > 89075) && (calculatedGross < 170050)) {
			FederalPercent = 0.24; // 14751 + 24% of (gross - 86375)
			federalO = (calculatedGross - (15213.50 + (FederalPercent * (calculatedGross - 89075))));
		}else if ((calculatedGross > 170050.00) && (calculatedGross < 215950.00)) {
			FederalPercent = 0.32; // 33603 + 32% of  (gross - 164925)
			federalO = (calculatedGross - (34647.50 + (FederalPercent * (calculatedGross - 170050))));
		}else if ((calculatedGross > 215950.00) && (calculatedGross < 323925.00)) {
			FederalPercent = .35; // 47843 + 35% of (gross - 209425)
			federalO = (calculatedGross - (49335.50 + (FederalPercent * (calculatedGross - 215950.00))));
		}else {
			if (calculatedGross > 323925.00) {
				FederalPercent = .37; // 157804.25 +  37% of (gross - 523600)
				federalO = (calculatedGross - (86127.00 + (FederalPercent * (calculatedGross - 323925.00))));
			};
		};
	};

	totalTax = IncomePercent + FederalPercent + SOCIALPERCENT + MEDICAREPERCENT + FAMILYLEAVE + DIS;
	return  calculatedGross - (calculatedGross * totalTax);

}


