#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct TVseries {
	string name, actor;
	double rating = 0;
	int count = 0;
};

int validName(vector<TVseries> & v, vector<TVseries> & f, string name) {
	
	for (int i = 0; i < f.size(); i++) {
		if (f[i].name == name) {
			return -2;
		}
	}
	
	
	for (int i = 0; i < v.size(); i++) {
		if (v[i].name == name) {
			return i;
		}
		
	}
	return -1;
}

void vectorSort(vector<TVseries> & v) {
	int k, j, maxIndex;
	TVseries temp;
	for (k = 0; k < v.size() - 1; k++) {
		maxIndex = k;
		for (j = k+1; j < v.size(); j++) {
			if (v[j].rating > v[maxIndex].rating) {
				maxIndex = j;
			}
			else if (v[j].rating == v[maxIndex].rating) {

				if (v[j].name < v[maxIndex].name) {
					maxIndex = j;
				}
			}
		}
		temp = v[k];
		v[k] = v[maxIndex];
		v[maxIndex] = temp; 
	}
}

string toUpper (const string& s) {
	string result = "";
	char c;
	unsigned long len = s.length();

	for (int i = 0; i < len; i++) {
		c = s.at(i);
		if (c >= 'a' && c <= 'z') {
			c = ('A' - 'a') + c;
		}
		result = result + c;
	}
	return result;
}

void printVector(vector<TVseries> v, double min) {
	cout << "RANK,NAME,ACTOR,POINTS" << endl;
	for (int i = 0; i < v.size(); i++) {
		if (v[i].actor == "" || v[i].name == "" || v[i].rating < min) {
			return;
		}
		cout << i + 1 << "," << v[i].name << "," << v[i].actor << "," << v[i].rating << endl;	
	}
}

void printMenu() {
	cout << "---" << endl;
	cout << "MENU" << endl;
	cout << "1. Print the series" << endl;
	cout << "2. Search the series according to the rating" << endl;
	cout << "3. Add the series to the favorite list" << endl;
	cout << "4. Print the favorite list" << endl;
	cout << "5. Exit" << endl;
	cout << "---" << endl;
}

int main() {

	bool isValid = false, running = true, isactor = true, sameName = false;
	string seriesFile, ratingFile, choice, line, actorName, seriesName, word, favName, tempWord, error;
	ifstream input;
	int index, vectorIndex=0, indexFav;
	vector<TVseries> TVseriesList(0);
	vector<TVseries> favList(0);
	double rating, min;

	cout << "Welcome to Netflix TV Series Ratings Calculator!" << endl;
	do {
		cout << "Please enter a filename for Series-Actor file: ";
		cin >> seriesFile;
		input.open(seriesFile.c_str());
		if (input.fail()) {
			cout << "Can not find the specified file." << endl;
		}
		else {
			while (!input.eof()) {
				getline(input, line);
				istringstream iss(line);
				while (iss >> word) {
					if (isactor) {
						if (word.find(";") != -1) {
							isactor = false;
							word = word.substr(0, word.length() - 1);
						}
						actorName += word + " ";
					}
					else if (!isactor) {
						seriesName += word + " ";
					}
				}
				sameName = false;
				for (int i = 0; i < TVseriesList.size(); i++) {
					if (TVseriesList[i].name == toUpper(seriesName.substr(0, seriesName.length() - 1))) {
						sameName = true;
					}
				}
				if (!sameName) {
					TVseries pusher;
					TVseriesList.push_back(pusher);
					TVseriesList[vectorIndex].actor = toUpper(actorName.substr(0, actorName.length() - 1));
					TVseriesList[vectorIndex].name = toUpper(seriesName.substr(0, seriesName.length() - 1));
					vectorIndex++;
				}
				
				actorName = "";
				seriesName = "";
				isactor = true;
				sameName = false;
			}
			input.close();
			isValid = true;
		}

	} while (!isValid);

	vectorIndex = 0;
	isValid = false;

	do {
		cout << "Please enter a filename for Rating file: ";
		cin >> ratingFile;
		input.open(ratingFile.c_str());
		if (input.fail()) {
			cout << "Can not find the specified file." << endl;
		}
		else {
			while (!input.eof()) {
				getline(input, line);
				istringstream iss(line);
				iss >> rating;
				while (iss >> word) {
					seriesName += word + " ";
				}
				seriesName = seriesName.substr(0, seriesName.length() - 1);
				for (int i = 0; i < TVseriesList.size(); i++)
				{
					if (toUpper(seriesName) == toUpper(TVseriesList[i].name)) {
						TVseriesList[i].count += 1;
						TVseriesList[i].rating += rating;
					}
				}
				vectorIndex++;
				isactor = true;
				seriesName = "";
			}
			input.close();
			isValid = true;
			for (int i = 0; i < TVseriesList.size(); i++) {
				TVseriesList[i].rating = (TVseriesList[i].rating / TVseriesList[i].count);
			}
		}
	} while (!isValid);

	vectorSort(TVseriesList);

	while (running) {
		printMenu();
		cout << "Enter your choice: ";
		cin >> choice;
		cout << "---" << endl;
		if (choice == "1") {			
			printVector(TVseriesList, 0);
		}
		else if (choice == "2") {
			cout << "Please enter the minimum rating: ";
			cin >> min;
			if (cin.fail()) {
				cin.clear();
				cin >> error;
				cout << "This is not a valid rating!" << endl;
			}
			else if (min >= 0 && min <= 10) {
				printVector(TVseriesList, min);
			}
			else {
				cout << "This is not a valid rating!" << endl;
			}
		}
		else if (choice == "3") {
			cout << "Please enter the name of series: ";
			getline(cin, favName);
			getline(cin, favName);
			favName = toUpper(favName);
			indexFav = validName(TVseriesList, favList, favName);
			if (indexFav == -2) {
				cout << "Your favorite list already have " << favName << endl;
			}
			else if (indexFav != -1) {
				favList.push_back(TVseriesList[indexFav]);
			}
			else {
				cout << "There is no such TV series!" << endl;
			}
		}
		else if (choice == "4") {
			if (favList.size() == 0) {
				cout << "Your favorite list is currently empty!" << endl;
			}
			else {
				vectorSort(favList);
				printVector(favList, 0);
			}
		}
		else if (choice == "5") {
			running = false;
		}
		else {
			cout << "This is not a valid option!" << endl;
		}
	}
	return 0;
}