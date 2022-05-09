#include "CalculateMeDateTime.h"

string CalculateMeDateTime::getCurrentDateTime() {
	char str[26];
	time_t result = time(NULL);
	ctime_s(str, sizeof str, &result);
	return str;
}

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

        if (monthFirst == month2)
        {
            if (day1 == day2)      //for same month, same day but diff year
                return temp;
            else if (day1 < day2)
                return temp + (day2 - day1);
            else
                return temp - (day1 - day2);
        }
        else if (month1 < month2)
        {
            int result = 0;
            for (int i = month1; i < month2; i++)
                result = result + no_of_days_in_month(i, year2);

            if (day1 == day2)      // for same day, diff year and diff month
                return temp + result;
            else if (day1 < day2)
            {
                result = result + (day2 - day1);
                return temp + result;
            }
            else
            {
                result = result - (day1 - day2);
                return temp + result;
            }
        }
        else
        {
            int result = 0;
            for (int i = month2; i < month1; i++)
                result = result + no_of_days_in_month(i, year2);

            if (day1 == day2)
                return temp - result;
            else if (day2 < day1)
            {
                result = result + (day1 - day2);
                return temp - result;
            }
            else
            {
                result = result - (day2 - day1);
                return temp - result;
            }
        }
    }
    else
    {
        int temp = 0;
        for (int i = year2; i < year1; i++)
        {
            if (check_leap_year(i))
                temp = temp + 366;
            else
                temp = temp + 365;
        }

        if (month1 == month2)
        {
            if (day1 == day2)      // for same day, same month but diff year
                return temp;
            else if (day2 < day1)
                return temp + (day1 - day2);
            else
                return temp - (day2 - day1);
        }
        else if (month2 < month1)
        {
            int result = 0;
            for (int i = month2; i < month1; i++)
                result = result + no_of_days_in_month(i, year1);

            if (day1 == day2)
                return temp + result;
            else if (day2 < day1)
            {
                result = result + (day1 - day2);
                return temp + result;
            }
            else
            {
                result = result - (day2 - day1);
                return temp + result;
            }
        }
        else
        {
            int result = 0;
            for (int i = month1; i < month2; i++)
                result = result + no_of_days_in_month(i, year1);

            if (day1 == day2)      // for same day, diff year and diff month
                return temp - result;
            else if (day1 < day2)
            {
                result = result + (day2 - day1);
                return temp - result;
            }
            else
            {
                result = result - (day1 - day2);
                return temp - result;
            }
        }
    }
	};
}