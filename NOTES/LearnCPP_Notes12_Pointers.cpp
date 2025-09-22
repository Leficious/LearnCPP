/** VALUE CATEGORIES (LVALUES AND RVALUES) */
{
'value category' exp resolves to val, func, obj
<C++11: 2 categories, >C++11: 5 categories
	('lvalue' && 'rvalue') && ('gvalue' && 'prvalue' && 'xvalue')(C++11)
'lvalue': evals to an identifiable obj || func
// C++ standard says it resolves to a value with an 'identity'
// identities can usually be accessed via
	identifier
	reference
	pointer
	// usually longer lifetime than single exp or statement
		int main(){
			int x { 5 }; // 5 is a literal 
			int y { x }; // x is an lvalue expression
			return 0;
		}
	// 2 types of lvalue:
	'modifiable' && 'non-modifiable'
		int main(){
			int x{};
			const double d{};
			int y { x }; // x is a modifiable lvalue expression
			const double e { d }; // d is a non-modifiable lvalue expression
			return 0;
		}

'rvalue': an expression thats isnt an 'lvalue'
// rvalues arent identifiable && must be used immediately
// some common rvalues:
	literals (c-style strings are an exception)
	returns
	int return5(){
		return 5;
	}
	int main(){
		int x{ 5 }; // 5 is an rvalue expression
		const double d{ 1.2 }; // 1.2 is an rvalue expression
		int y { x }; // x is a modifiable lvalue expression
		const double e { d }; // d is a non-modifiable lvalue expression
		int z { return5() }; // return5() is an rvalue expression (since the result is returned by value)
		int w { x + 1 }; // x + 1 is an rvalue expression
		int q { static_cast<int>(d) }; // the result of static casting d to an int is an rvalue expression
		return 0;
	}
	
operators expect 'rvalues' unless otherwise speced
assignment op= needs left val to be 'lvalue' && right to be 'rvalue'
// following can be done through conversion of lval to rval
	int main(){
		int x{ 1 };
		int y{ 2 };
		x = y; // y is not an rvalue, but this is legal
		return 0;
	}
	// y converts to evaluate to produce a rvalue
all 'lvalue' can implicitly convert to 'rvalue'
'rvalue' cannot implicitly convert to 'lvalue'
}
/** LVALUE REFERENCES */
{
reference: alias existing object
once defined: any op on reference is applied to object being referenced
2 types of refs: 'lval refs' && 'rval refs'
'lval ref':
	// regular types
	int        // a normal int type (not an reference)
	int&       // an lvalue reference to an int object
	double&    // an lvalue reference to a double object
	const int& // an lvalue reference to a const int object
// can create an lval reference var
	#include <iostream>
	int main(){
		int x { 5 };    // x is a normal integer variable
		int& ref { x }; // ref is an lvalue reference variable that can now be used as an alias for variable x
		std::cout << x << '\n';  // print the value of x (5)
		std::cout << ref << '\n'; // print the value of x via ref (5)
		return 0;
	}
	// type& name || type &name = no difference
	// modern convention prefers type&

references must be initialized as well 'ref initialization'
when ref is initialized with object it is 'bound' aka 'reference binding'
'nonconst lval references' can only be bound to modifiable lval
	int main(){
		int x { 5 };
		int& ref { x };         // okay: non-const lvalue reference bound to a modifiable lvalue
		const int y { 5 };
		int& invalidRef { y };  // invalid: non-const lvalue reference can't bind to a non-modifiable lvalue
		int& invalidRef2 { 0 }; // invalid: non-const lvalue reference can't bind to an rvalue
		return 0;
	}
	// lval references to void are disallowed

in most cases a ref val only binds to objects of the same type
// compiler will try to do implicit conversion
	int main(){
		int x { 5 };
		int& ref { x };            // okay: referenced type (int) matches type of initializer
		double d { 6.0 };
		int& invalidRef { d };     // invalid: conversion of double to int is narrowing conversion, disallowed by list initialization
		double& invalidRef2 { x }; // invalid: non-const lvalue reference can't bind to rvalue (result of converting x to double)
		return 0;
	}

once initialized, refs cannot be reseated (changed to ref sth other)
	#include <iostream>
	int main(){
		int x { 5 };
		int y { 6 };
		int& ref { x }; // ref is now an alias for x
		ref = y; // assigns 6 (the value of y) to x (the object being referenced by ref)
		// The above line does NOT change ref into a reference to variable y!
		std::cout << x << '\n'; // user is expecting this to print 5
		return 0;
	}
	// this will print 6

references share same scope as normal vars
with 1 exception, ref && referent lifetimes are independant
	a ref can be destroyed before its referent
	a referent can be destroyed before its reference
a reference dying before a referent has no impact
a referent dying can leave a 'dangling reference'
// this leads to undefined behavior

a reference isnt actually an object
// just an alias to an object that doesnt take up memory itself
// generally compiler will simply replace with referrent
	int var{};
	int& ref1{ var };  // an lvalue reference bound to var
	int& ref2{ ref1 }; // an lvalue reference bound to var
	// in this case ref2 actually simply binds to var 
}
/** LVALUE REFERENCES TO CONST */
{
'lval ref' can only bind to modifiable vals
to bind to 'const vals' must use a 'const ref'
	int main(){
		const int x { 5 };    // x is a non-modifiable lvalue
		const int& ref { x }; // okay: ref is a an lvalue reference to a const value
		return 0;
	}
	// can view but not modify the const
	// const ref can be used with modifiable val, ref will remain read only, val stays modifiable
	// in general prefer const lval references to non-const

strangely, 'const lval ref' can bind to 'rval'
// a temp obj is created, ref is bound to that temp obj
// const reference will extend the lifetime of the rval to the same as the ref
// rval conversions are also allowed:
	#include <iostream>
	int main(){
		// case 1
		const double& r1 { 5 };  // temporary double initialized with value 5, r1 binds to temporary
		std::cout << r1 << '\n'; // prints 5
		// case 2
		char c { 'a' };
		const int& r2 { c };     // temporary int initialized with value 'a', r2 binds to temporary
		std::cout << r2 << '\n'; // prints 97 (since r2 is a reference to int)
		return 0;
	}
	// this can lead to interesting scenarios:
	// implicit conversion created a temp value and bind to that
	// any changes to the original input will not be visible on the binding
'constexpr ref' can only bind to 'static objects'
// this allowed them to be used in constant expressions
// given limiations, generally constexpr refs not really used
	int main(){
		static const int s_x { 6 }; // a const int
		[[maybe_unused]] constexpr const int& ref2 { s_x }; // needs both constexpr and const
		return 0;
	} // constexpr refers to ref, const int is the type
}
/** PASS BY LVALUE REFERENCE */
{
some objects are expensive to copy:
	#include <iostream>
	#include <string>
	void printValue(std::string y){
		std::cout << y << '\n';
	} // y is destroyed here
	int main(){
		std::string x { "Hello, world!" }; // x is a std::string
		printValue(x); // x is passed by value (copied) into parameter y (expensive)
		return 0;
	}

can pass by reference: 
	#include <iostream>
	#include <string>
	void printValue(std::string& y) // type changed to std::string&
	{
		std::cout << y << '\n';
	} // y is destroyed here
	int main(){
		std::string x { "Hello, world!" };
		printValue(x); // x is now passed by reference into reference parameter y (inexpensive)
		return 0;
	}
	// now instead of accessing copy of x, it refs x directly
// doing this allows actual modification via the param:
	#include <iostream>
	void addOne(int& y) // y is bound to the actual object x
	{
		++y; // this modifies the actual object x
	}
	int main(){
		int x { 5 };
		std::cout << "value = " << x << '\n';
		addOne(x);
		std::cout << "value = " << x << '\n'; // x has been modified
		return 0;
	}
pass by 'non-const ref' can only take in 'non-const val'
}
/** PASS BY CONST LVALUE REFERENCE */
{
a 'const lval ref' can bind to any val
// this offers the same benefit of not making a copy, while also ensuring no change can be made
// generally favor passing by const ref instead of non-const ref
implicit conversion can occur, but should be avoided
// the point of using pass-by-ref is to avoid copy, conversion produces a copy, which defeats the purpose
pass-by-ref params can be mixed freely with pass-by-val params
// general rules for passing by ref vs by val:
	'fundamental types', 'enumerated types' are cheap: pass by val
	'class types' expensive, pass by 'const ref'
'std::string_view' should be preferred to 'const std::string&'
// handles more args, allows substring without copying
}
/** INTRODUCTION TO POINTERS */
{
'&' is the address-off op:
	#include <iostream>
	int main(){
		int x{ 5 };
		std::cout << x << '\n';  // print the value of variable x
		std::cout << &x << '\n'; // print the memory address of variable x
		return 0;
	}
	// addresses are printed in hex
'*' is the dereference op: returns the val at given memory as a 'lval'
	#include <iostream>
	int main(){
		int x{ 5 };
		std::cout << x << '\n';  // print the value of variable x
		std::cout << &x << '\n'; // print the memory address of variable x
		std::cout << *(&x) << '\n'; // print the value at the memory address of variable x (parentheses not required, but make it easier to read)
		return 0;
	}

a type that specified a pointer is a 'pointer type'
	int;  // a normal int
	int&; // an lvalue reference to an int value
	int*; // a pointer to an int value (holds the address of an integer value)

pointers arent initialized by def; 'a wild pointer'
// always initialize your pointers
	int main()
	{
		int x{ 5 };

		int* ptr;        // an uninitialized pointer (holds a garbage address)
		int* ptr2{};     // a null pointer (we'll discuss these in the next lesson)
		int* ptr3{ &x }; // a pointer initialized with the address of variable x

		return 0;
	}

a pointer's type has to match the type of object being pointed to
initializing a pointer with literal val is disallowed (besides 1 exception)
size of a pointer is based on architicture:
	32 bit system is 32 bits (4 bytes)
	64 bit system is 64 bits (8 bytes)
when the pointed val is deleted, it created a 'dangling pointer'
}
/** NULL POINTERS */
{
'null pointer': holds something that has no value
	int main(){
		int* ptr {}; // ptr is now a null pointer, and is not holding an address
		return 0;
	}
	
'nullptr' is a null pointer literal, which can be used in assignment:
	int main(){
		int* ptr { nullptr }; // can use nullptr to initialize a pointer to be a null pointer
		int value { 5 };
		int* ptr2 { &value }; // ptr2 is a valid pointer
		ptr2 = nullptr; // Can assign nullptr to make the pointer a null pointer
		someFunction(nullptr); // we can also pass nullptr to a function that has a pointer parameter
		return 0;
	}
	// dereferencing a nullptr leads to undefined behavior
	// generally this leads to a crash

pointers implicitly convert to 'bool' vals:
	'nullptr' to 'false'
	'non-null' to 'true'

in older code 0 && 'NULL' are alternative literals that are the same as 'nullptr'
// generally avoid these and just use nullptr
references are generally safer than pointers
// favor using references unless a pointer is necessary
}
/** POINTERS AND CONST */
{
a 'non-const' pointer cant be pointed at a 'const' type
'pointer to const' can point to 'const' values
	int main(){
		const int x{ 5 };
		const int* ptr { &x }; // okay: ptr is pointing to a "const int"
		*ptr = 6; // not allowed: we can't change a const value
		return 0;
	}
	// this only indicates that it is pointing to const
	
// hence, the pointer cant still be changed to point to something else
	int main(){
		const int x{ 5 };
		const int* ptr { &x }; // ptr points to const int x
		const int y{ 6 };
		ptr = &y; // okay: ptr now points at const int y
		return 0;
	}
	
// pointer to const can be used on nonconst vals as well, and it will enforce const
// the original non-const val can still be directly altered
	int main(){
		int x{ 5 }; // non-const
		const int* ptr { &x }; // ptr points to a "const int"
		*ptr = 6;  // not allowed: ptr points to a "const int" so we can't change the value through ptr
		x = 6; // allowed: the value is still non-const when accessed through non-const identifier x
		return 0;
	}

a pointer itself can also be 'const': aka a 'const pointer'
'const pointer' pointed val is 'non-const' && can be changed, but pointer cannot be repointed 
// declared after the asterisk in pointer declaration:
	int main(){
		int x{ 5 };
		int* const ptr { &x }; // const after the asterisk means this is a const pointer
		return 0;
	}
}
/** PASS BY ADDRESS */
{
'pass by val' || 'pass by reference' || 'pass by address'
'pass by address' provides an address via a pointer
the address can then by dereferenced to manipulate the value
'pass by address' doesnt create a copy of the val
// it only copies the pointer so 4/8 bytes depending on architecture
when 'passing by address' a 'nullptr' check should be implemented
	void print(int* ptr){
		if (ptr) // if ptr is not a null pointer
		{
			std::cout << *ptr << '\n';
		}
	}
	
// better written as a guard usually
	void print(int* ptr)
	{
		if (!ptr) // if ptr is a null pointer, early return back to the caller
			return;
		std::cout << *ptr << '\n';
	}

// an assert can also be used
	void print(const int* ptr) // now a pointer to a const int
	{
		assert(ptr); // fail the program in debug mode if a null pointer is passed (since this should never happen)
		std::cout << *ptr << '\n';
	}

generally prefer 'pass by const ref' as opposed to 'pass by address'
}
/** PASS BY ADDRESS (PART 2) */
{
'pass by address' used to enable 'optional arg'
	void printIDNumber(const int *id=nullptr){
		if (id)
			std::cout << "Your ID number is " << *id << ".\n";
		else
			std::cout << "Your ID number is not known.\n";
	}
	int main(){
		printIDNumber(); // we don't know the user's ID yet
		int userid { 34 };
		printIDNumber(&userid); // we know the user's ID now
		return 0;
	}

'passing by address' creates a copy of the pointer
// when repointing repoints that copy
its possible to 'pass by address by reference'
	#include <iostream>
	void nullify(int*& refptr) // refptr is now a reference to a pointer
	{
		refptr = nullptr; // Make the function parameter a null pointer
	}
	int main(){
		int x{ 5 };
		int* ptr{ &x }; // ptr points to x
		std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");
		nullify(ptr);
		std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");
		return 0;
	}
}
/** RETURN BY REFERENCE AND RETURN BY ADDRESS */
{
returning by val also copies a val
// can return by reference instead:
	std::string&       returnByReference(); // returns a reference to an existing std::string (cheap)
	const std::string& returnByReferenceToConst(); // returns a const reference to an existing std::string (cheap)

the object returned must exist after func returns
// usage of static keyword is advised
lifetime extension doesnt work across functions
returning 'non-const static vars' can lead to weird behavior
	#include <iostream>
	#include <string>
	const int& getNextId(){
		static int s_x{ 0 }; // note: variable is non-const
		++s_x; // generate the next id
		return s_x; // and return a reference to it
	}
	int main(){
		const int& id1 { getNextId() }; // id1 is a reference
		const int& id2 { getNextId() }; // id2 is a reference
		std::cout << id1 << id2 << '\n';
		return 0;
	}
	// both id1 and id2 refer to a reference of object s_x
	// hence any changes to s_x will reflect on both id1 and id2

when a non-ref var is assigned/initialized with a returned ref, a copy is made
// this behaves as if it was returned by value
you can daisy chain && pass references from param to returns:
// below passes strings in main via param and returns the reference to them
// the return still uses the param references that refer to main
	#include <iostream>
	#include <string>
	// Takes two std::string objects, returns the one that comes first alphabetically
	const std::string& firstAlphabetical(const std::string& a, const std::string& b){
		return (a < b) ? a : b; // We can use operator< on std::string to determine which comes first alphabetically
	}
	int main(){
		std::string hello { "Hello" };
		std::string world { "World" };
		std::cout << firstAlphabetical(hello, world) << '\n';
		return 0;
	}
	// we can avoid making copies this way
	// this saves making 3 copies (1 for each param, 1 for return)

an 'rval' passed by 'const ref' can still be returned as such
	#include <iostream>
	#include <string>
	const std::string& foo(const std::string& s){
		return s;
	}
	std::string getHello(){
		return "Hello"; // implicit conversion to std::string
	}
	int main(){
		const std::string s{ foo(getHello()) };
		std::cout << s;
		return 0;
	}
	// an rvalue string is created by getHello()
	// foo() passes it as a const reference, keeping the temporary alive
	// return initializes s to the rvalue as a copy 
	// the rvalue is discarded
	// this is allowed because const ref extends the lifetime to the full expression
	// const std::string& r = foo(getHello()) wouldnt work

returning by address is similar to by reference
// main benefit is using nullptr
// main caveat is needing to check for a nullptr
// generally prefer return by reference over return by address
}
/** IN AND OUT PARAMETERS */
{
a 'non-const' allowed func to modify val of obj passed in arg
// this is called an out param
	#include <cmath>    // for std::sin() and std::cos()
	#include <iostream>
	// sinOut and cosOut are out parameters
	void getSinCos(double degrees, double& sinOut, double& cosOut){
		// sin() and cos() take radians, not degrees, so we need to convert
		constexpr double pi { 3.14159265358979323846 }; // the value of pi
		double radians = degrees * pi / 180.0;
		sinOut = std::sin(radians);
		cosOut = std::cos(radians);
	}
	int main(){
		double sin { 0.0 };
		double cos { 0.0 };
		double degrees{};
		std::cout << "Enter the number of degrees: ";
		std::cin >> degrees;
		// getSinCos will return the sin and cos in variables sin and cos
		getSinCos(degrees, sin, cos);
		std::cout << "The sin is " << sin << '\n';
		std::cout << "The cos is " << cos << '\n';
		return 0;
	}
	// above sin and cos are passed in as non-const params so the void function can modify them
	// by convention output params are usually rightmost
}
/** TYPE DEDUCTION WITH POINTERS, REFERENCES, AND CONST */
{
type deduction drops references
// std::string& is deduced as std::string
// makes a copy and drops the reference
	#include <string>
	std::string& getRef(); // some function that returns a reference
	int main(){
		auto ref { getRef() }; // type deduced as std::string (not std::string&)
		return 0;
	}

type deduction doesnt drop pointers:
	#include <string>
	std::string* getPtr(); // some function that returns a pointer
	int main(){
		auto ptr1{ getPtr() }; // std::string*
		return 0;
	}
	// auto* can be used to make it clear the deduced type is a pointer

'top level const' applied to object itself:
	const int x
	int* const ptr
	// ptr itself is const
'low level const' applies to object accessed through:
	const int& ref
	const int* ptr
	// value accessed through & and * are const

deduction only drops top level && preserves low level
	const int x = 42;
	auto a = x;		// int top level const dropped
	const int* p = &x;
	auto b = p;		// const int* low level preserved
	const int* const z = &y
	auto c = h;		// const int* low level preserved, high level dropped
	
deduction drops any references, unless the deduced type is defined as a ref
a 'const ref' dropping ref will cause the low level to become top level
deduction then drops any 'top level const' as well
// constexpr is never deduced, must be explicitly stated always
	const int& ref	// low level referring to val through ref
	const int ref	// high level referring to copy of int itself
	int ref			// high level dropped

deduction doesnt drop pointers
'auto' will only deduce a pointer when initialized as a pointer
'auto*' always deduces a pointer
'auto const' && 'const auto' both make the deduced pointer a 'const pointer'
'auto* const' deduces a 'const pointer'
'const auto*' deduces a 'pointer to const'
// const auto* is deduced as type first and then pointer is applied
// const auto is deduced as a pointer directly
// generally use auto* as it allows control over top/low level const deduction
}
/** STD::OPTIONAL */
{
'std::optional' implements an optional val
'std::optional<T>' can have a val of T but doesnt have to
	#include <optional> // for std::optional (C++17)
	// Our function now optionally returns an int value
	std::optional<int> doIntDivision(int x, int y){
		if (y == 0)
			return {}; // or return std::nullopt
		return x / y;
	}
	// can be used with var declaration as well
	int main(){
		std::optional<int> result1 { doIntDivision(20, 5) };
		if (result1) // if the function returned a value
			std::cout << "Result 1: " << *result1 << '\n'; // get the value
		else
			std::cout << "Result 1: failed\n";
		std::optional<int> result2 { doIntDivision(5, 0) };
		if (result2)
			std::cout << "Result 2: " << *result2 << '\n';
		else
			std::cout << "Result 2: failed\n";
		return 0;
	}
// constructions:
	std::optional<int> o1 { 5 };            // initialize with a value
	std::optional<int> o2 {};               // initialize with no value
	std::optional<int> o3 { std::nullopt }; // initialize with no value
	
// checking for value:
	if (o1.has_value()) // call has_value() to check if o1 has a value
	if (o2)             // use implicit conversion to bool to check if o2 has a value

'std::optional' has usage syntax identical to pointer
	* can be used to dereference values as well
	implicit conversion to 'bool'
// semantically theyre different:
	// pointer has ref semantics: assignment copies pointer not pointed obj
	// optional has val semantics: assignment copies val
dereferencing 'std::optional' with no val leads to undefined behavior
C++23 'std::expected' returns an expected val || error code

optional args via pass by address require an lval input
	void printIDNumber(const int *id=nullptr){
		if (id)
			std::cout << "Your ID number is " << *id << ".\n";
		else
			std::cout << "Your ID number is not known.\n";
	}

'std::optional' allows rval input optional args
	void printIDNumber(std::optional<const int> id = std::nullopt){
		if (id)
			std::cout << "Your ID number is " << *id << ".\n";
		else
			std::cout << "Your ID number is not known.\n";
	}
	// note std::optional copies an the object val directly
	// std::optional doesnt support references
}