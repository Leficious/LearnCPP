/** IMPLICIT TYPE CONVERSION */
{
different data types represent data differently in binary
binary 3: 0000 0000 0000 0000 0000 0000 0000 0011
binary 3.f: 0100 0000 0100 0000 0000 0000 0000 0000
to properly represent the data, conversion is necessary
'implicit conversion': an input type supplied isnt the expected type
	double d{ 3 }; // int value 3 implicitly converted to type double
	d = 6; // int value 6 implicitly converted to type double
	return 3.0; // double value 3.0 implicitly converted to type float
	double division{ 4.0 / 3 }; // int value 3 implicitly converted to type double
	if (5) // int value 5 implicitly converted to type bool
	void doSomething(long l)
	doSomething(3); // int value 3 implicitly converted to type long
// above are rules known as the standard conversions
type conversion can fail when compiler cant find acceptable conversion
// there is no conversion for string literal to int so it fails
	int x { "14" };
// other times certain conversions are not allowed
	int x { 3.5 }; // brace-initialization disallows conversions that result in data loss
}
/** FLOATING-POINT AND INTEGRAL PROMOTION */
{
the number of bits a type uses is called the 'width'
'numeric promotion': narrower type aka 'char' converts to wider aka 'int'
'numeric promotion' aka the source value can be converted to an equivalent target
as such, compilers will freely use numeric promotion an wont issue warnings
'numeric promotion' reduces redundancy
// param x can be promoted from to short, char, unsigned char, etc.
	void printInt(int x){
		std::cout << x << '\n';
	}

'floating point promotions': 
'float' convert to 'double'
// this function will work with both a float and a double
	void printDouble(double d){
		std::cout << d << '\n';
	}
	
'integral promotions':
'signed char' && 'signed short' convert to 'int'
'unsigned char' && 'char8_t' && 'unsigned short' convert to 'int' || 'unsigned int'
// int vs uint depends on whether each one can hold the entire range of the type
'bool' converts to 'int' so 'true' to '1'  && 'false' to '0'
// generally most things get converted to int
// certain architextures with 2 byte ints can promote unsigned integrals types to unsigned ints
// unsigned types may be promoted to larger signed types so the signedness is not preserved
}
/** NUMERIC CONVERSIONS */
{
'numeric conversion' covers the cases where conversion isnt widening
brace initialization disallows some numeric conversions
'numeric conversion' can be unsafe; meaning the value isnt preserved
'reinterpretive conversions' are unsafe 'numeric conversion' where no data is lost, but the value may be different
// for example a signed int -5 converting to an unsigned one
// the data persists (it can be converted back but the value is different
'lossy conversion' are unsafe where data may be lost
	int i = 3.0; // okay: will be converted to int value 3 (value preserved)
	int j = 3.5; // data lost: will be converted to int value 3 (fractional value 0.5 lost)
// data is lost (it cannot be converted back) value is also different
// compilers generally issue a warning or error for implicit lossy conversion
}
/** NARROWING CONVERSIONS, LIST INITIALIZATION, AND CONSTEXPR INITIALIZERS */
{
'narrowing conversion': destination type cant hold all of source type
ie: 'floating point' to 'integral'
// avoid narrowing conversions when possible
// when done, use static_cast to make it explicit
// not allowed with brace initialization
'constexpr' vars allows narrowing conversions assuming data can be stored
    constexpr int n1{ 5 };   // note: constexpr
    unsigned int u1 { n1 };  // okay: conversion is not narrowing due to exclusion clause
    constexpr int n2 { -5 }; // note: constexpr
    unsigned int u2 { n2 };  // compile error: conversion is narrowing due to value change

'float' to 'int' is always considered narrowing; theres no 'constexpr' clause
'constexpr floating type' to 'floating type' is allowed even assuming precision is lost
'constexpr initialization' is useful in list initialization
}
/** ARITHMETIC CONVERSIONS */
{
certain ops require their operands to be of the same type
when broken hence, causes 'arithmetic conversion' via 'usual arithmetic conversion'
	binary arithmetic operators: + - * % /
	binary relational operators: < > <= >= == !=
	binary bitwise arithmetic operators: & ^ |
	condition: ?
	// overloaded operators do not obey normal arithmetic conversion rules
type rankings:
// if it doesnt appear ie char, short, then its converted to float
	long double (highest rank)
	double
	float
	long long
	long
	int (lowest rank)
usual rules in conversions:
	integral, floating: integral conveted to floating, then higher rank type is output
	integral, integral: integral is promoted, then higher rank type is output
additional rules inm integral operands with different signs:
	'unsigned' rank >= 'signed' rank: 'signed' is converted to 'unsigned'
	'signed' can represent all values of 'unsigned': 'unsigned' becomes 'signed'
	otherwise: both converted to 'unsigned'
}
/** EXPLICIT TYPE CONVERSION (CASTING) AND STATIC_CAST */
{
casting causes an 'explicit type conversion'
there are 5 types of casting; 4 are named
	static_cast			//	Performs compile-time type conversions between related types.
	dynamic_cast		//	Performs runtime type conversions on pointers or references in an polymorphic (inheritance) hierarchy
	const_cast			//	Adds or removes const.
	reinterpret_cast	//	Reinterprets the bit-level representation of one type as if it were another type
	C-style casts 		//	Performs some combination of static_cast, const_cast, or reinterpret_cast.
'const_cast' && 'reinterpret_cast' should be avoided because theyre rarely useful
in C, casting done via ()
	std::cout << (double)x / y << '\n'; // C-style cast of x to double
C++ provides additionally:
	std::cout << double(x) / y << '\n'; //  // function-style cast of x to double
// C style casts should be avoided since they can be ambiguous as to what cast theyre actually performing
'static_cast' should be used in most cases:
'static_cast' returns a temporary type object containing the converted value
'static_cast' type-checks so certain casts arent permitted
// this is intentional as opposed to c style to prevent dangerous conversions
// static_cast requires the types be known at compile time
// static_cast explicitly tell the compiler that narrowing type conversions are acceptable

'casting' vs 'initializing temp object'
// generally prefer static_cast
'int x{}' uses list initialization, which disallows narrowing
    int x { 10 };
    int y { 4 };
    // We want to do floating point division, so one of the operands needs to be a floating point type
    std::cout << double{x} / y << '\n'; // okay if int is 32-bit, narrowing if x is 64-bit
'static_cast' is more 'explicit'
initialization only allows single word types so 'int' is ok, but 'unsigned int' isnt
can bypass with type alias:
	using uint = unsigned int;
	uint {c};
}
/** TYPEDEFS AND TYPE ALIASES */
{
'using' keyword creates alias that represents data type
	using Distance = double; // define Distance as an alias for type double
	Distance milesToDestination{ 3.4 }; // defines a variable of type double
	
naming conventions:
// theres no historical consistency
	ending in _t
	ending in _type
	capital letter no suffix // modern convention
	
types alias is just alternate identifier to existing type
// they are not treated as distinct types, hence aliases are not typesafe
// some languages support strong typedef which actually does create a new type
    using Miles = long; // define Miles as an alias for type long
    using Speed = long; // define Speed as an alias for type long
    Miles distance { 5 }; // distance is actually just a long
    Speed mhz  { 3200 };  // mhz is actually just a long
	
type alias follows same scoping rules as vars
when type aliases are needed across files, use a header with them
	#ifndef MYTYPES_H
	#define MYTYPES_H
		using Miles = long;
		using Speed = long;
	#endif
	
'typedef' is older way of creating alias
// The following aliases are identical
	typedef long Miles;
	using Miles = long;
generally prefer aliases 'using' over 'typedef'

aliases can be used to distinguish types between 32bit && 64bit architecture
	#ifdef INT_2_BYTES
	using int8_t = char;
	using int16_t = int;
	using int32_t = long;
	#else
	using int8_t = char;
	using int16_t = short;
	using int32_t = int;
	#endif
fixed-width integer types are actually just type aliases to various fundamental types
// this is why int8_t tends to behave like a char
	#include <cstdint> // for fixed-width integers
	#include <iostream>
	int main(){
		std::int8_t x{ 97 }; // int8_t is usually a typedef for signed char
		std::cout << x << '\n';
		return 0;
	} // the program prints 'a' since ASCII 97 is a

'type aliases' can also make complex types easier to read
// this is very common and a good usage of it
they can also be used to document code with an identifier that suggests the vars usage
// this generally isnt worth it
can also modularize code ie want to change var from 'short' to 'long':
// no alias: have to hunt down every short and replace
// alias: simply change 'using name = short' to 'using name = long'
ultimately, 'type aliases' should be used judiciously when they increase clarity && easier maintenance
}
/** TYPE DEDUCTION FOR OBJECTS USING THE AUTO KEYWORD */
{
'type deduction' also 'type inference' allows compiler to deduce type of an object
    auto d { 5.0 }; // 5.0 is a double literal, so d will be deduced as a double
    auto i { 1 + 2 }; // 1 + 2 evaluates to an int, so i will be deduced as an int
    auto x { i }; // i is an int, so x will be deduced as an int
	
functions have 'return types' so they can also be used with 'auto'
	int add(int x, int y){
		return x + y;
	}
	int main(){
		auto sum { add(5, 6) }; // add() returns an int, so sum's type will be deduced as an int
		return 0;
	}

'type deduction' can be used with 'const' && 'constexpr'
	const auto b { 5 };     // b is a const int
    constexpr auto c { 5 }; // c is a constexpr int

'type deduction' needs something to deduce, so empty initializer && 'void function' wont work
	#include <iostream>
	void foo(){
	}
	int main(){
		auto a;           // The compiler is unable to deduce the type of a
		auto b { };       // The compiler is unable to deduce the type of b
		auto c { foo() }; // Invalid: c can't have type incomplete type void
		return 0;
	}
'type deduction' is useful when later datatypes get more complex
'type deduction' generally drops 'const'
// add const auto instead if const wants to be maintained
	const int a { 5 }; // a has type const int
    auto b { a };      // b has type int (const dropped)
	const auto b { a }; // b has type const int (const dropped but reapplied)

'string literals' have weird type: 'const char*'
'std::string' && 'std::string_view' need s/sv suffixes
// generally better to just not use literals
	using namespace std::literals; // easiest way to access the s and sv suffixes
    auto s1 { "goo"s };  // "goo"s is a std::string literal, so s1 will be deduced as a std::string
    auto s2 { "moo"sv }; // "moo"sv is a std::string_view literal, so s2 will be deduced as a std::string_view

'constexpr' isnt a part of the type system, but it is implicitly 'const'
'const' will be dropped:
	constexpr double a { 3.4 };  // a has type const double (constexpr not part of type, const is implicit)
    auto b { a };                // b has type double (const dropped)
    const auto c { a };          // c has type const double (const dropped but reapplied)
    constexpr auto d { a };      // d has type const double (const dropped but implicitly reapplied by constexpr)
    return 0;

benefits of 'type deduction':
// readability
	// harder to read
	int a { 5 };
	double b { 6.7 };
	// easier to read
	auto c { 5 };
	auto d { 6.7 };
// protects against uninitialization
	int x; // oops, we forgot to initialize x, but the compiler may not complain
	auto y; // the compiler will error out because it can't deduce a type for y

downsides:
// obscurity
	auto y { 5 }; // oops, we wanted a double here but we accidentally provided an int literal
	// certain types like unsigned generally want to be clear
'type deduction' is generally acceptable when type of object doesnt matter
favor 'explicit type' when making type obvious is useful
}
/** TYPE DEDUCTION FOR FUNCTIONS */
{
'type deductions' can also be used with functions
	auto add(int x, int y){
		return x + y;
	}
all 'return' in function must have same 'return type'
// this wont work
	auto someFcn(bool b){
		if (b)
			return 5; // return type int
		else
			return 6.7; // return type double
	}
	// if needed then static_cast type int to type double

benefits:
// prevents mismatched return type (prevents conversions)
// tis useful for when return is implementation defined
	// let compiler determine the return type of unsigned short + char
	auto add(unsigned short x, char y){
		return x + y;
	}
downside:
// auto functions must have full definition
// this makes sense as individual translation units have no way to deduce the type from other locations
// a forward declaration is not enough
// following code will throw an error:
	#include <iostream>
	auto foo();
	int main(){
		std::cout << foo() << '\n'; // the compiler has only seen a forward declaration at this point
		return 0;
	}
	auto foo(){
		return 5;
	}
// they can obscure the typing; have to dig through functions to see return type
generally, prefer 'explicit return type' over 'type deduction'

'trailing return syntax' specifies the 'return type' after the rest of the function
// in this case, no deduction is being made
	auto add(int x, int y) -> int
	{
	  return (x + y);
	}
// this is mostly used when there are complex return types for readability
	std::common_type_t<int, double> compare(int, double);         // harder to read (where is the name of the function in this mess?)
	auto compare(int, double) -> std::common_type_t<int, double>; // easier to read (we don't have to read the return type unless we care)
// can also align function names
	auto add(int x, int y) -> int;
	auto divide(double x, double y) -> double;
	auto printSomething() -> void;
	auto generateSubstring(const std::string &s, int start, int len) -> std::string;
	
prior to c++20 'auto' function params wouldnt work
after c++20 'auto' in function params triggers 'function templates'
}