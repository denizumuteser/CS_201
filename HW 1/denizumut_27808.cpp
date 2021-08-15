#include <iostream>
#include <string>
using namespace std;

int main()
{
	string studentName, courseName, firstTime, currentGrade, previousGrade, desiredGrade, yesNo;
	
	cout << "Welcome to the Fall 2020-2021 Semester grading system. What is your name? ";
	cin >> studentName;
	cout << "Hello " << studentName << "! Please enter the name of the course to be processed: ";
	cin >> courseName;
	cout << "Hello " << studentName << "! If you take the " << courseName << " for the first time, enter YES otherwise NO: ";
	cin >> firstTime;
	if (firstTime == "YES")
	{
		cout << "What is your grade from (A,B,C,D,F)? ";
		cin >> currentGrade;
		if (currentGrade == "A" || currentGrade == "B" || currentGrade == "C" || currentGrade == "D")
		{
			cout << "Do you want to switch your grade from " << currentGrade << " to S (YES or NO)? ";
			cin >> yesNo;
			if (yesNo == "YES")
			{
				desiredGrade = "S";
			}
			else if (yesNo == "NO")
			{
				desiredGrade = currentGrade;
			}
			else
			{
				cout << "Invalid grade selection. Goodbye..." << endl;
				return 0;
			}
		}
		else if (currentGrade == "F")
		{
			cout << "Do you want to switch your grade from " << currentGrade << " to U (YES or NO)? ";
			cin >> yesNo;
			if (yesNo == "YES")
			{
				desiredGrade = "U";
			}
			else if (yesNo == "NO")
			{
				desiredGrade = currentGrade;
			}
			else
			{
				cout << "Invalid grade selection. Goodbye..." << endl;
				return 0;
			}
		}
		else
		{
			cout << "Invalid grade selection. Goodbye..." << endl;
			return 0;
		}
	}
	else if (firstTime == "NO")
	{
		cout << "Please enter your previous grade from (A,B,C,D,F,S,U): ";
		cin >> previousGrade;
		if (previousGrade != "A" && previousGrade != "B" && previousGrade != "C" && previousGrade != "D" && previousGrade != "F" && previousGrade != "S" && previousGrade != "U")
		{
			cout << "Invalid grade selection. Goodbye..." << endl;
			return 0;
		}
		cout << "Please enter your current grade from (A,B,C,D,F): ";
		cin >> currentGrade;
		if (currentGrade != "A" && currentGrade != "B" && currentGrade != "C" && currentGrade != "D" && currentGrade != "F" && currentGrade != "S" && currentGrade != "U")
		{
			cout << "Invalid grade selection. Goodbye..." << endl;
			return 0;
		}
		cout << "Please enter the grade you want to choose from (A,B,C,D,F,S,U): ";
		cin >> desiredGrade;
		//conditions
		if (previousGrade == "F" && currentGrade == "F" && desiredGrade != "F")
		{
			cout << "Invalid grade selection. If you received F before, and fail this semester, you get F." << endl;
			return 0;
		}
		else if (previousGrade == "S" && currentGrade == "F" && desiredGrade != "F")
		{
			cout << "Invalid grade selection. If you received S before and fail this semester, you get F." << endl;
			return 0;
		}
		else if (previousGrade == "U" && (currentGrade == "A" || currentGrade == "B" || currentGrade == "C" || currentGrade == "D") && desiredGrade != "S" && desiredGrade != currentGrade)
		{
			cout << "Invalid grade selection. If you received U before, you may choose S or current letter grade." << endl;
			return 0;
		}
		else if ((currentGrade == "A" || currentGrade == "B" || currentGrade == "C" || currentGrade == "D") && desiredGrade == "U")
		{
			cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve." << endl;
			return 0;
		}
		else if (currentGrade == "F" && desiredGrade == "S")
		{
			cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve." << endl;
			return 0;
		}

		if (desiredGrade != currentGrade && desiredGrade != "S" && desiredGrade != "U")
		{
			cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve." << endl;
			return 0;
		}
	}
	else
	{
		return 0;
	}
	//final output
	cout << studentName << ", your final grade for " << courseName << " is " << desiredGrade << ". Goodbye..." << endl;
	return 0;
}



