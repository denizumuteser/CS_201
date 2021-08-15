#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

bool spellcheck(string input, string pool) {
	string word;
	istringstream iss2(pool);
	while (iss2 >> word) {
		if (input == word) {
			return true;
		}
	}
	return false;
}

string spellcorrect(string input, string pool) {
	int count = 0, temp = 0;
	string word = "", output, output2;
	bool oneMatch = true;
	double value;
	value = float((input.length()) / 2.0);
	istringstream  iss3(pool);
	while (iss3 >> word) {
		if (word.length() == input.length()) {
			for (int i = 0; i < word.length(); i++)
			{
				if (word.at(i) == input.at(i)) {
					count++;
				}
			}
			if (count >= value && count >= temp) {
				if (count == temp) {
					output2 += "," + word;
					temp = count;
					
				}
				else {
					output2 = word;
					temp = count;
				}
			}
			else {
				output = ("{" + input + "}");
			}
		}
		else {
			output = ("{" + input + "}");
		}
		count = 0;
	}
	if (output2 != "") {
		if (output2.find(",") != -1) {
			return ("(" + output2 + ")");
		}
		return output2;
	}
	return output;
}

string toLower(const string& s) {
	string result = "";
	char c;
	unsigned long len = s.length();

	for (int i = 0; i < len; i++) {
		c = s.at(i);
		if (c >= 'A' && c <= 'Z') {
			c = c - ('A' - 'a');
		}
		result = result + c;
	}
	return result;
}

int main() {
	ifstream input, input2;
	string name_pool, name_main, word, new_pool, line, output, depo;
	bool is_name_valid = false;

	do {
		cout << "Please enter a filename for the word pool: ";
		cin >> name_pool;
		input.open(name_pool.c_str());
		if (input.fail()) {
			cout << "Cannot open the word pool file." << endl;
		}
		else {
			while (!input.eof()) {
				input >> word;
				if (new_pool.find(toLower(word)) == -1) {
					new_pool += toLower(word) + " ";
				}
					
			}
			is_name_valid = true;
			input.close();
		}
	} while (is_name_valid == false);
	new_pool = new_pool.substr(0, new_pool.length()-1);

	is_name_valid = false;
	do {
		cout << "Please enter a filename for the main text: ";
		cin >> name_main;
		input2.open(name_main.c_str());
		if (input2.fail()) {
			cout << "Cannot open the main text file." << endl;
		}
		else {
			cout << "You may find the results below:" << endl;
			cout << endl;
			while (getline(input2, line)) {
				istringstream iss(line);
				while (iss >> word) {
					if (spellcheck(word, new_pool) == true) {
						depo += word + " ";
					}
					else {
						output = spellcorrect(toLower(word), new_pool);
						depo += output + " ";
					}
				
				}
				cout << depo.substr(0, depo.length()-1);
				cout << endl;
				depo = "";
			}
			is_name_valid = true;
			input2.close();
		}
	} while (is_name_valid == false);
}