#include <iostream>
#include <iomanip>
#include <string>
#include "strutils.h"
using namespace std;

bool check_input(string color, double width, double height, double length) {
	if (width > 0 && height > 0 && length > 0) {
		return true;
	}
	else {
		cout << "Invalid entry for " << color << " cuboid. Dimensions should be positive real numbers!" << endl;
		return false;
	}
}

void checkCubeandDisplay(string color, double width, double height, double length) {
	if (width == height && width == length && height == length) {
		cout << color << " cuboid is a cube." << endl;
	}
	else {
		cout << color << " cuboid is not a cube." << endl;
	}
	cout << endl;
}

void display(string color, double area, double volume) {
	cout << "Results for the " << color << " cuboid:" << endl;
	cout << "Area: " << area << endl;
	cout << "Volume: " << volume << endl;
}

void calculate(string color, double width, double height, double length, double &area, double &volume) {
	area = (2 * (height * width + width * length + height * length));
	volume = (height * width * length);
	display(color, area, volume);
	checkCubeandDisplay(color, width, height, length);
}	

string compare(string desiredMetric, string color1, string color2, double metric1, double metric2) {
	if (metric1 > metric2) {
		return color1 + " has the largest " + desiredMetric + ".";
	}
	else if (metric1 == metric2) {
		return "Two cuboids have the same " + desiredMetric + ".";
	}
	else {
		return color2 + " has the largest " + desiredMetric + ".";
	}
}

int main() {
	cout.setf(ios::fixed);
	cout.precision(2);
	double length1, length2, width1, width2, height1, height2, area1, area2, volume1, volume2;
	string color1, color2, temp1, temp2;


	cout << "Hello! This program compares two cuboids..." << endl;
	cout << "Please enter colors for the two cuboids: ";
	cin >> color1 >> color2;
	
	
	if (LowerString(color1) == LowerString(color2)) {
		cout << "Color names cannot be the same, good bye..." << endl;
		return 0;
	}
	

	cout << "Please enter length, width and height of the " << color1 << " cuboid: ";
	cin >> length1 >> width1 >> height1;
	if (check_input(color1, width1, height1, length1) == false) {
		return 0;
	}
	cout << "Please enter length, width and height of the " << color2 << " cuboid: ";
	cin >> length2 >> width2 >> height2;
	if (check_input(color2, width2, height2, length2) == false) {
		return 0;
	}

	calculate(color1, width1, height1, length1, area1, volume1);
	calculate(color2, width2, height2, length2, area2, volume2);
	
	cout << "Comparison of the two cuboids:" << endl;
	cout << compare("volume", color1, color2,volume1, volume2) << endl;
	cout << compare("area", color1, color2, area1, area2) << endl;

	return 0;
}