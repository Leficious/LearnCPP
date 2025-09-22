/** INTRODUCTION TO FUNCTION OVERLOADING */
{
functions with the same identifier, but diff param types are 'overloaded'
the compiler will be able to differentiate based on the input types
// this matching behaviour is called 'overload resolution'
}
/** FUNCTION OVERLOAD DIFFERENTIATION */
{
'overloaded functions' are differentiated in a few ways:
	number of params
	type of params // no typedefs, type aliases, const. includes ellipses.)
member functions: 'qualifiers' are also considered
// these functions can be differentiated based on param number
	int add(int x, int y){
		return x + y;
	}
	int add(int x, int y, int z){
		return x + y + z;
	}
// these ones from their types
// type aliases arent distinct types, so they wont work
	int add(int x, int y); // integer version
	double add(double x, double y); // floating point version
	double add(int x, double y); // mixed version
	double add(double x, int y); // mixed version
	
a function signature includes:
// a return type is not considered for differentiation nor signature
	identifier
	number of params
	types of params
	function level qualifier
the compiler 'mangles' the name of the functions by adding things
}
/** FUNCTION OVERLOAD RESOLUTION AND AMBIGUOUS MATCHES */
{
'overload resolution': matching function calls to 'overloaded function'
in cases theres an exact match, tis simple:
	void print(int x){
		 std::cout << x << '\n';
	}
	void print(double d){
		 std::cout << d << '\n';
	}
	int main(){
		 print(5); // 5 is an int, so this matches print(int)
		 print(6.7); // 6.7 is a double, so this matches print(double)
		 return 0;
	}
but whatif the input doesnt match either exactly?
// below long/char dont match either, so which should it implicitly convert to?
	#include <iostream>
	void print(int x){
		 std::cout << x << '\n';
	}
	void print(double d){
		 std::cout << d << '\n';
	}
	int main(){
		 print('a'); // char does not match int or double, so what happens?
		 print(5L); // long does not match int or double, so what happens?
		 return 0;
	}
the compiler would execute a series of actions in above:
	no matching functions were found; compiler moves to the next step
	single match found: best match, completed, no more subsequent steps
	more than 1 match found: ambiguous match error
the compilers acts/matches in order:
	exact matches
	trivial conversions (qualifier, reference, lval rval)
	numeric promotion // char to int, float to double, etc.
	numeric conversions // char to double
	user defined conversion // would implement normal rules again after
	find function that uses ellipsis
	no function match error
'ambiguous matching' occurs when numeric conversion occurs && matches 2 'overloaded function' params
// long can convert to int or double
// this results in an ambiguous call error
	void foo(int){
	}
	void foo(double){
	}
	int main(){
		foo(5L); // 5L is type long
		return 0;
	}
functions with multiple params need to have a totality of better matches 
// this scenario first arg matches exactly to all overloads, but a is promotion to int
#include <iostream>
void print(char, int){ // this function wins
	std::cout << 'a' << '\n';
}
void print(char, double){
	std::cout << 'b' << '\n';
}
void print(char, float){
	std::cout << 'c' << '\n';
}
int main(){
	print('x', 'a'); // exact match char, char promotes to int
	return 0;
}
}
/** DELETING FUNCTIONS */
{
certain types can be excluded with '= delete' specifier
// this will halt compilation with a compile error even if promotion/conversion is possible
	#include <iostream>
	void printInt(int x){
		std::cout << x << '\n';
	}
	void printInt(char) = delete; // calls to this function will halt compilation
	void printInt(bool) = delete; // calls to this function will halt compilation
	int main(){
		printInt(97);   // okay
		printInt('a');  // compile error: function deleted
		printInt(true); // compile error: function deleted
		printInt(5.0);  // compile error: ambiguous match
		return 0;
	}
	// deleted functions count towards ambiguation hence double being an error

}
/** DEFAULT ARGUMENTS */
{
'default argument' is the 'default val' provided in a function param
// this makes the value an optional param (default val can serve as arg)
// user specified vals will take precedent
	#include <iostream>
	// you must use = to specify a default arg
	void print(int x, int y=4) { // 4 is the default argument
		std::cout << "x: " << x << '\n';
		std::cout << "y: " << y << '\n';
	}
	int main(){
		print(1, 2); // y will use user-supplied argument 2
		print(3); // y will use default argument 4, as if we had called print(3, 4)
		return 0;
	}
'explicit args' must be leftmost
'default args' must be the rightmost args in the function param list
	void print(int x=10, int y); // not allowed
	void print(std::string_view sv="Hello", double d=10.0);
	int main(){
		print();           // okay: both arguments defaulted
		print("Macaroni"); // okay: d defaults to 10.0
		print(20.0);       // error: does not match above function (cannot skip argument for sv)
		return 0;
	}
'default args' can only be defined once per translation unit
// either in the definiction or the forward declaration; not both
	#include <iostream>
	void print(int x, int y=4); // forward declaration
	void print(int x, int y=4) // compile error: redefinition of default argument
	{
		std::cout << "x: " << x << '\n';
		std::cout << "y: " << y << '\n';
	}
// also must be declared before usage
	#include <iostream>
	void print(int x, int y); // forward declaration, no default argument
	int main(){
		print(3); // compile error: default argument for y hasn't been defined yet
		return 0;
	}
	void print(int x, int y=4){
		std::cout << "x: " << x << '\n';
		std::cout << "y: " << y << '\n';
	}
best practice: declare 'default vals' in forward declarations (esp in header files)
'default arg' functions can be overloaded
// default args arent part of a functions signature but can be deemed viable for empty args
// they can lead to ambiguous matches:
	void foo(int x = 0){
	}
	void foo(double d = 0.0){
	}
	int main(){
		foo(); // ambiguous function call
		return 0;
	}
// default args also dont work for functions called through func pointers
}
/** FUNCTION TEMPLATES */
{
templates allow functions to work with multiple types
instead of having many overloaded functions, use templates
'function template' generates overloaded functions
'primary template' generates 'instantiated functions'
'primary template' uses placeholder types 'template types'
// this is how to declare a template:
	template <typename T> // this is the template parameter declaration defining T as a type template parameter
	T max(T x, T y) // this is the function template definition for max<T>
	{
		return (x < y) ? y : x;
	}
	// each template is limited to the scope of the template function that follows
// generally T is fine, but if it is necessary then Tname is also ok
}
/** FUNCTION TEMPLATE INSTANTIATION */
{
to use a 'function template':
	max<actual_type>(arg1, arg2); // actual_type is some actual type, like int or double
// compiler will see that the function doesnt exist and create an overload
// this instantiation is called 'implicit instantiation'
// instantiated function calld 'specialization'
'template arg deduction': when args match actual type
// in this case no explicit definition is necessary
	std::cout << max<>(1, 2) << '\n';
	std::cout << max(1, 2) << '\n';
	// compiler will prefer non-template function over equally viable template

functions can have a mix of templates && non-templates types
	template <typename T>
	int someFcn(T, double){
		return 5;
	}
	int main(){
		someFcn(1, 3.4); // matches someFcn(int, double)
		someFcn(1, 3.4f); // matches someFcn(int, double) -- the float is promoted to a double
		someFcn(1.2, 3.4); // matches someFcn(double, double)
		someFcn(1.2f, 3.4); // matches someFcn(float, double)
		someFcn(1.2f, 3.4f); // matches someFcn(float, double) -- the float is promoted to a double
		return 0;
	}
	// return doesnt need <> since its always int

'function templates' can also have 'default vals'
each 'static' local var will have its own version of it in 'instantiatians'
'template types' are also sometimes called 'generic types'
hence with a lot of 'templates' there is 'generic programming'
// generally functions are good to use
// disadvantages: harder to debug, slower to compile
}
/** FUNCTION TEMPLATES WITH MULTIPLE TEMPLATE TYPES */
{
'implicit type conversions' arent done with 'type deduction'
// explicitly stating type will bypass the deduction
	max<>(2, 3.5) // this will not work
	max<double>(2, 3.5) // 2 is implicitly converted to double
	
instead of 1, can use 2 'template types'
	#include <iostream>
	template <typename T, typename U> // We're using two template type parameters named T and U
	T max(T x, U y) // x can resolve to type T, and y can resolve to type U
	{
		return (x < y) ? y : x; // uh oh, we have a narrowing conversion problem here
	}
	int main(){
		std::cout << max(2, 3.5) << '\n'; // resolves to max<int, double>
		return 0;
	}
	
consider 'auto' to allow compiler to decide appropriate output type
	#include <iostream>
	template <typename T, typename U>
	auto max(T x, U y) // ask compiler can figure out what the relevant return type is
	{
		return (x < y) ? y : x;
	}
	int main(){
		std::cout << max(2, 3.5) << '\n';
		return 0;
	}
	// caveat: remember auto must be fully defined before it can be used
	// templates are resolved by the overloaded functions generated by template
	
when 'auto' needs to be forward declared use std::common_type_t
	#include <iostream>
	#include <type_traits> // for std::common_type_t
	template <typename T, typename U>
	auto max(T x, U y) -> std::common_type_t<T, U>; // returns the common type of T and U
	int main(){
		std::cout << max(2, 3.5) << '\n';
		return 0;
	}
	template <typename T, typename U>
	auto max(T x, U y) -> std::common_type_t<T, U>{
		return (x < y) ? y : x;
	}

C++20 'auto' has novelle usage.
when used in param types in normal function, compiler converts to 'template'
// these 2 are equivalent:
	auto max(auto x, auto y){
		return (x < y) ? y : x;
	} // this newer brand of C++ should be preferred for concision
	// the same as above
	// auto makes it so every var has independent type
	template <typename T, typename U>
	auto max(T x, U y){
		return (x < y) ? y : x;
	}
	
'function templates' can also be overloaded:
	#include <iostream>
	// Add two values with matching types
	template <typename T>
	auto add(T x, T y){
		return x + y;
	}
	// Add two values with non-matching types
	// As of C++20 we could also use auto add(auto x, auto y)
	template <typename T, typename U>
	auto add(T x, U y){
		return x + y;
	}
	// Add three values with any type
	// As of C++20 we could also use auto add(auto x, auto y, auto z)
	template <typename T, typename U, typename V>
	auto add(T x, U y, V z){
		return x + y + z;
	}
	int main(){
		std::cout << add(1.2, 3.4) << '\n'; // instantiates and calls add<double>()
		std::cout << add(5.6, 7) << '\n';   // instantiates and calls add<double, int>()
		std::cout << add(8, 9, 10) << '\n'; // instantiates and calls add<int, int, int>()
		return 0;
	// add<T>(T, T) has precendence over add<T,U>(T,U)
	// this is known as "partial ordering of function templates"
	// it is more restrictive, so it will be preferred
}
}
/** NON-TYPE TEMPLATE PARAMETERS */
{
A non-type template parameter can be any of the following types:
// non-type temp param is a fixed type that is placeholder for constexpr val passed in as arg
	integral type
	enumeration type
	std::nullptr_t
	floating point type (since C++20)
	pointer || reference to an object
	pointer || reference to a function
	pointer || reference to a member function
	literal 'class type' (since C++20)
	
bitsets use a param to specify the number of bits stored:
	std::bitset<8> bits{ 0b0000'0101 }; // The <8> is a non-type template parameter
how to declare a non-type parameter:
	template <int N> // declare a non-type template parameter of type int named N
	void print(){
		std::cout << N << '\n'; // use value of N here
	}
	int main(){
		print<5>(); // 5 is our non-type template argument
		return 0;
	}

'non-type template params' are useful when 'constexpr' params are needed
good when doing 'static_assert' instead of 'assert' in compile-time debugging
'implicit conversions' are also allowed, albeit less permissively
matching isnt very smart with 'non-type template params'
hence overloading can easily result in ambiguous matching
	#include <iostream>
	template <int N> // int non-type template parameter
	void print(){
		std::cout << N << '\n';
	}
	template <char N> // char non-type template parameter
	void print(){
		std::cout << N << '\n';
	}
	int main(){
		print<5>();   // ambiguous match with int N = 5 and char N = 5
		print<'c'>(); // ambiguous match with int N = 99 and char N = 'c'
		return 0;
	}

C++17: 'non-type template params' can be 'auto'
}
/** USING FUNCTION TEMPLATES IN MULTIPLE FILES */
{
consider the following program:
// main.cpp
	#include <iostream>
	template <typename T>
	T addOne(T x); // function template forward declaration
	int main(){
		std::cout << addOne(1) << '\n';
		std::cout << addOne(2.3) << '\n';
		return 0;
	}
// add.cpp
	template <typename T>
	T addOne(T x) // function template definition
	{
		return x + 1;
	}
above wont compile because 'overloaded functions' cant be created in main.cpp
since main.cpp doesnt know the definition in add.cpp
linker hence will search 'double' && 'int' overloaded functions && find nothing
// theoritically if double and int overloads were generated in add.cpp, then it would compile
// however, such usage is rather esoteric and leads too confusion
// general rule: function templates must have definition visible at point of declaration
the best workaround is to place definitions in header files
similar to 'inline', 'template functions' can bypass ODR assuming identical definitions
// specializations are also implicitly inline
}