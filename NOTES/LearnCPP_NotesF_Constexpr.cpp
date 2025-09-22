/** CONSTEXPR FUNCTIONS */
{
'constexpr' functions allow the usage of 'constant expressions'
	#include <iostream>
	constexpr double calcCircumference(double radius) // now a constexpr function
	{
		constexpr double pi { 3.14159265359 };
		return 2.0 * pi * radius;
	}
	int main(){
		constexpr double circumference { calcCircumference(3.0) }; // now compiles
		std::cout << "Our circle has circumference " << circumference << "\n";
		return 0;
	}
'constexpr' functions can be evaled at compile time:
	call to 'constexpr' must have args that are known at compile time
	statements && expressions within 'constexpr' function must eval at compile time
'constexpr' can be evaled at runtime as well:
	#include <iostream>
	constexpr int greater(int x, int y){
		return (x > y ? x : y);
	}
	int main(){
		int x{ 5 }; // not constexpr
		int y{ 6 }; // not constexpr
		std::cout << greater(x, y) << " is greater!\n"; // will be evaluated at runtime
		return 0;
	}
}
/** CONSTEXPR FUNCTIONS (PART 2) */
{
'constexpr function' evals at compile time when necessary
// in other cases the compiler decides:
	#include <iostream>
	constexpr int getValue(int x){
		return x;
	}
	int main(){
		int x { getValue(5) }; // may evaluate at runtime or compile-time
		return 0;
	}
above, initialization of x isnt required to be 'constexpr'
hence, compiler gets to decide whether its evaled at runtime/compile time
'constexpr function' params arent 'constexpr' && cant be marked as such
'constexpr function' are inherently 'inline'
// hence, compiler should see full definition of constexpr function
// use headers for multifile constexpr functions and write it at top of cpp file for single use
}
/** CONSTEXPR FUNCTIONS (PART 3) AND CONSTEVAL */
{
C++20 introduces 'consteval' which forces a function to be compile time
// technically consteval params arent constexpr either
there is currently no way of checking whether a 'constexpr' call evals at runtime/compiletime
'std::is_constant_evaluated()' moreso checks
	the compiler is forced to eval at compile time 
	AND NOT
	tis evaluating at compile time
C++ 'if consteval' replaces 'std::is_constant_evaluated()'
	they evaluate the same way, just nicer syntax
can use a 'consteval function' to wrap a 'constexpr' function call to force it to compile at runtime
	consteval auto CONSTEVAL(auto value){
		return value;
	}
	// This function returns the greater of the two numbers if executing in a constant context
	// and the lesser of the two numbers otherwise
	constexpr int compare(int x, int y) // function is constexpr
	{
		if (std::is_constant_evaluated())
			return (x > y ? x : y);
		else
			return (x < y ? x : y);
	}
	int main(){
		std::cout << CONSTEVAL(compare(5, 6)) << '\n';       // will execute at compile-time
		return 0;
	}
	// it returns by value, but is resolved at compiletime anyways
}
/** CONSTEXPR FUNCTIONS (PART 4) */
{
'non-const' vars can be manipulated in a 'constexpr' function
// despite this, constexpr args can be passed into other constexpr functions
'non-constexpr functions' can be called, solong as its never called in a constant expressions
	#include <type_traits> // for std::is_constant_evaluated
	constexpr int someFunction(){
		if (std::is_constant_evaluated()) // if evaluating in constant context
			return someConstexprFcn();
		else
			return someNonConstexprFcn();
	} // generally avoid non-constexpr function calls in a constexpr function
	// if needed, then conditionalize with std::is_constant_evaluated() or if consteval
a 'pure function' meets the following criteria:
	function always returns the same result given the same args
	function has no side effects
	// pure functions should generally be constexpr
	// modifying a static local var is a side effect as it persists across calls
}

