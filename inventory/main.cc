//This is how I'd do it in a data structures class, if you want to see how to do it with just CSCI40 skills, check out the other .cc file in this directory
#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <boost/algorithm/string/trim.hpp>
using namespace boost;
using namespace boost::algorithm;
using namespace std;

//Turn on or off all debugging couts
#define DEBUG(X)

//Upper cases a string
void uppercaseify(string &str) {
	for (char &ch : str) ch = toupper(ch);
}

void die() {
	cout << "Invalid Input!\n";
	exit(EXIT_FAILURE);
}

class Inventory {
	vector<string> cars = {};
	string name = "";
	public:
	Inventory(string new_name) {
		//YOU 
		name = new_name;
	}
	bool is_in(string search) const {
		//YOU
		for (string x : cars) {
			if (x == search) return true;
		}
		return false; 
	}
	void insert(string new_car) {
		//YOU
		if (!is_in(new_car)) {
			cars.push_back(new_car);
		}

	}
	Inventory intersect(const Inventory &other) {  
		//YOU
		Inventory retval("");
		for (size_t i = 0; i < cars.size(); i++) {
			if (other.is_in(cars.at(i))) retval.insert(cars.at(i)); //If a car is in the other vector, insert into the current vector
		}
		return retval;
	}
	Inventory unionize(const Inventory &other, bool copy = false) {  
		//YOU
		Inventory retval("");
		for (size_t i = 0; i < cars.size(); i++) {
			retval.insert(cars.at(i)); //Insert a new car into the vector
		}

		for (size_t j = 0; j < other.cars.size(); j++) {
			//if (other.is_in())
			retval.insert(other.cars.at(j)); //Insert a new car into the other vector
		}
		if (copy) cars = retval.cars; //If there's a duplicate car, then set it equal to the current car

		return retval; 
	}
	int size() const {
		return cars.size();
	}
	string get_name() const {
		return name;
	}
	friend istream& operator>>(istream &ins, Inventory &other);
	friend ostream& operator<<(ostream &outs, const Inventory &other);
}; //End of inventory

class SuperSet {
	vector<Inventory> set; //Set of dealerships
	public:
	SuperSet() : set() {}
	void insert(Inventory &new_inv) {
		set.push_back(new_inv);
	}
	//It will return the inventory matching name
	//If ignore_fail is set, then it won't die on a lack of a match
	Inventory* search(string name, bool ignore_fail = false) {
		for (size_t i = 0; i < set.size(); i++) {
			if (set.at(i).get_name() == name) return &set.at(i);
		}
		if (ignore_fail) return nullptr; //STUB
		else die();
	}
	//Prints all inventories in all tables
	void print_all() {
		//YOU
		Inventory temp("");
		for (auto x : set) {
			temp.unionize(x,true);	
			cout << x << endl;
		}
		cout << temp.size() << endl;
	}
	void poset() { //Do the partial ordering of the sets here
	}
} inventories;

//This should read from an instream, parse the input and add the vins to other
//You don't need to write this if you don't want.
istream& operator>>(istream &ins, Inventory &other) {
	//YOU
	string temp = "";
	ins >> temp;
	other.insert(temp);
	return ins;
}

//This should output an inventory to outs
ostream& operator<<(ostream &outs, const Inventory &other) {
	//YOU
	if (other.name != "") cout << other.name << ": ";
	for (size_t i = 0; i < other.cars.size(); i++) {
		if (i == other.cars.size() - 1) outs << other.cars.at(i);
		else outs <<  other.cars.at(i) << ", ";
	}
	return outs;
}

int main() {
	SuperSet set;
	//vector<string> vec;
	while (!cin.eof()) {
		//Should rewrite this using getline and strstream
		string line;
		getline(cin,line);
		stringstream ss(line);
		string first,second,third,fourth,fifth;
		ss >> first;
		trim(first);

		if (first.size() < 1) break;
		if (!cin) break;
		if (first == "CREATE") {
			//YOU
			ss >> second;
			if (second != "TABLE") die();
			if (ss.eof()) die();
			getline(ss, third);
			trim(third);
			if (third.size() == 0) die();
			for (char x : third) if (islower(x) || (!isalnum(x) && x != ' ')) die(); 
			Inventory temp(third);
			set.insert(temp); //Creating anonymous variable.	
		} //END CREATE
		else if (first == "INSERT") {
			//YOU
			ss >> second;
			if (second == "INTO") {
				string ID;
				while (third != "VALUES") {
					ID += third + " ";
					if (ss.eof()) die();
					ss >> third;
				}
				trim(ID);
				Inventory *temp = set.search(ID);
				while (ss) {
					getline(ss, third, ',');
					trim(third);
					Inventory *temp2 = set.search(third, true);
					if (temp2 != nullptr) {
						temp->unionize(*temp2, true);
					}  
					else temp->insert(third);
				}
			}
			else die();

		} //END INSERT
		else if (first == "SELECT") {
			//YOU
			Inventory *temp1, *temp2;
			ss >> second;
			if (second == "FROM") {
				string ID;
				while (third != "UNION") {
					ID += third + " ";
					if (ss.eof()) die();
					ss >> third;
				}
				trim(ID);
				temp1 = set.search(ID);

				ID = "";
				getline(ss, ID);
				trim(ID);
				temp2 = set.search(ID);
				cout << temp1->unionize(*temp2) << endl;
			}
			else if (second == "*") {
				ss >> third;
				if (third == "FROM") {
					ss >> fourth;
					if (fourth == "*") {
						set.print_all();
					}
					else {
						string ID;
						while (fourth != "INNER") {
							ID += fourth + " ";
							if (ss.eof()) die();
							ss >> fourth;
						}
						trim(ID);
						temp1 = set.search(ID);
						ss >> fifth;
						if (fifth != "JOIN") die();
						ID = "";
						getline(ss, ID);
						trim(ID);
						temp2 = set.search(ID);
						cout << temp1->intersect(*temp2) << endl;
					}
				} 
			}
			else die();	
		} //END SELECT

		//Extra cfedit stuff below
		else if (first == "ID") {
			//YOU

		} //END ID
		else if (first == "POSET") {
			//YOU

		} //END POSET
		else {
			DEBUG(cout << "COMMAND NOT RECOGNIZED: " << first << endl);
			die();
		}
	}
}
