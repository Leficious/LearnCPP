/** CONTROL FLOW INTRODUCTION */
{
sequence of statements in execution is called 'execution path'
'control flow statements' alter the control flow
}
/** IF STATEMENTS AND BLOCKS */
{
'if statements' pass assuming a condition evaluates to 'true'
'else' && 'else if' follow the chain upon 'false'
multiple statements can be written in blocks
// stylistic preference: use blocks or not
// for single lines write on same line, multi-line use blocks
}
/** COMMON IF STATEMENT PROBLEMS */
{
nesting 'if-statements' is allowed
a 'dangling-else' can occur within nested'if-statements'
	#include <iostream>
	int main(){
		std::cout << "Enter a number: ";
		int x{};
		std::cin >> x;
		if (x >= 0) // outer if-statement
			// it is bad coding style to nest if statements this way
			if (x <= 20) // inner if-statement
				std::cout << x << " is between 0 and 20\n";
		// which if statement does this else belong to?
		else
			std::cout << x << " is negative\n";
		return 0;
	}
	// in this case else pairs up with the last unmatched if-statement
	// this can be avoided via enclosing the if-statements in a block
	#include <iostream>
	int main(){
		std::cout << "Enter a number: ";
		int x{};
		std::cin >> x;
		if (x >= 0){
			if (x <= 20)
				std::cout << x << " is between 0 and 20\n";
			else // attached to inner if statement
				std::cout << x << " is greater than 20\n";
		}
		else // attached to outer if statement
			std::cout << x << " is negative\n";
		return 0;
	}
	
'if statements' can && should be flattened when possible
'null statements' = nothing statement
they are used when the languages require a statement
	if (x > 10)
		; // this is a null statement
}
/** CONSTEXPR IF STATEMENTS */
{
'if-statements' are generally evaluated at runtime
doing a 'constexpr' 'if-statement' is wasteful because itll always evaluate to the same result
'const-expr if-statements' were introduced in C++17
// they determine and refactor the code at compile to so this:
	int main(){
		constexpr double gravity{ 9.8 };
		if constexpr (gravity == 9.8) // now using constexpr if
			std::cout << "Gravity is normal.\n";
		else
			std::cout << "We are not on Earth.\n";
		return 0;
	}
// compiles to this:
	int main(){
	constexpr double gravity{ 9.8 };
	std::cout << "Gravity is normal.\n";
	return 0;
	}
	// if the if-statement uses a constexpr var generally use constexpr-if
}
/** SWITCH STATEMENT BASICS */
{
multiple 'if statements' can be chained, but doing so can be messy
in cases where a single variable is checked multiple times a 'switch-statement' can be used
// switch statements only allow integral types: int, char, bool, short, long int, etc.
	void printDigitName(int x){
		switch (x){
		// case labels are conventionally not indented
		case 1:
			std::cout << "One";
			return;
		case 2:
			std::cout << "Two";
			return;
		case 3:
			std::cout << "Three";
			return;
		default:
			std::cout << "Unknown";
			return;
		}
	}
	// if the expression's value matches any of the case labels, then everything afterwards executes
	// if no value matches then the default case is used
	// if there is neither a default case nor a matching value then the switch is skipped
	// default is optional, generally placed in last block when present
	// a break statement can be used to stop execution beyond a certain case
	// generally case statements should end in a break or return
	
'switch' is generally better when we want to evaluate to a small number of values
'if-else' offers more direct control && flexibility:
	testing values ie (x > 5)
	multiple conditions (x > 5 && x < 10)
	non-integral type support (x == 3.0)
	the expression evalutes to 'bool'
}
/** SWITCH FALLTHROUGH AND SCOPING */
{
when a statement doesnt have 'break' || 'return' it can result in a 'fallthrough'
everything after the initial 'case statement' will execute in sequence
in C++17 when 'fallthrough' is desirable '[[fallthrough]]' should be used
'[[fallthrough]]' is an 'attribute'
'attributes' were added in C++17 to provide the compiler additional information about code
'[[fallthrough]]' modifies a 'null-statement' to indicate that 'fallthrough' is desirable
// this is mainly to avoid throwing a warning
tests can be combined via logical 'or operator'
	bool isVowel(char c){
		return (c=='a' || c=='e' || c=='i' || c=='o' || c=='u' ||
			c=='A' || c=='E' || c=='I' || c=='O' || c=='U');
	}
	
// this is hard to read so an if can be preferred
// [[fallthrough]] is not necessary here as no statement is entered
	bool isVowel(char c){
		switch (c){
		case 'a': // if c is 'a'
		case 'e': // or if c is 'e'
		case 'i': // or if c is 'i'
		case 'o': // or if c is 'o'
		case 'u': // or if c is 'u'
		case 'A': // or if c is 'A'
		case 'E': // or if c is 'E'
		case 'I': // or if c is 'I'
		case 'O': // or if c is 'O'
		case 'U': // or if c is 'U'
			return true;
		default:
			return false;
		}
	}
	
'case labels' dont end scope, unlike an 'if-statement' block
	switch (1){
	case 1: // does not create an implicit block
		foo(); // this is part of the switch scope, not an implicit block to case 1
		break; // this is part of the switch scope, not an implicit block to case 1
	default:
		std::cout << "default case\n";
		break;
	}

vars can be declared within a 'switch':
// they can NOT be initialized
	switch (1){
		int a; // okay: definition is allowed before the case labels
		int b{ 5 }; // illegal: initialization is not allowed before the case labels
	case 1:
		int y; // okay but bad practice: definition is allowed within a case
		y = 4; // okay: assignment is allowed
		break;
	case 2:
		int z{ 4 }; // illegal: initialization is not allowed if subsequent cases exist
		y = 5; // okay: y was declared above, so we can use it here too
		break;
	case 3:
		break;
	}
}
/** GOTO STATEMENTS */
{
'goto' is an unconditional jump to another spot in code
the spot is determined by a 'statement label'
// statement label has function scope
// function scope: label is visible in function even before declaration
// just as goto can jump backward, it can jump forward as well
	#include <iostream>
	#include <cmath> // for sqrt() function
	int main(){
		double x{};
	tryAgain: // this is a statement label
		std::cout << "Enter a non-negative number: ";
		std::cin >> x;
		if (x < 0.0)
			goto tryAgain; // this is the goto statement
		std::cout << "The square root of " << x << " is " << std::sqrt(x) << '\n';
		return 0;
	}

'goto' leads to arbritrary jumping aka 'spaghetti code'
practice: generally avoid 'goto' unless alternative is far less readable (nested loop exit)
}
/** INTRODUCTION TO LOOPS AND WHILE STATEMENTS */
{
loops are 'control flow' constructs that allow code to execute repeatedly
'while' is the simplest loop type: 'while' something is 'true' code executes
	#include <iostream>
	int main(){
		int count{ 1 };
		while (count <= 10){
			std::cout << count << ' ';
			++count;
		}
		std::cout << "done!\n";
		return 0;
	}
'while' thats always 'true' = a intentional infinite loop ie: while (true){}
// the only way to exit would be a break, exit, goto, exception, or killing the program
// this is used for things that need to run continously
a 'loop var' is whats used to determine the number of times to loop
common names are: 'j' 'i' 'k' // this is from fortran
some devs prefer 'iii' 'jjj' 'kkk' // easier to search in a program
others times 'count' 'index' // more explicit
integral 'loop var' should generally be 'signed'
doing something every n iterations can be done via the '%' op
	#include <iostream>
	// Iterate through every number between 1 and 50
	int main(){
		int count{ 1 };
		while (count <= 50){
			// print the number (pad numbers under 10 with a leading 0 for formatting purposes)
			if (count < 10){
				std::cout << '0';
			}
			std::cout << count << ' ';
			// if the loop variable is divisible by 10, print a newline
			if (count % 10 == 0){
				std::cout << '\n';
			}
			// increment the loop counter
			++count;
		}
		return 0;
	}
	
// loops can be nested
	#include <iostream>
	void printUpto(int outer){
		int inner{ 1 };
		while (inner <= outer){
			std::cout << inner << ' ';
			++inner;
		}
	} // inner destroyed here
	int main(){
		// outer loops between 1 and 5
		int outer{ 1 };
		while (outer <= 5){
			printUpto(outer);
			// print a newline at the end of each row
			std::cout << '\n';
			++outer;
		}
		return 0;
	}
// instead of a function, loops can be put directly in other loops as well
// below is the same function as above
	#include <iostream>
	int main()
	{
		// outer loops between 1 and 5
		int outer{ 1 };
		while (outer <= 5)
		{
			int inner{ 1 };
			while (inner <= outer)
			{
				std::cout << inner << ' ';
				++inner;
			}
			// print a newline at the end of each row
			std::cout << '\n';
			++outer;
		} // inner destroyed here
		return 0;
	}
}
/** DO WHILE STATEMENTS */
{
'do while' always executes at least once
after executing, its checks the condition
condition == 'true' the execution loops again
// do while should be used sparingly and regular whiles should be preferred
	#include <iostream>
	int main(){
		int selection {};
		do{
			std::cout << "Please make a selection: \n";
			std::cout << "1) Addition\n";
			std::cout << "2) Subtraction\n";
			std::cout << "3) Multiplication\n";
			std::cout << "4) Division\n";
			std::cin >> selection;
		}
		while (selection < 1 || selection > 4);
		// do something with selection here
		std::cout << "You selected option #" << selection << '\n';
		return 0;
	}
}
/** FOR STATEMENTS */
{
'for-statements' are the most used loop in C++
2 types: classic 'for' && newer 'for-each'
// for syntax:
// in general prefer var scope within the for loop instead outside
	for (init-statement; condition; end-expression)
	   statement;
// equivalent while syntax:
	{
		init-statement; // used to define variables used in the loop
		while (condition)
		{
			statement; 
			end-expression; // used to modify the loop variable prior to reassessment of the condition
		}
	}
1: init statement is executed; only happens once
// initialized var has loop scope so is alive for as long as the loop
2: condition is evaluated: 'true' then execute statement | 'false' terminate loop
3: 'end expression' is evaluated (usually increment/decrement) then goes back to step 2
'<>' should be preferred over '!=' as the latter only covers a single value (that can be jumped over)
'for loops' can be written with omitted statements
// this will execute just fine
    int i{ 0 };
    for ( ; i < 10; ) // no init-statement or end-expression
    {
        std::cout << i << ' ';
        ++i;
    }
// this will produce an infinite loop (same as a while(true))
// C++ standard specifies that an omitted conditional should be treated as true 
	for (;;)
    statement;
// for loops can iterate over multiple vars
	#include <iostream>
	int main(){
		for (int x{ 0 }, y{ 9 }; x < 10; ++x, --y)
			std::cout << x << ' ' << y << '\n';
		return 0;
	}
// for loops can also be nested in other loops
	#include <iostream>
	int main(){
		for (char c{ 'a' }; c <= 'e'; ++c) // outer loop on letters
		{
			std::cout << c; // print our letter first

			for (int i{ 0 }; i < 3; ++i) // inner loop on all numbers
				std::cout << i;
			std::cout << '\n';
		}
		return 0;
	}
in general prefer 'while' loops when there is no obvious counter
prefer 'for' when there is an obvious counter
}
/** BREAK AND CONTINUE */
{
'break' can also end loops
'break' ends the loop; 'return' ends the function
'continue' ends the current loop interation && stays in the loop
// continue usually used at top of loop to skip something
// break and continue should be used judiciously to help optimize loops
// early returns can be utilized when they simplify logic
}
/** HALTS (EXITING YOUR PROGRAM EARLY) */
{
'halt' terminates the program
halts are implemented as functions rather than keywords
'std::exit' causes the program to terminiate normally
// normal termination = the program exited in an expected way (hence status code)
// std::exit does cleanup such as destroying static objects
// std::exit is called implicitly after main() returns 
by including 'cstdlib' 'std::exit' can be called early to terminate the program early
'std::exit' doesnt clean up local vars || up the callstack
hence, its good practice to cleanup before exiting early
// modern OSes generally clean up nicely, but:
	// its good practice to clean up allocated memory
	// cleanup of caching, logs, etc may be necessary for predicatable behavior
'std::atexit' allows the user to bind a function to 'std::exit'
// this is usually done at the beginning of the program
	#include <cstdlib> // for std::exit()
	#include <iostream>
	void cleanup(){
		// code here to do any kind of cleanup required
		std::cout << "cleanup!\n";
	}
	int main(){
		// register cleanup() to be called automatically when std::exit() is called
		std::atexit(cleanup); // note: we use cleanup rather than cleanup() since we're not making a function call to cleanup() right now
		std::cout << 1 << '\n';
		std::exit(0); // terminate and return status code 0 to operating system
		// The following statements never execute
		std::cout << 2 << '\n';
		return 0;
	}
	
since 'std::exit' is called upon 'main()' returning, 'std::atexit' is also called then
the function returned must have no params && no 'return value'
multiple functions can be registered via 'std::atexit()'
// they are executed in reverse order (last function goes first)
'std::exit' may cause crashes on multi-threaded programs when it deletes 'static objects'
'std_quick_exit()' && 'std::at_quick_exit' terminates the program, but doesnt clean up statics
'std::abort()' causes 'abnormal termination' 
// this means the program encountered some unusual error ie dividing by 0
// abort does not do any cleanup
'std::terminate()' is usually used with 'exceptions' 
// though terminate can be called explicitly its usually called implicitly
// implictly called when an exception isnt handled
// std::terminate calls std::abort by default
halting shouldnt generally be used. local object destruction is very important in C++
'Exceptions' are a better mechanism to handle error cases
}
/** INTRODUCTION TO RANDOM NUMBER GENERATION */
{
'algorithm': finite sequence of instructions that can be followed to produce some result
an algorithm is 'stateful' when it retains some information across calls
a 'stateless' algorithm doesnt store any info && must be given it
'deterministic' means that based on given input 'x' it will always produce 'y'
a state is the internal vars (that change) used to drive the algorithm
// below is a stateful deterministic algorithm that increments an input by 1
	#include <iostream>
	int plusOne(){
		static int s_state { 3 }; // only initialized the first time this function is called
		// Generate the next number
		++s_state;      // first we modify the state
		return s_state; // then we use the new state to generate the next number in the sequence
	}
	int main(){
		std::cout << plusOne() << '\n';
		std::cout << plusOne() << '\n';
		std::cout << plusOne() << '\n';
		return 0;
	}

'pseudo-random number generator': an algorithm that generates numbers simulate randomness
// a basic PRNG:
	#include <iostream>
	unsigned int LCG16() {
		static unsigned int s_state{ 0 }; // only initialized the first time this function is called

		// We modify the state using large constants and intentional overflow to make it hard
		// for someone to casually determine what the next number in the sequence will be.

		s_state = 8253729 * s_state + 2396403; // first we modify the state
		return s_state % 32768; // then we use the new state to generate the next number in the sequence
	}
	int main(){
		for (int count{ 1 }; count <= 100; ++count){
			std::cout << LCG16() << '\t';

			if (count % 10 == 0)
				std::cout << '\n';
		}
		return 0;
	}
'LCG16()' is also 'deterministic': entering value 'x', 'y' will always be the result
in order to generate different output sequences, the intial state of a 'PRNG' needs to vary
// this is called a random seed or seed for short
// when the initial state of a PRNG is set it is "seeded" 
// all values that a PRNG produce are deterministically calculated from the seed values
an ideal seed should have the following characteristics:
	contain as many bits as the state of the PRNG
	each bit in the seed should be randomized independently
	should contain a good mix of 1s & 0s across all bits
	there should be no bits that are always 0 || 1
	the seed should have a low correlation with previous seeds
what makes a good PRNG continued:
	1: the PRNG should generate each number with approximately the same probability
	// this is called distribution uniformity; this can be checked via a histogram
	2: the method by which the next number in the sequence is generated shouldn’t be predictable
	3: the PRNG should have a good dimensional distribution of numbers
	// should generate different ranges and types of numbers at "random"
	4: the PRNG should have a high period on all seeds
	// all PRNGS are periodic (so eventually theyll repeat themselves)
	// the longer it takes to repeat, the better the PRNG
	5: the PRNG should be efficient
	// generally PRNGs have states under 4096 bytes
6 PRNG families in C++20:
	minstd_rand: 			linear congruential generator
	mt19937: 				mersenne twister
	ranlux24: 				subtract && carry
	knuth_b: 				shuffled linear congruential generator
	default_random_engine: 	any of the above
	rand():					linear congruential generator
knuth_b, default_random_engine, rand() should never be used in C++
mersenne twister is the only decent C++ out-of-box PRNG
// most applications, mersenne twister is fine
// issue is that its results can be predicted after 624 generated numbers
// for non-predictable systems like statistical sims and cryptography consider the following:
// Xoshiro, Wyrand, Chacha
}
/** GENERATING RANDOM NUMBERS USING MERSENNE TWISTER */
{
to access randomization in C++ include the '<random>' header
'mt19937': generates 32-bit 'unsigned integers'
'mt19937_64': generates 64-bit 'unsigned integers'
// mt19937 and mt19937_64 are types that can be instantiated
// name() is concise way of writing mt.operator()
	#include <iostream>
	#include <random> // for std::mt19937
	int main(){
		std::mt19937 mt{}; // Instantiate a 32-bit Mersenne Twister
		for (int count{ 1 }; count <= 40; ++count){
			std::cout << mt() << '\t'; // generate a random number
			if (count % 5 == 0)
				std::cout << '\n';
		}
		return 0;
	}
a 'random number distribution' converts PRNGs outputs into a range of other numbers
uniform distribution is a RND that produces outputs with equal probability
// a distributor is a functor that takes a generator, which in this case calls mt() internally
	#include <iostream>
	#include <random> // for std::mt19937 and std::uniform_int_distribution
	int main(){
		std::mt19937 mt{};
		// Create a reusable random number generator that generates uniform numbers between 1 and 6
		std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };
		for (int count{ 1 }; count <= 40; ++count){
			std::cout << die6(mt) << '\t'; // generate a roll of the die here
			// If we've printed 10 numbers, start a new row
			if (count % 10 == 0)
				std::cout << '\n';
		}
		return 0;
	}
because all PRNGs are deterministic, above examples will generate the same numbers when run
// this is due to mt19937 being initialized with the same value each time
// catch22: we need a random number to drive our random number
// using system clock and system random device are good alternatives
'std::time' is commonly used in older code
C++ also has a chrono library with various clocks
	#include <iostream>
	#include <random> // for std::mt19937
	#include <chrono> // for std::chrono
	int main(){
		// Seed our Mersenne Twister using steady_clock
		std::mt19937 mt{ static_cast<std::mt19937::result_type>(
			std::chrono::steady_clock::now().time_since_epoch().count()
			) };
		// Create a reusable random number generator that generates uniform numbers between 1 and 6
		std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };
		// Print a bunch of random numbers
		for (int count{ 1 }; count <= 40; ++count){
			std::cout << die6(mt) << '\t'; // generate a roll of the die here
			// If we've printed 10 numbers, start a new row
			if (count % 10 == 0)
				std::cout << '\n';
		}
		return 0;
	}
	// the downside is that if program is run in quick succession then seeds wont be very different
'std::chrono::high_resolution_clock' is a popular choice instead of 'std::chrono::steady_clock'
'std::chrono::high_resolution_clock' uses the most granular unit of time
// std::chrono::high_resolution_clock may use system time, which can be rolled back by users
// std::chrono:steady_time is less granular but guarantees users cant adjust it
std::chrono::steady_clock::now().time_since_epoch().count()
std::chrono::steady_clock: 'static type'
now(): returns a time_point with the current wall clock time; 
time_since_epoch(): gets the time between time_point && the epoch (jan 1, 1970)
count(): extracts the raw number of ticks as a numeric type like 'long long'

std::random_device is an implementation-defined PRNG
std::random_device asks the OS to get a pseudo-random number (depends on the OS)
// std::random device{}() creates a value initializerd temp obj of type std::random_device
// () then calls operator() on that temp obj which returns a rand value
	#include <iostream>
	#include <random> // for std::mt19937 and std::random_device
	int main(){
		std::mt19937 mt{ std::random_device{}() };
		// Create a reusable random number generator that generates uniform numbers between 1 and 6
		std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };
		// Print a bunch of random numbers
		for (int count{ 1 }; count <= 40; ++count){
			std::cout << die6(mt) << '\t'; // generate a roll of the die here
			// If we've printed 10 numbers, start a new row
			if (count % 10 == 0)
				std::cout << '\n';
		}
		return 0;
	}
	// std::random_device isnt required to be non-deteministic 
	// on some systems it could produce the same sequence
	// due to it being implentation defined, usually random_device is used to seed other PRNGs

generally avoid reseeding:
// a common mistake: 
// this will reinitialize a new marsenne twister each time with a new random device as well
// is inperformant and may mess up randomness
	#include <iostream>
	#include <random>
	int getCard(){
		std::mt19937 mt{ std::random_device{}() }; // this gets created and seeded every time the function is called
		std::uniform_int_distribution card{ 1, 52 };
		return card(mt);
	}
	int main(){
		std::cout << getCard() << '\n';
		return 0;
	}
	
marsenne twister internal state needs 19937 bits
in the above example where clock/device seed the mt19937 it is only a single integer
we initialize 624 integers with 1
// this results in underseeding
'std::seed_seq' can help:
the idea is to use 'random_device' to generate numbers into 'std::seed_seq'
which then floods the rest with additional 'random' seed data
// dont use 624 instances of random_device: this will be slow and exhaust the pool of rand numbers
	#include <iostream>
	#include <random>
	int main(){
		std::random_device rd{};
		std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() }; // get 8 integers of random numbers from std::random_device for our seed
		std::mt19937 mt{ ss }; // initialize our Mersenne Twister with the std::seed_seq
		// Create a reusable random number generator that generates uniform numbers between 1 and 6
		std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };
		// Print a bunch of random numbers
		for (int count{ 1 }; count <= 40; ++count){
			std::cout << die6(mt) << '\t'; // generate a roll of the die here
			// If we've printed 10 numbers, start a new row
			if (count % 10 == 0)
				std::cout << '\n';
		}
		return 0;
	}
when a PRNG is given a bad seed/is underseeded the results can be bad
some PRNGs benefit from 'warm-up'
'warm-up': a technique where results are generated N times && discarded
'seed_seq' performs an automatic warm-up
}
/** GLOBAL RANDOM NUMBERS (RANDOM.H) */
{
the best thing here is to create a global random number generator object (inside a 'namespace')
// this is a rare case where using non-const global vars is acceptable
	#ifndef RANDOM_MT_H
	#define RANDOM_MT_H
	#include <chrono>
	#include <random>
	// This header-only Random namespace implements a self-seeding Mersenne Twister.
	// Requires C++17 or newer.
	namespace Random{
		// Returns a seeded Mersenne Twister
		// Note: we'd prefer to return a std::seed_seq (to initialize a std::mt19937), but std::seed can't be copied, so it can't be returned by value.
		// Instead, we'll create a std::mt19937, seed it, and then return the std::mt19937 (which can be copied).
		inline std::mt19937 generate()
		{
			std::random_device rd{};

			// Create seed_seq with clock and 7 random numbers from std::random_device
			std::seed_seq ss{
				static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
					rd(), rd(), rd(), rd(), rd(), rd(), rd() };

			return std::mt19937{ ss };
		}

		// Here's our global std::mt19937 object.
		// The inline keyword means we only have one global instance for our whole program.
		inline std::mt19937 mt{ generate() }; // generates a seeded std::mt19937 and copies it into our global object

		// Generate a random int between [min, max] (inclusive)
			// * also handles cases where the two arguments have different types but can be converted to int
		inline int get(int min, int max)
		{
			return std::uniform_int_distribution{min, max}(mt);
		}

		// The following function templates can be used to generate random numbers in other cases
		// Generate a random value between [min, max] (inclusive)
		// * min and max must have the same type
		// * return value has same type as min and max
		// * Supported types:
		// *    short, int, long, long long
		// *    unsigned short, unsigned int, unsigned long, or unsigned long long
		// Sample call: Random::get(1L, 6L);             // returns long
		// Sample call: Random::get(1u, 6u);             // returns unsigned int
		template <typename T>
		T get(T min, T max){
			return std::uniform_int_distribution<T>{min, max}(mt);
		}

		// Generate a random value between [min, max] (inclusive)
		// * min and max can have different types
			// * return type must be explicitly specified as a template argument
		// * min and max will be converted to the return type
		// Sample call: Random::get<std::size_t>(0, 6);  // returns std::size_t
		// Sample call: Random::get<std::size_t>(0, 6u); // returns std::size_t
		// Sample call: Random::get<std::int>(0, 6u);    // returns int
		template <typename R, typename S, typename T>
		R get(S min, T max){
			return get<R>(static_cast<R>(min), static_cast<R>(max));
		}
	}
	#endif
	'inline' allowed above header to conform to the ODR
}