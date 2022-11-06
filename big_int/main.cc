#include "/public/read.h" //Kerney's rad input library
#include <boost/multiprecision/cpp_int.hpp> //Bigint
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp> //Bigfloat
#include <boost/multiprecision/miller_rabin.hpp> //Prime testing
#include <boost/math/constants/constants.hpp> //Has pi
#include <iostream>
#include <iomanip>
using namespace std;
using namespace boost::random;
using namespace boost::multiprecision;
using boost::multiprecision::cpp_dec_float_100;
using boost::math::constants::pi;

//You will have to write these functions
void addition();
void subtraction();
void multiplication();
void division();
void mod();
void factorial();
void exponential();
void exponential_modulus();
void prime_testing();
void volume();
void integral();

int main() {

	/*
	typedef cpp_int int2;
	typedef uint64_t uint64;
	int2 bob = 50;
	cout << bob * 2 << endl;*/
	//Set precision to 100 digits
	cout << std::setprecision(std::numeric_limits<cpp_dec_float_100>::digits10);

	//TUTORIAL
	//This is how you make a bigint
	//cpp_int x("324234233423432422344"); //Arbitrary precision integer
	//cout << pow(x,2) << endl; //x squared
	//cout << powm(x,2,10) << endl; //x squared modulus 10

	//This is how you make a big float
	//cpp_dec_float_100 x = 2 * pi<cpp_dec_float_100>(); //100 digits of precision in a float
	//cout << x << endl;

	system("figlet BIG MATH | lolcat --seed=32");
	cout << "Pick an option:\n" <<
		"0. Addition\n" <<
		"1. Subtraction\n" <<
		"2. Multiplication\n" << 
		"3. Division\n" <<
		"4. Modulus\n" <<
		"5. Factorial\n" <<
		"6. Exponentiation\n" <<
		"7. Exponentiation & Modulus\n" <<
		"8. Prime Testing\n" <<
		"9. Volume of a cylinder\n" <<
		"10. Integral\n" << //Definite integral
		"(Anything else to quit)\n";
	auto choice = read_opt<int>();
	if (!choice) exit(0);
	else if (choice == 0) addition(); //DONE
	else if (choice == 1) subtraction(); //DONE
	else if (choice == 2) multiplication(); //DONE
	else if (choice == 3) division(); //DONE
	else if (choice == 4) mod(); //DONE
	else if (choice == 5) factorial(); //DONE
	else if (choice == 6) exponential(); 
	else if (choice == 7) exponential_modulus(); 
	else if (choice == 8) prime_testing(); 
	else if (choice == 9) volume(); //DONE 
	else if (choice == 10) integral(); 
}

//Example of how to do it
void addition() {
	cpp_int first  = read("Please enter the first integer:\n");
	cpp_int second = read("Please enter the second integer:\n");
	cout << first << " + " << second << " = " << (first + second) << endl;
}

//YOU: Write all these functions
void subtraction() {
	cpp_int first  = read("Please enter the first integer:\n");
	cpp_int second = read("Please enter the second integer:\n");
	cout << first << " - " << second << " = " << (first - second) << endl;
}

void multiplication() {
	cpp_int first  = read("Please enter the first integer:\n");
	cpp_int second = read("Please enter the second integer:\n");
	cout << first << " * " << second << " = " << (first * second) << endl;
}

void division() {
	cpp_int first  = read("Please enter the first integer:\n");
	cpp_int second = read("Please enter the second integer:\n");
	cout << first << " / " << second << " = " << (first / second) << endl;
}

void mod() {
	cpp_int first  = read("Please enter the first integer:\n");
	cpp_int second = read("Please enter the second integer:\n");
	cout << first << " % " << second << " = " << (first % second) << endl;
}


//The 0 is a placeholder for you to replace with the answer
void factorial() {
	cpp_int first  = read("Please enter the first integer:\n");
	cpp_int second = 1;
	//Output first!
	for (cpp_int i = first; i > 0; i--) second *= i;
	cout << first << "! = " << second << endl;
}

void exponential() {
	cpp_int first  = read("Please enter the first integer:\n");
	int second = read("Please enter the second integer:\n");
	//Output (first ^ second)
	//cpp_int x = first ** second == 1 << second;
	cout << first << " ^ " << second << " = " << pow(first,second) << endl;
}

void exponential_modulus() {
	cpp_int first  = read("Please enter the first integer:\n");
	int second = read("Please enter the second integer:\n");
	cpp_int third  = read("Please enter the third integer:\n");
	//Output (first ^ second) % third
	cout << "(" << first << " ^ " << second << ") % " << third << " = " << powm(first,second,third) << endl;
}

//You can write your own test or use a library function to determine primality
void prime_testing() {
        cpp_int first = read("Please enter the first integer:\n");
        if (miller_rabin_test(first,25)) cout << first << " is a prime.\n";
        else cout << first << " is not a prime.\n";
        /*
        bool prime = true;
        if (first <= 1) prime = false;
        for (cpp_int i = 2; i < first; i++) {
                if (first % i == 0) prime = false;
                else prime = true;
        }
        if (prime) cout << first << " is a prime.\n";
        else cout << first << " is not a prime.\n";
        */
}

/*
void prime_testing() {
	cpp_int first  = read("Please enter the first integer:\n");
	//If first is a prime, print the first, otherwise print the second
	if (miller_rabin_test((n-1)first)) cout << first << " is a prime.\n";
	else {
		cout << first << " is not a prime.\n";
		
		for (cpp_int i = 2; i < first / 2; i++) { 
			if (first % i == 0 || first <= 1) {
				cout << first << " is not a prime.\n";
				break;
			}
		}
	}
}*/

//Compute volume of cylinder
void volume() {
	//Formula: pi (radius)^2 * height
	cpp_dec_float_100 height = read("Please enter the first float:\n");
	cpp_dec_float_100 radius = read("Please enter the second float:\n");
	//cpp_int x = pi<cpp_dec_float_100>() * pow(radius,2) * height;
	cout << "A cylinder of height " << height << " and radius " << radius << " has a volume of " << pi<cpp_dec_float_100>() * pow(radius, 2) * height << endl;
}

//Compute the integral of cos(x) / (1+abs(x) using a left Riemann sum with a width of 0.001
//abs(sin(end)) is a placeholder you need to replace with the answer
	/*while (x <= end - width) {x += width;	}*/
	//cpp_dec_float_100 x = start;
	//cpp_dec_float_100 width = 0.001;
void integral() {
	cpp_dec_float_100 start = read("Please enter the start point of the integral:\n");
	cpp_dec_float_100 end = read("Please enter the end point of the float:\n");
	cpp_dec_float_100 x = 0;
	if (start >= end) {
		cout << "The starting point must be less than the ending point.\n";
		exit(0);
	}	
	for (cpp_dec_float_100 i = start; i <= end - 0.001; i+= 0.001) { x += ((cos(i)) / (1+abs(i))) * 0.001; }

	cout << "The area under the curve of cos(x) / (1+abs(x)) from " << start << " to " << end << " is " << x << endl;
}
