#include "CalculateMeDateTime.h"

string CalculateMeDateTime::getCurrentDateTime() {
	char str[26];
	time_t result = time(NULL);
	ctime_s(str, sizeof str, &result);
	return str;
}



int CalculateMeDateTime::check_leap_year(int year) {
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
        return 1;
    };//if year is a leap year
    return 0;
};

int CalculateMeDateTime::no_of_days_in_month(int month, int year) {
    // jan, march, may, july, aug, oct, dec contains 31 days
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        return 31;

    // april, jun, sept, nov contains 30 days
    if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;

    if (month == 2)
    {
        int n = check_leap_year(year);
        if (n == 1)    // if year is a leap year then Feb will contain 29 days, otherwise it contains 28 days
            return 29;

        else
            return 28;
    }


    return 0;
};

long CalculateMeDateTime::getDifference(int monthFirst, int dayFirst, int yearFirst, int monthSecond, int daySecond, int yearSecond) {
	int result = 0; // hold the difference
    if (yearFirst == yearSecond)
    {
        if (monthFirst == monthSecond)
        {
            if (dayFirst == daySecond)      //for same dates
                return 0;
            else
                return abs(dayFirst - daySecond);  //for same year, same month but diff days
        }
        else if (monthFirst < monthSecond)
        {
            int result = 0;
            for (int i = monthFirst; i < monthSecond; i++)
                result = result + no_of_days_in_month(i, yearFirst);

            if (dayFirst == daySecond)      //for same year, same day but diff month 
                return result;
            else if (dayFirst < daySecond)
            {
                result = result + (daySecond - dayFirst);
                return result;
            }
            else
            {
                result = result - (dayFirst - daySecond);
                return result;
            }
        }
        else
        {
            int result = 0;
            for (int i = monthSecond; i < monthFirst; i++)
                result = result + no_of_days_in_month(i, yearFirst);

            if (dayFirst == daySecond)
                return result;
            else if (daySecond < dayFirst)
            {
                result = result + (dayFirst - daySecond);
                return result;
            }
            else
            {
                result = result - (daySecond - dayFirst);
                return result;
            }
        }
    }
    else if (yearFirst < yearSecond)
    {
        int temp = 0;
        for (int i = yearFirst; i < yearSecond; i++)
        {
            if (check_leap_year(i))
                temp = temp + 366;
            else
                temp = temp + 365;
        }

        if (monthFirst == monthSecond)
        {
            if (dayFirst == daySecond)      //for same month, same day but diff year
                return temp;
            else if (dayFirst < daySecond)
                return temp + (daySecond - dayFirst);
            else
                return temp - (dayFirst - daySecond);
        }
        else if (monthFirst < monthSecond)
        {
            int result = 0;
            for (int i = monthFirst; i < monthSecond; i++)
                result = result + no_of_days_in_month(i, yearSecond);

            if (dayFirst == daySecond)      // for same day, diff year and diff month
                return temp + result;
            else if (dayFirst < daySecond)
            {
                result = result + (daySecond - dayFirst);
                return temp + result;
            }
            else
            {
                result = result - (dayFirst - daySecond);
                return temp + result;
            }
        }
        else
        {
            int result = 0;
            for (int i = monthSecond; i < monthFirst; i++)
                result = result + no_of_days_in_month(i, yearSecond);

            if (dayFirst == daySecond)
                return temp - result;
            else if (daySecond < dayFirst)
            {
                result = result + (dayFirst - daySecond);
                return temp - result;
            }
            else
            {
                result = result - (daySecond - dayFirst);
                return temp - result;
            }
        }
    }
    else
    {
        int temp = 0;
        for (int i = yearSecond; i < yearFirst; i++)
        {
            if (check_leap_year(i))
                temp = temp + 366;
            else
                temp = temp + 365;
        }

        if (monthFirst == monthSecond)
        {
            if (dayFirst == daySecond)      // for same day, same month but diff year
                return temp;
            else if (daySecond < dayFirst)
                return temp + (dayFirst - daySecond);
            else
                return temp - (daySecond - dayFirst);
        }
        else if (monthSecond < monthFirst)
        {
            int result = 0;
            for (int i = monthSecond; i < monthFirst; i++)
                result = result + no_of_days_in_month(i, yearFirst);

            if (dayFirst == daySecond)
                return temp + result;
            else if (daySecond < dayFirst)
            {
                result = result + (dayFirst - daySecond);
                return temp + result;
            }
            else
            {
                result = result - (daySecond - dayFirst);
                return temp + result;
            }
        }
        else
        {
            int result = 0;
            for (int i = monthFirst; i < monthSecond; i++)
                result = result + no_of_days_in_month(i, yearFirst);

            if (dayFirst == daySecond)      // for same day, diff year and diff month
                return temp - result;
            else if (dayFirst < daySecond)
            {
                result = result + (daySecond - dayFirst);
                return temp - result;
            }
            else
            {
                result = result - (dayFirst - daySecond);
                return temp - result;
            }
        }
    }
}