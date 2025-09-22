/** INTRODUCTION TO TESTING YOUR CODE */
{
'software validation': process of determining software acts predictably
compile && test frequently
'unit testing': testing a small part of code
	temporary print statements
	test functions
	test functions with number of tests failed/passed
		int testVowel(){
		if (!isLowerVowel('a')) return 1;
		if (isLowerVowel('q')) return 2;
		return 0;
		}

'assert' can be used to abort the program with an error message
// #include <cassert> && assert(bool)
'testing framework': premade software that streamlines testing
'integration testing': after unit testing, testing in the larger program
}
/** CODE COVERAGE */
{
'code coverage': how much of the code is executed when testing
'statement coverage': percentage of statements exercised by testing
// the following program has full coverage as every line is executed
// foo (1,0)
	int foo(int x, int y){
		int z{ y };
		if (x > y){
			z = x;
		}
		return z;
	}
// this one will require 2 calls to test call statements
	bool isLowerVowel(char c){
		switch (c) { // statement 1
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u':
			return true; // statement 2
		default:
			return false; // statement 3
		}
	}

'branch coverage': percentage of branches that have executed
an 'if' statement has 2 branches; 'switch' can have many
// same function as before foo(1,0) only has 50% branch coverage
// best practice: aim for 100% branch coverage
	int foo(int x, int y){
		int z{ y };
		if (x > y){
			z = x;
		}
		return z;
	}

'loop coverage': informally known as the '012 test'
// a loop should work and be tested 2 times
'category testing': testing inputs of similar types
	'int': should test negtives, zero, positive, overflow
	'floating point': test precision with -0.1, 0.1, -0.7, 0.7
	'strings': test full whitespace, partial whitespace, alphanumerals
	'pointer': test 'nullptr'
}
/** COMMON SEMANTIC ERRORS IN C++ */
{
'conditional logic errors': incorrect code in control flow condition
// if input 5 then will return 5 is greater than 5
	#include <iostream>
	int main(){
		std::cout << "Enter an integer: ";
		int x{};
		std::cin >> x;
		if (x >= 5) // oops, we used operator>= instead of operator>
			std::cout << x << " is greater than 5\n";
		return 0;
	}
	
'infinite loops': when a loop statement is always 'true' && doesnt end
// count can never be an negative due to being an unsigned int
	#include <iostream>
	int main(){
		for (unsigned int count{ 5 }; count >= 0; --count){
			if (count == 0)
				std::cout << "blastoff! ";
			else
			  std::cout << count << ' ';
		}
		std::cout << '\n';
		return 0;
	}
	
'off-by-one errors': when a loop iterates >1 too many/few times
// < means that 5 will never iterate so only 1, 2, 3, 4 will print
	#include <iostream>
	int main(){
		for (int count{ 1 }; count < 5; ++count){
			std::cout << count << ' ';
		}
		std::cout << '\n';
		return 0;
	}
	
'incorrect operator precedence': 
// ! has higher precedence than y
	#include <iostream>
	int main(){
		int x{ 5 };
		int y{ 7 };
		if (!x > y) // oops: operator precedence issue
			std::cout << x << " is not greater than " << y << '\n';
		else
			std::cout << x << " is greater than " << y << '\n';
		return 0;
	}
	
'precision issues with floating point types':
// floating point cvar doesnt have precision so it rounds
// floating point comparisons can also be problematic
	#include <iostream>
	int main(){
		float f{ 0.123456789f };
		std::cout << f << '\n';
		return 0;
	}

'integer division': division of 2 integers will result in an integer output
// below 5/3 = 1 since the rest are truncated
	#include <iostream>
	int main(){
		int x{ 5 };
		int y{ 3 };
		std::cout << x << " divided by " << y << " is: " << x / y << '\n'; // integer division
		return 0;
	}

'accidental null statements': 
// below if has ; so it executes nothing
	#include <iostream>
	void blowUpWorld(){
		std::cout << "Kaboom!\n";
	}
	int main(){
		std::cout << "Should we blow up the world again? (y/n): ";
		char c{};
		std::cin >> c;
		if (c == 'y');     // accidental null statement here
			blowUpWorld(); // so this will always execute since it's not part of the if-statement
		return 0;
	}
}
/** DETECTING AND HANDLING ERRORS */
{
there are generally 4 ways of handling errors in functions:
	handle within the function
	pass the error back to the caller
	halt the program
	exception
	
is possible, prefer handling it within the function:
either retry till successful || cancel the operation
// this simply ignores and notifies the user of invalid input
	void printIntDivision(int x, int y){
		if (y != 0)
			std::cout << x / y;
		else
			std::cout << "Error: Could not divide by zero\n";
	}

a 'void' function can 'return bool' instead to determine success
	bool printIntDivision(int x, int y){
		if (y == 0){
			std::cout << "Error: could not divide by zero\n";
			return false;
		}
		std::cout << x / y;
		return true;
	}

'sentinel value': a value that has special meaning in context of function
// below 0.0 is a sentinel value for indicating whether the function failed
// The reciprocal of x is 1/x, returns 0.0 if x=0
	constexpr double error_no_reciprocal { 0.0 }; // could also be placed in namespace
	double reciprocal(double x){
		if (x == 0.0)
		   return error_no_reciprocal;
		return 1.0 / x;
	}

'non-recoverable error': will cause program to cease function
in these cases best to terminate the program
best thing is to let 'main()' ret a non-zero value
otherwise 'std::exit' 'std::abort' can work
returning an error can be complicated so C++ has 'exceptions'

'interative applications': user interacts with after running
	games, music apps, etc
'non-interative applications': doesnt require user input to operate
	'tools': ran to get some immediate result ie: naming script
	'services': ran silently in background ie: virus scanner
'std::cout': all conventional user-facing text
'std::cerr': logfile, technical warnings, status updates, percentage completion
'std::cerr': non-interactive programs
}
/** STD::CIN AND HANDLING INVALID INPUT */
{
'input validation': checks whether user input conforms to expectations
3 common methods:
	prevent user typing invalid input
	allow user to input into string, validate, && convert
	lets user input whatever, extract, && handle error cases
string validation can be tricky so extraction is preferred
4 types of common invalid input:
	extraction succeeds, but input is meaningless
	extraction succeeds, but user inputs additional fields
	extraction fails
	extraction succeeds, but user overflows
	
input is meaningless:
// below will output 5 k 7 is in calculator app
	Enter a decimal number: 5
	Enter one of the following: +, -, *, or /: k
	Enter a decimal number: 7
// in this case an input validation can be applied with while
	char getOperator(){
		while (true) {// Loop until user enters a valid input
			std::cout << "Enter one of the following: +, -, *, or /: ";
			char operation{};
			std::cin >> operation;

			// Check whether the user entered meaningful input
			switch (operation){
			case '+':
			case '-':
			case '*':
			case '/':
				return operation; // return it to the caller
			default: // otherwise tell the user what went wrong
				std::cout << "Oops, that input is invalid.  Please try again.\n";
			}
		} // and try again
	}

extraneous input:
	Enter a decimal number: 5*7
>> extracts 5 into x, leaving *7 in buffer 
* is extracted into op, leaving 7 in buffer
7 is extracted into y, program finishes && outputs:
	Enter a decimal number: 5*7
	Enter one of the following: +, -, *, or /: Enter a decimal number: 5 * 7 is 35
// generally its best to ignore extraneous chars
	std::cin.ignore(100, '\n');  // clear up to 100 characters out of the buffer, or until a '\n' character is removed
// if user inputs more than 100 chars
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n')
// std::numeric_limits<std::streamsize>::max returns largest value that can be stored by type std::streamsize
	std::cin.ignore() disables the count check
// this is usually added in a function to avoid boilerplate
	#include <limits> // for std::numeric_limits
	void ignoreLine(){
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
'std::cin.eof()' outputs 'true' assuming last input reached end of input stream
'std::cin.peek()' peeks at the next characcter without extracing it

extraction fails:
	Enter a decimal number: a
in order to fix:
	detect prior extraction failed
	reset 'std::cin' back in normal operation
	remove the input that caused failure
		if (std::cin.fail()) { // If the previous extraction failed
			std::cin.clear(); // Put us back in 'normal' operation mode
			ignoreLine();     // And remove the bad input
		}
'std::cin' has an implicit 'bool conversion'
	if (!std::cin) { // If the previous extraction failed
		std::cin.clear(); // Put us back in 'normal' operation mode
		ignoreLine();     // And remove the bad input
	}

checking 'end-of-file':
EOF is a special error state that means 'no more data available'
'std::cin': no input = simply prompted again
'EOF' can be generated with special OS chars like 'ctrl'
// EOF is an error state, not a char
// OSes have different chars that can trigger an EOF request
// these are sometimes called EOF characters
when user inputs 'EOF' chatacter, 'std::cin''s reaction is OS dependant
'EOF' isnt first: on Windows all 'EOF characters' are ignored besides 'newline'
'EOF' is first: 'EOF error' will be sent, input stream maybe disconnected
'std::cin.clear' can clear 'EOF errors'
assuming input stream disconnected then next input req will generate another 'EOF error'
// ideally use std::cin.eof() and then terminate program
    if (std::cin.eof()) { // If the user entered an EOF
        std::exit(0); // Shut down the program now
    }

extraction succeeds but user overflows numeric value:
	Enter a number between -32768 and 32767: 40000
	Enter another number between -32768 && 32767: The sum is: 32767
in above, 'std::cin' goes into failure mode && assigns closest in-range val
additional inputs are skipped leaving y with 0
}
/** ASSERT AND STATIC_ASSERT */
{
'precondition': any condition that must be 'true' prior to some execution
// ie: 'y != 0' checks y has non-zero val before dividing
	void printDivision(int x, int y){
		if (y == 0) { // handle
			std::cerr << "Error: Could not divide by zero\n";
			return; // bounce the user back to the caller
		}
		// We now know that y != 0
		std::cout << static_cast<double>(x) / y;
	}
'invariant': any condition that must be 'true' when code runs
'postcondition': any condition that must be 'true' after code runs

'assertion': is an expression that's true unless theres a bug
assuming 'true': 'assertion' does nothing
assuming 'false': error message is displayed && std::abort() is called
runtime 'assertion' are implemented via assert() macro in <cassert>
#include <cassert> // for assert()
#include <cmath> // for std::sqrt
#include <iostream>

double calculateTimeUntilObjectHitsGround(double initialHeight, double gravity){
  assert(gravity > 0.0); // The object won't reach the ground unless there is positive gravity.
  if (initialHeight <= 0.0){
    // The object is already on the ground. Or buried.
    return 0.0;
  }
  return std::sqrt((2.0 * initialHeight) / gravity);
}
'assert' are usually used to validate function params
// assertions can be used liberally throughout code
'assert' messages be rather undescriptive
// a string literal be tacked on at the end to add more info:
	assert(found && "Car could not be found in database");
// this works because a string literal is always true
'assert' also used to document cases that werent implmented
	assert(moved && "Need to handle case where student was just moved to another classroom");
'assert' macro comes with some performance cost
'assert' generally shouldnt be found in production code
preprocessor macro 'NDEBUG' turns off all asserts
// most IDEs have this by default for production builds
'static_assert' is checked at compile-time rather than runtime
// static_assert condition must be a const expression
// static_assert can be placed anywhere (even global namespace)
// there is no runtime cost to static_assert
// if possible, use static_assert over assert
'assert' vs 'error handling':
	'assert': programming errors during dev
	'assert': doesnt allow recovery after errors
	'assert': typically compiled out of release builds
	'error handling': handle error cases in a release build
	'error handling': handles different behavior differently
some other general rules about 'assert':
	'assert': shouldnt have any side effects
	'assert': triggers when abort is called
	'abort': triggers termination immediately with no cleanup
	'abort': should only be used when corruption isnt likely
}
	