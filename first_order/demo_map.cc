#include <iostream>
#include <map>
#include <vector>
using namespace std;

//Insert a mapping from A to B, like "Socrates" => "Mortal".
void map_insert(multimap<string,string> &m,const string &a,const string &b) {
	m.insert({a,b});
}

//Return all hits for s in the map, in a vector of strings
//Returns an empty vector if there are no hits
vector<string> map_search(const multimap<string,string> &m, const string &s) {
	vector<string> retval;
	size_t count = m.count(s); //How big is the map?
	if (count == 0) return retval; //If it is empty, just return an empty vector
	//equal_range() is a function that returns a pair of iterators to the beginning and end of a range 
	// where all the values equal s (the string we're searching for)
	for (auto it = m.equal_range(s).first; it != m.equal_range(s).second; ++it)
		retval.push_back(it->second); //it->first is the key (like "Socrates"), it->second is the value (like "Mortal").
	return retval;
}

int main() {
	//Build a database of facts about months
	multimap<string, string> m;
	map_insert (m, "January", "31 Days"); //Record something we know about January
	map_insert (m, "January", "It is cold"); //Record more facts about January
	map_insert (m, "January", "The French call it Janvier"); //And a third
	map_insert (m, "February", "The Chinese call it Er Yue, which means 2nd Month"); //Store something about February

	//Now search the database
	cout << "Here's what we know about January:\n";
	auto vec = map_search(m,"January"); //Will return a vector<string> of size 3
	for (auto s : vec) cout << s << endl; 

	cout << "\nHere's what we know about February:\n";
	vec = map_search(m,"February"); //Will return a vector<string> of size 1
	for (auto s : vec) cout << s << endl;

	cout << "\nHere's what we know about March:\n";
	vec = map_search(m,"March"); //Will return an empty vector
	for (auto s : vec) cout << s << endl; //So will print nothing
}
