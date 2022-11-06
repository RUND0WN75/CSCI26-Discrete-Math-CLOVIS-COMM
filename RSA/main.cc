#include "/public/read.h" //Kerney's rad input library
#include <boost/multiprecision/cpp_int.hpp> //Bigint
#include <boost/multiprecision/cpp_dec_float.hpp> //Bigfloat
#include <boost/multiprecision/miller_rabin.hpp> //Prime testing
#include <boost/math/constants/constants.hpp> //Has pi
#include <algorithm>
using namespace std;
using namespace boost::random;
using namespace boost::multiprecision;

//You must write these functions
void generate();
void encode();
void decode();
void encrypt(); //DONE
void decrypt(); //DONE

int main()
{
	//TUTORIAL
	//This is how you make a bigint
	//cpp_int x("324234233423432422344"); //Arbitrary precision integer

	cout << "Welcome to RSA CSCI 26!\n";
	cout << "Pick an option:\n" <<
		"0. Generate Primes\n" <<
		"1. Encode a string\n" <<
		"2. Decode a string\n" <<
		"3. Encrypt a string\n" <<
		"4. Decrypt a string\n" << 
		"(Anything else to quit)\n";
	auto choice = read_opt<int>(); //Requires --std=c++17 to compile
	if (!choice) exit(0);
	else if (choice == 0) generate(); 
	else if (choice == 1) encode(); 
	else if (choice == 2) decode(); 
	else if (choice == 3) encrypt(); 
	else if (choice == 4) decrypt(); 
	else exit(0);
}

//Computes modular inverse given T and E
//Credit - http://stackoverflow.com/questions/12826114/euclids-extended-algorithm-c
cpp_int calculate_inverse(cpp_int t, cpp_int e) {
	cpp_int a,b,q,x,lastx,y,lasty,temp,temp1,temp2,temp3;
	a = t;
	b = e;
	if (b>a) {//we switch them
		swap(b,a);
	}

	x=0;
	y=1;
	lastx=1;
	lasty=0;
	while (b!=0) {
		q= a/b;
		temp1= a%b;
		a=b;
		b=temp1;

		temp2=x;
		x=lastx-q*x;
		lastx=temp2;

		temp3=y;
		y=lasty-q*y;
		lasty=temp3;
	}

	while (lasty < 0) lasty += t;
	return lasty;
}

//Generate P and Q, the two primes used to make your private key
//typedef cpp_int int_type;
void generate() {
mt11213b base_gen(clock());
	cpp_int p,q,e,n,t,d;
	p = read<cpp_int>("Please enter the first number you want to start looking for primes at:\n");
	q = read<cpp_int>("Please enter the second number you want to start looking for primes at:\n");
	//YOU: Find the first prime >= p and q
	while (!miller_rabin_test(p,25,base_gen)) {
		p++;
	}
	
	while (!miller_rabin_test(q,25,base_gen)) {
		q++;
	}

	cout << "P: " << p << endl;
	cout << "Q: " << q << endl;
	//YOU: Using P and Q, compute the RSA numbers. 
	n = p*q;
	t = (p-1)*(q-1);

	//E is done for you
	if (n > 65537) e = 65537;
	else if (n > 17) e = 17;
	else if (n > 7) e = 7;
	else e = 3;
	d = calculate_inverse(t,e);

	cout << "E: " << e << endl;
	cout << "N: " << n << endl;
	cout << "T: " << t << endl;
	cout << "D: " << d << endl;
}

//Convert an ASCII into a bigint
void encode() {
	string s = readline("What string would you like to encode?\n");
	cpp_int result = 0;
	//YOU: encode the string here
	for (char x : s) {
		//Add ASCII value of a character
		result += x;
		//Shift 8 bits to the left
		result = result << 8;
	}
	result = result >> 8;
	cout << "M:\n";
	cout << result << endl;
}

//Convert a bigint into an ACII string
void decode() {
	cpp_int x = read("What int would you like to decode?\n");
	string retval;
	//YOU: Decode x into the string retval here
	while (x != 0) {
		//Mod 256
		retval = retval + static_cast<char>(x % 256);
		//Shift 8 bits to the right
		x = x >> 8;
	}
	reverse(retval.begin(),retval.end());
	cout << "Your message is:\n";
	cout << retval << endl;
}

//---EVERYTHING BELOW IS FINISHED---

void encrypt() {
	cpp_int e = read("Please enter E:\n");
	cpp_int n = read("Please enter N:\n");
	cpp_int m = read("Please enter M:\n");
	if (m > n) {
		cout << "Sorry, M cannot be bigger than N.\n";
		exit(1);
	}
	cout << "S:\n";
	cpp_int s;
	//YOU: Do RSA encrypt here, should be one line of code
	s = powm(m,e,n);
	cout << s << endl;
}

void decrypt() {
	cpp_int d = read("Please enter D:\n");
	cpp_int n = read("Please enter N:\n");
	cpp_int s = read("Please enter S:\n");
	if (s > n) {
		cout << "Sorry, S cannot be bigger than N.\n";
		exit(1);
	}
	cout << "M:\n";
	cpp_int m;
	//YOU: Do RSA decrypt here, should be one line of code
	m = powm(s,d,n);
	cout << m << endl;
}
