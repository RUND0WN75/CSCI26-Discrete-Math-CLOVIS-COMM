#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
using namespace std;

void uppercaseify(string &s) { for (char &c : s) c = toupper(c); }

int main() {
	vector<string> names;
	vector<vector<string>> inventories;
	while (true) {
		cout << "PLZ enter a table name (QUIT to quit):\n";
		//In your code this will be CREATE TABLE right?
		string name;
		cin >> name;
		uppercaseify(name);
		if (name == "QUIT" || !cin) break;
		names.push_back(name); //Add a name to the roster
		vector<string> new_table;
		inventories.push_back(new_table); //Add a corresponding table
	}
	while (true) {
		cout << "Please enter a table name to access (QUIT to quit):\n";
		string name;
		cin >> name;
		uppercaseify(name);
		//TODO: Vet the input
		if (name == "QUIT" || !cin) break;
		size_t index = names.size();
		for (size_t i = 0; i < names.size(); i++) {
			if (name == names.at(i)) {
				index = i;
				break;
			}
		}
		if (index == names.size()) {
			cout << "Table not found\n";
			continue;
		}
		cout << "Do you want to insert or search?\n";
		string s;
		cin >> s;
		uppercaseify(s);
		if (s == "INSERT") {
			cout << "Type VINs to insert (QUIT to quit):\n";
			while (true) {
				cin >> s;
				uppercaseify(s);
				if (!cin or s == "QUIT") break;
				//TODO: Check for duplicates
				inventories.at(index).push_back(s);
			}
		}
		else if (s == "SEARCH") {
			cout << "Type VINs to search for (QUIT to quit):\n";
			while (true) {
				cin >> s;
				uppercaseify(s);
				if (!cin or s == "QUIT") break;
				bool found = false;
				for (size_t i = 0; i < inventories.at(index).size(); i++) {
					if (s == inventories.at(index).at(i)) found = true;
				}
				if (found)
					cout << "IN TABLE\n";
				else
					cout << "NOT IN TABLE\n";
			}
		}
	}
}
