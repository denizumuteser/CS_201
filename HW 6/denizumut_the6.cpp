#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "favoriteseries.h"
using namespace std;

void vectorSort(vector<episode>& v) {
	int k, j, maxIndex;
	episode temp;
	for (k = 0; k < v.size() - 1; k++) {
		maxIndex = k;
		for (j = k + 1; j < v.size(); j++) {
			if (v[j].date < v[maxIndex].date) {
				maxIndex = j;
			}
			else if (v[j].date == v[maxIndex].date) {

				if (v[j].slot == v[maxIndex].slot) {
					if (v[j].seriesCode < v[maxIndex].seriesCode) {
						maxIndex = j;
					}
				}
				else if (v[j].slot == "MORNING") {
					maxIndex = j;
				}
				else if (v[j].slot == "AFTERNOON" && v[maxIndex].slot != "MORNING") {
					maxIndex = j;
				}
				else if (v[j].slot == "EVENING" && v[maxIndex].slot == "NIGHT") {
					maxIndex = j;
				}
			}
		}
		temp = v[k];
		v[k] = v[maxIndex];
		v[maxIndex] = temp;
	}
}


void printVector(vector<episode> v, vector<series> v2) {
	string name;
	cout << "CODE,SERIES,EPISODE,DATE,SLOT" << endl;
	for (int i = 0; i < v.size(); i++) {
		for (int ii = 0; ii < v2.size(); ii++)
		{
			if (v[i].seriesCode == v2[ii].seriesCode) {
				name = v2[ii].seriesName;
			}
		}
		cout << v[i].seriesCode << "," << name << "," << v[i].episodeName << "," << v[i].date << "," << v[i].slot << endl;
	}
}


string toUpper(const string& s) {
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

bool existInDatabase(vector<series> v, int code) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i].seriesCode == code) {
			return true;
		}
	}
	return false;
}

void printMenu() {
	cout << "---" << endl;
	cout << "MENU" << endl;
	cout << "1. Print all TV series" << endl;
	cout << "2. Add TV series" << endl;
	cout << "3. Drop TV series" << endl;
	cout << "4. Print your favorite series with schedule" << endl;
	cout << "5. Print all your favorite actors" << endl;
	cout << "6. Exit" << endl;
	cout << "---" << endl;
}

int main() {
	string name, surname, menuChoice, line, word, seriesNamestr, actorNamestr, dateInput, episodeNameInput, timeInput;
	int id, month, day, year, index1, index2, codeChoice;
	bool running = true, isSeriesName = true;
	ifstream input;
	vector<series> seriesVector;
	episode episodeInput;
	Date episodeDate;
	

	input.open("series.txt");
	while (!input.eof()) {
		series seriesInput;
		getline(input, line);
		istringstream iss(line);
		iss >> id;
		seriesInput.seriesCode = id;
		while (iss >> word) {
			if (isSeriesName) {
				seriesNamestr += word + " ";
				if (word.find(";") != -1) {
					isSeriesName = false;
					seriesInput.seriesName = toUpper(seriesNamestr.substr(0, seriesNamestr.length() - 2));
					seriesNamestr = "";
				}
			}
			else {
				actorNamestr += word + " ";
				if (word.find(",") != -1) {
					seriesInput.actorNames.push_back(toUpper(actorNamestr.substr(0, actorNamestr.length()-2)));
					actorNamestr = "";
				}
			}
		}
		isSeriesName = true;
		seriesInput.actorNames.push_back(toUpper(actorNamestr.substr(0, actorNamestr.length()-1))); //last actor name
		actorNamestr = "";
		seriesVector.push_back(seriesInput);
	}
	input.close();
	input.open("episodes.txt");
	while (!input.eof()) {
		getline(input, line);
		istringstream iss(line);
		iss >> id >> dateInput >> timeInput;
		while (iss >> word) {
			episodeNameInput += word + " ";
		}
		episodeInput.episodeName = toUpper(episodeNameInput.substr(0, episodeNameInput.length() - 1));
		episodeInput.seriesCode = id;
		index1 = dateInput.find("/");
		index2 = dateInput.find("/", index1+1);
		month = stoi(dateInput.substr(0, index1));
		day = stoi(dateInput.substr(index1 + 1, index2 - index1 - 1));
		year = stoi(dateInput.substr(index2 + 1));
		Date episodeDate(month, day, year);
		episodeInput.date = episodeDate;
		episodeInput.slot = toUpper(timeInput);
		for (int i = 0; i < seriesVector.size(); i++) {
			if (seriesVector[i].seriesCode == episodeInput.seriesCode) {
				(seriesVector[i].episodes).push_back(episodeInput);
			}
		}
		episodeNameInput = "";
	}
	input.close();
		
	vector<episode> allEpisodes;
	for (int i = 0; i < seriesVector.size(); i++) {
		vectorSort(seriesVector[i].episodes);
		for (int ii = 0; ii < seriesVector[i].episodes.size(); ii++) {
			allEpisodes.push_back(seriesVector[i].episodes[ii]);
		}
	}
	vectorSort(allEpisodes);

	cout << "Welcome to my favorite TV series schedule program!" << endl;
	cout << "Please, enter your name and surname: ";
	cin >> name >> surname;
	name = toUpper(name);
	surname = toUpper(surname);

	FavoriteSeries favSeries(name, surname);

	while (running) {
		printMenu();
		cout << "Please enter your choice: ";
		cin >> menuChoice;
		if (menuChoice == "1") {
			printVector(allEpisodes, seriesVector);
		}
		else if (menuChoice == "2") {
			cout << "Enter code for the TV series you want to add: ";
			cin >> codeChoice;
			
			if (existInDatabase(seriesVector, codeChoice)) {
				if (!favSeries.ifExists(codeChoice)) {
					for (int i = 0; i < seriesVector.size(); i++) {
						if (seriesVector[i].seriesCode == codeChoice) {
							if (!favSeries.isConflict(seriesVector[i])) {
								favSeries.addSeries(seriesVector[i]);
								cout << favSeries.getFullName() << ", " << seriesVector[i].seriesName << " added to your schedule." << endl;
								
							}
							else {
								cout << favSeries.getFullName() << ", you can't add this TV series because of a date and slot conflict!" << endl;
							}

						}
					}
				}
				else {
					cout << favSeries.getFullName() << ", you can't add this TV series because you already added it!" << endl;
				}
			}
			else {
				cout << favSeries.getFullName() << ", there is no such TV series in the database!" << endl;
			}
			
		}
		else if (menuChoice == "3") {
			if (favSeries.isListEmpty()) {
				cout << favSeries.getFullName() << ", you did not add any TV series yet!" << endl;
			}
			else {
				cout << "Enter code for the TV series you want to drop: ";
				cin >> codeChoice;
				if (favSeries.ifExists(codeChoice)) {
					favSeries.dropSeriesSorted(codeChoice);
					for (int i = 0; i < seriesVector.size(); i++) {
						if (seriesVector[i].seriesCode == codeChoice) {
							name = seriesVector[i].seriesName;
						}
					}
					cout << favSeries.getFullName() << ", " << name << " has been dropped from your favorite list!" << endl;
				}
				else {
					cout << favSeries.getFullName() << ", there is no such TV series in your favorite list!" << endl;
				}
			}
		}
		else if (menuChoice == "4") {
			if (favSeries.isListEmpty()) {
				cout << favSeries.getFullName() << ", you did not add any TV series yet!" << endl;
			}
			else {
				cout << favSeries.getFullName() << ", here is your favorite TV series:" << endl;
				favSeries.displayFavoriteList();
			}
		}
		else if (menuChoice == "5") {
			if (favSeries.isListEmpty()) {
				cout << favSeries.getFullName() << ", you did not add any TV series yet!" << endl;
			}
			else {
				cout << favSeries.getFullName() << ", here is your favorite actors:" << endl;
				favSeries.displayFavoriteActors();
			}

		}
		else if (menuChoice == "6") {
			running = false;
			cout << "Goodbye, " << favSeries.getFullName() << "!" << endl;
		}
		else {
			cout << "Invalid option!" << endl;
		}

	}

	return 0;
}