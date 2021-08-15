#include <iostream>
#include <string>
using namespace std;

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

string cinLine() {
	string result, s;
	cin >> s;
	while (toUpper(s) != "END") {
		result = result + " " + s;
		cin >> s;
		
	}
	result = result.substr(1);
	return result;
}

bool isValid(string s) {
	bool valid = true;
	for (int i = 0; i < s.length(); i++) {
		if (!((s.at(i) >= '0' && s.at(i) <= '9') || (s.at(i) >= 'A' && s.at(i) <= 'Z') || (s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) == 32)))
		{
			valid = false;
		}
	}
	return valid;
}

void printOut(int indx, string word) {
	cout << "index: " << indx - 1;
	cout << " word: " << word << endl;
}

void search(string source_str, string search_str) {
	string source_str2 = " " + source_str + " ";
	string word;
	int index, startpos, count, endpos, start_from;
	start_from = 0;
	index = 0;

	if (search_str.at(search_str.length() - 1) == '*' && search_str.at(search_str.length() - 2) == '*') {
		string search_str2 = search_str.substr(0, (search_str.length() - 2));
		for (count = 0; count < source_str.length() && index !=-1;count++) {
			index = source_str2.find(search_str2, start_from);
			endpos = source_str2.find(" ", index + 1);
			startpos = source_str2.rfind(" ", endpos - 1);
			word = source_str2.substr(startpos + 1, (endpos - startpos - 1));
			if (index > 0) {
				printOut(index, word);
			}
			start_from = index + 1;
		}	
	}
	else if (search_str.at(search_str.length() - 1) == '+') {
		string search_str2 = search_str.substr(0, (search_str.length() - 1));
		for (count = 0; count < source_str.length() && index != -1; count++) {
			index = source_str2.find(search_str2, start_from);
			endpos = source_str2.find(" ", index + 1);
			startpos = source_str2.rfind(" ", endpos - 1);
			word = source_str2.substr(startpos + 1, (endpos - startpos - 1));
			if (index > 0) {
				if(startpos + 1 == index) {
					printOut(index, word);
				}
			}
			start_from = index + 1;
		}
	}
	else if (search_str.at(search_str.length() - 1) == '.') {
		string search_str2 = search_str.substr(0, (search_str.length() - 1));
		for (count = 0; count < source_str.length() && index != -1; count++) {
			index = source_str2.find(search_str2, start_from);
			endpos = source_str2.find(" ", index + 1);
			startpos = source_str2.rfind(" ", endpos - 1);
			word = source_str2.substr(startpos + 1, (endpos - startpos - 1));
			if (index > 0) {
				if (index + search_str2.length() == endpos) {
					printOut(index, word);
				}
			}
			start_from = index + 1;
		}
	}
	else if (search_str.at(search_str.length() - 1) == '*') {
		string search_str2 = search_str.substr(0, (search_str.length() - 1));
		for (count = 0; count < source_str.length() && index != -1; count++) {
			index = source_str2.find(search_str2, start_from);
			endpos = source_str2.find(" ", index + 1);
			startpos = source_str2.rfind(" ", endpos - 1);
			word = source_str2.substr(startpos + 1, (endpos - startpos - 1));
			if (index > 0) {
				if ((index + search_str2.length() != endpos) && (startpos + 1 != index) && (word.at(word.length()-1) != search_str2.at(search_str2.length()-1))) {
					printOut(index, word);
				}
			}
			start_from = index + 1;
		}
	}
}

int main() {
	string source_string, search_string;
	int index;

	cout << "Enter source string: ";
	source_string = cinLine();
	while (!(isValid(source_string))) {
		cout << "Enter source string: ";
		source_string = cinLine();
	}

	cout << "Enter search string: ";
	cin >> search_string;
	while (toUpper(search_string) != "QUIT") {
		search(source_string, search_string);
		cout << "Enter search string: ";
		cin >> search_string;
	}
	return 0;
}