#include <iostream>
#include <map>
#include <vector>
#include <cctype>
using namespace std;

vector<string> all_are(string a);
vector<string> some_are(string a);
vector<string> none_are(string a);
//Passing in a vector and subject to be looked for
void find_adjective(const vector<string> &vec_A, const string &subject, const string &message) {
	///Iterate through the vector
	//Each time we iterate,  we output something
	for (string word : vec_A) { 
		cout << subject << message << word << endl;
		//Make a temp vector = calls the function
		//Checking for each adjective
		vector<string> temp1 = all_are(word);
		vector<string> temp2 = some_are(word);
		vector<string> temp3 = none_are(word);
		find_adjective(temp1, subject, " IS ");
		find_adjective(temp2, subject, " MAY BE ");
		find_adjective(temp3, subject, " IS NOT ");
	}
}

/*
void SOME_ARE(const vector<string> &vec_A, const string &subject) {
	for (string word : vec_A) { 
		cout << subject << " MAY BE " << word << endl;
		vector<string> temp1 = some_are(word);
		SOME_ARE(temp1, subject);
	}
}

void NONE_ARE(const vector<string> &vec_A, const string &subject) {
	for (string word : vec_A) { 
		cout << subject << " IS NOT " << word << endl;
		vector<string> temp1 = none_are(word);
		NONE_ARE(temp1, subject);
	}
}*/

//Insert a mapping from A to B, like "Socrates" => "Mortal".
void map_insert(multimap<string,string> &m,const string &a,const string &b) {
	m.insert({a,b});
}

//Return all hits for A in the map. The vector returns all hits.
//For example, searching for "Socrates" may return "Mortal" in a size-1 vector
vector<string> map_search(const multimap<string,string> &m, const string &a) {
	vector<string> retval;
	size_t count = m.count(a);
	if (count == 0) return retval;
	for (auto it = m.equal_range(a).first; it != m.equal_range(a).second; ++it)
		retval.push_back(it->second);
	return retval;
}

//We uppercaseify ALL INPUT in this program for simplicity
void upper(string &s) {
	for (char &c: s)
		c = toupper(c);
}
void die() {
	//https://www.youtube.com/watch?v=HwBmPiOmEGQ
	cout << "Dave, this conversation can serve no purpose any more. Goodbye.\n";
	exit(1);
}

vector<string> is_a(string a = "") {
	static multimap<string,string> m; //This is the IS-A database
	vector<string> retval;
	if (a == "") { //New IS-A rule
		cout << "Type a new rule, such as 'Socrates IS A man':\n";

		//Read first word in sentence - Socrates
		string hyponym; //Means "smaller concept"
		cin >> hyponym;
		if (!cin) die();
		upper(hyponym);

		//Read second word in sentence - IS
		string copula; //Copula means "is a"
		cin >> copula;
		if (!cin) die();
		upper(copula);
		if (copula != "IS") die();

		//Read third word in sentence - A
		cin >> copula;
		if (!cin) die();
		upper(copula);
		if (copula != "A") die();

		//Read forth word in sentence - man
		string hypernym; //Means "larger concept"
		cin >> hypernym;
		if (!cin) die();
		upper(hypernym);

		//Now insert it into the database, m.
		map_insert(m,hyponym,hypernym);

		//Print confirmation to the screen
		cout << "Successfully inserted rule: " << hyponym << " IS A " << hypernym << endl;
	}
	else { //IS-A query
		retval = map_search(m,a);
	}
	return retval;
}


vector<string> all_are(string a = "") {
	static multimap<string,string> m; //This is the ALL-ARE database
	vector<string> retval;
	if (a == "") { //New ALL-ARE rule
		string first, second;
		cout << "Type a new rule, such as 'ALL men ARE mortal':\n";

		//YOU: Do this section
		//Reads in "ALL"
		string x;
		cin >> x;
		if (!cin) die();
		upper(x);
		if (x != "ALL") die();

		//Reads in first concept
		cin >> first;
		if (!cin) die();
		upper(first);

		//Reads in "ARE"
		cin >> x;
		if (!cin) die();
		upper(x);
		if (x != "ARE") die();

		//Reads in second concept
		cin >> second;
		if (!cin) die();
		upper(second);

		//Insert into the query
		map_insert(m,first,second);

		cout << "Successfully inserted rule: ALL " << first << " ARE " << second << endl;
	}
	else { //ALL-ARE query
		//YOU: Do this section
		retval = map_search(m,a);
	}
	return retval;
}


vector<string> some_are(string a = "") {
	static multimap<string,string> m; //This is the SOME-ARE database
	vector<string> retval;
	if (a == "") { //New SOME-ARE rule
		string first, second;
		cout << "Type a new rule, such as 'SOME dogs ARE smart':\n";

		//YOU: Do this section
		//Reads in "SOME"
		string y;
		cin >> y;
		if (!cin) die();
		upper(y);
		if (y != "SOME") die();

		//Reads in first concept
		cin >> first;
		if (!cin) die();
		upper(first);

		//Reads in "ARE"
		cin >> y;
		if (!cin) die();
		upper(y);
		if (y != "ARE") die();

		//Reads in second concept
		cin >> second;
		if (!cin) die();
		upper(second);

		//Insert into the query
		map_insert(m,first,second);
		cout << "Successfully inserted rule: SOME " << first << " ARE " << second << endl;
	}
	else { //SOME-ARE query
		//YOU: Do this section
		retval = map_search(m,a);
	}
	return retval;
}

vector<string> none_are(string a = "") {
	static multimap<string,string> m; //This is the NONE-ARE database
	vector<string> retval;
	if (a == "") { //New NONE-ARE rule
		string first, second;
		cout << "Type a new rule, such as 'NO cats ARE perfect':\n";

		//YOU: Do this section
		//Reads in "NO"
		string z;
		cin >> z;
		if (!cin) die();
		upper(z);
		if (z != "NO") die();

		//Reads in first concept
		cin >> first;
		if (!cin) die();
		upper(first);

		//Reads in "ARE"
		cin >> z;
		if (!cin) die();
		upper(z);
		if (z != "ARE") die();

		//Reads in second concept
		cin >> second;
		if (!cin) die();
		upper(second);

		//Insert into the query
		map_insert(m,first,second);

		cout << "Successfully inserted rule: NO " << first << " ARE " << second << endl;
	}
	else { //NONE-ARE query
		//YOU: Do this section
		retval = map_search(m,a);
	}
	return retval;
}


//This function will look up people from the IS-A database and print out
// everything that we know about them.
void question() {
	cout << "What would you like to know about?\n";
	string subject;
	cin >> subject;
	if (!cin) die();
	upper(subject);
	auto vec = is_a(subject); //Look up the person in the IS-A map
	for (auto i : vec) {
		cout << subject << " IS A " << i << endl;
			auto vec2 = all_are(i);
			find_adjective(vec2, subject, " IS ");
			
			auto vec3 = some_are(i);
			find_adjective(vec3, subject, " MAY BE ");

			auto vec4 = none_are(i);
			find_adjective(vec4, subject, " IS NOT ");
	}

	//YOU:
	//Now that you have all the things socrates is, go into those sets and print out everything you know about them as well.
	//If we know the following facts (from being entered earlier):
	// 1) Socrates is a men (note the plurals will look weird)
	// 2) All men are mortal
	// 3) Some mortal are smart
	// 4) No men are perfect
	//
	//And we ask to look up Socrates, it should print this:
	//SOCRATES IS A MEN
	//SOCRATES IS MORTAL
	//SOCRATES MAY BE SMART
	//SOCRATES IS NOT PERFECT

	//Don't worry about contradictory inferences, unless you want extra credit...

	//auto vec5 = map_search(is_a(subject), );
	//for (auto i : vec5) cout << subject << " IS A" << i << endl;
	
	//auto vec5 = map_search(all_are(subject), );
	//for (auto i : vec6) cout << subject << " IS " << i << endl;
	
	//auto vec5 = map_search(some_are(subject), );
	//for (auto i : vec7) cout << subject << " MAYBE " << i << endl;
	
	//auto vec5 = map_search(no_are(subject), );
	//for (auto i : vec8) cout << subject << " IS NOT: " << i << endl;
}

int main() {
	cout << "Hello, Dave. I am the HAL 9000.\n";
	while (true) {
		cout << "Would you like to input:\n";
		cout << "1) An IS-A rule?\n";
		cout << "2) An ALL-ARE rule?\n";
		cout << "3) A SOME-ARE rule?\n";
		cout << "4) A NONE-ARE rule?\n";
		cout << "5) Ask a question?\n";
		cout << "6) Deactivate the HAL 9000.\n";
		string s;
		cin >> s;
		if (!cin) die();
		if (s == "1") {
			is_a();
		}
		else if (s == "2") {
			all_are();
		}
		else if (s == "3") {
			some_are();
		}
		else if (s == "4") {
			none_are();
		}
		else if (s == "5") {
			question();
		}
		else if (s == "6") {
			break;
		}
		else {
			cout << "I'm sorry, Dave, but I can't do that.\n";
			continue;
		}
	}
	//For the feels: https://www.youtube.com/watch?v=c8N72t7aScY
	cout << "Daisy, Daisy, give me your answer, do...\n";
	return 0;
}
