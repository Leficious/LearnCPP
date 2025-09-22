/** INTRODUCTION TO PROGRAM-DEFINED (USER-DEFINED) TYPES */
{
'fundamental types': available immediate use
'compound types': extensions of 'fundamental types'
'user-defined': user created custom types
// 2 types:
	'enumerated types'
	'class types'
// these types need definition like functions
// definitions must end in a semicolon
	struct Fraction
	{
		int numerator {};
		int denominator {};
	};

// program-defined types are usually denoted with capital letter
// programs that need a type need to know its full definition
// forward declaration is not enough
// program-defined types usually in header files

types are partially exempt from ODR:
	all definitions must be identical
	one definition per translation unit
}
/** UNSCOPED ENUMERATIONS */
{
'enumeration': data restricted to set of symbolic constants
C++ supports 2 types of enums: 'unscoped' && 'scoped'
// they are defined as following:
// Define a new unscoped enumeration named Color
	enum Color{ // unnamed enumerations should be avoided
		// Here are the enumerators
		// These symbolic constants define all the possible values this type can hold
		// Each enumerator is separated by a comma, not a semicolon
		red,
		green,
		blue, // trailing comma optional but recommended
	}; // the enum definition must end with a semicolon
	// enums are implicitly constexpr

no general naming convention enumerators: avoid all caps
	simply use lower letter: red, blue, green

enumerated types are disctinct (unlike typedefs || aliases)
they can enhance readability
// should be used only when the states are non-concurrent
// some common enum uses:
	enum DaysOfWeek{
		sunday,
		monday,
		tuesday,
		wednesday,
		thursday,
		friday,
		saturday,
	};
	enum CardinalDirections{
		north,
		east,
		south,
		west,
	};
	enum CardSuits{
		clubs,
		diamonds,
		hearts,
		spades,
	};

enums are cheap to copy, no need to pass by reference
'unscoped enums' are in the same scope as the definition
assuming global scope can lead to errors in other enums:
	enum Color{
		red,
		green,
		blue, // blue is put into the global namespace
	};
	enum Feeling{
		happy,
		tired,
		blue, // error: naming collision with the above blue
	};

'unscoped enums' provide a named scope region:
    Color apple { red }; // okay, accessing enumerator from global namespace
    Color raspberry { Color::red }; // also okay, accessing enumerator from scope of Color
	// generally unscoped enums are accessed without ::

an 'enum' only used locally should simply be declared locally
}
/** UNSCOPED ENUMERATOR INTEGRAL CONVERSIONS */
{
'enums' are integral types:
	enum Color{
		black,   // 0
		red,     // 1
		blue,    // 2
		green,   // 3
		white,   // 4
		cyan,    // 5
		yellow,  // 6
		magenta, // 7
	};
	int main()
	{
		Color shirt{ blue }; // shirt actually stores integral value 2

		return 0;
	}

the exact vals can be defined:
	enum Animal{
		cat = -3,    // values can be negative
		dog,         // -2
		pig,         // -1
		horse = 5,
		giraffe = 5, // shares same value as horse
		chicken,     // 6
	};
	// horse and giraffe are non-distinct, but C++ allows it
	// most of the time explicit value definitions are necessary

'enum' zero initializes to 0 regardless of whether there's a enumerator
hence, 0 should generally be the 'default' value
alternatively an invalid/unknown enumerator also works:
	enum Winner
	{
		winnerUnknown, // default value (0)
		player1,
		player2,
	};

'unscoped enums' implicitly convert to integers
generally 'int' is used as underlying base integral type
// possible to specify an underlying integral type:
// Use an 8-bit integer as the enum underlying type
	enum Color : std::int8_t
	{
		black,
		red,
		blue,
	};

integer wont implicitly convert to enums
can 'static_cast' to convert:
    Pet pet { static_cast<Pet>(2) }; // convert integer 2 to a Pet
    pet = static_cast<Pet>(3);       // our pig evolved into a whale!
}
/** CONVERTING AN ENUMERATION TO AND FROM A STRING */
{
to print the name of a enumerator there are usually 2 approaches:
// switch statement:
	enum Color{
		black,
		red,
		blue,
	};
	constexpr std::string_view getColorName(Color color){
		switch (color)
		{
		case black: return "black";
		case red:   return "red";
		case blue:  return "blue";
		default:    return "???";
		}
	}
	// second method is using an array see lesson 17

inputs also have a few methods:
// input int and static_cast to enum
	int main(){
		std::cout << "Enter a pet (0=cat, 1=dog, 2=pig, 3=whale): ";
		int input{};
		std::cin >> input; // input an integer
		if (input < 0 || input > 3)
			std::cout << "You entered an invalid pet\n";
		else{
			Pet pet{ static_cast<Pet>(input) }; // static_cast our integer to a Pet
			std::cout << "You entered: " << getPetName(pet) << '\n';
		}
		return 0;
	}
// input the string directly and use std::optional
	int main(){
		std::cout << "Enter a pet: cat, dog, pig, or whale: ";
		std::string s{};
		std::cin >> s;
		std::optional<Pet> pet { getPetFromString(s) };
		if (!pet)
			std::cout << "You entered an invalid pet\n";
		else
			std::cout << "You entered: " << getPetName(*pet) << '\n';
		return 0;
	}
}
/** INTRODUCTION TO OVERLOADING THE I/O OPERATORS */
{
'operator overloading': like 'function overloading', but operators
// the following steps are taken:
	define function with name of op as identifier
	add param of appropriate type (left to right)
	// one of these must be a user defined type
	set retvalue to whatever makes sense
	use retstatement
	
overloading << to print 'enum'
	// Teach operator<< how to print a Color
	// std::ostream is the type of std::cout, std::cerr, etc...
	// The return type and parameter type are references (to prevent copies from being made)
	std::ostream& operator<<(std::ostream& out, Color color)
	{
		out << getColorName(color); // print our color's name to whatever output stream out
		return out;                 // operator<< conventionally returns its left operand

		// The above can be condensed to the following single line:
		// return out << getColorName(color)
	}

overloading >> to input 'enum'
	// pet is an in/out parameter
	std::istream& operator>>(std::istream& in, Pet& pet)
	{
		std::string s{};
		in >> s; // get input string from user

		std::optional<Pet> match { getPetFromString(s) };
		if (match) // if we found a match
		{
			pet = *match; // dereference std::optional to get matching enumerator
			return in;
		}

		// We didn't find a match, so input must have been invalid
		// so we will set input stream to fail state
		in.setstate(std::ios_base::failbit);

		// On an extraction failure, operator>> zero-initializes fundamental types
		// Uncomment the following line to make this operator do the same thing
		// pet = {};

		return in;
	}
}
/** SCOPED ENUMERATIONS (ENUM CLASSES) */
{
'scoped enums' have a few differences:
	dont implicitly convert to integers
	enumerators only exist within the scope region
	to declare one, 'enum class' is used insteads
	
integer val can still be accessed via 'static_cast'
// can also static_cast int to enumerator
// C++23 std::to_underlying() is better
// defined in <utility> header
generally favor scoped enums over unscoped ones

similar to 'using namespace' 'using enum' imports all enumerators into current scope
}
/** INTRODUCTION TO STRUCTS, MEMBERS, AND MEMBER SELECTION */
{
a 'struct' allows bundling multiple vars into a single type
// structs are 'class types'
	struct Employee{
		int id {};
		int age {};
		double wage {};
	};
	// the vars are called 'data members/member vars'

to access members, use 'member-selection-operator.'
	// assignment can be done this way as well
	int main(){
		Employee joe {};
		joe.age = 32;  // use member selection operator (.) to select the age member of variable joe
		std::cout << joe.age << '\n'; // print joe's age
		return 0;
	}
}
/** STRUCT AGGREGATE INITIALIZATION */
{
'member vars' arent initialized inherently
// this leads to undefined behavior
	int main(){
		Employee joe; // note: no initializer here either
		std::cout << joe.id << '\n';
		return 0;
	}
	// global declaration zero initializes all members by default

'aggregate': type that has multiple data members broadly
structs are aggregates
structs use 'aggregate initialization' which allows multiple initializations
uses a 'initializer list'
// 2 types:
    Employee frank = { 1, 32, 60000.0 }; // copy-list initialization using braced list
    Employee joe { 2, 28, 45000.0 };     // list initialization using braced list (preferred)
// C++ 20:
	Employee robert ( 3, 45, 62500.0 );  // direct initialization
	// generally avoid this wont work with std::array

missing members will be zero initialized:
	Employee joe { 2, 28 }; // joe.whatever will be value-initialized to 0.0

'default initialization' values can be provided as well:
	struct Employee{
		int id {};
		int age {};
		double wage { 76000.0 };
		double whatever;
	};

'operator<<' can be overloaded to print a 'struct' as well:
	std::ostream& operator<<(std::ostream& out, const Employee& e)
	{
		out << e.id << ' ' << e.age << ' ' << e.wage;
		return out;
	} // structs can be expensive, so passing by ref is nice here

vars of a 'struct' type can be 'const' && 'constexpr'
// like all other vars, must be initialized

initialization happens in order of declaration
// what if that order is jumbled? consider:
	struct Foo{
		int a {};
		int b {}; // just added
		int c {};
	};
	int main(){
		Foo f { 1, 3 }; // now, f.a = 1, f.b = 3, f.c = 0
		return 0;
	}
	// above B was added so C now zero initializes
	
C++20 above can be resolved with 'designated initializers':
// list must go in order of declaration:
    Foo f1{ .a{ 1 }, .c{ 3 } }; // ok: f1.a = 1, f1.b = 0 (value initialized), f1.c = 3
    Foo f2{ .a = 1, .c = 3 };   // ok: f2.a = 1, f2.b = 0 (value initialized), f2.c = 3
    Foo f3{ .b{ 2 }, .a{ 1 } }; // error: initialization order does not match order of declaration in struct

assignment can also be done via lists like initialization:
    Employee joe { 1, 32, 60000.0 };
    joe = { joe.id, 33, 66000.0 }; // Joe had a birthday and got a raise
	// joe.id was passed in to preserve the original current value

assignment also works with 'designated initializers':
	Employee joe { 1, 32, 60000.0 };
    joe = { .id = joe.id, .age = 33, .wage = 66000.0 }; // Joe had a birthday and got a raise
	// if joe.id were omitted, it would take its value

'struct' can be initialized with another 'struct' of the same type:
	Employee foo {0, 1, 2};
	Employee x = foo;
	Employee y(foo);
	Employee z{foo};
}
/** DEFAULT MEMBER INITIALIZATION */
{
some 'default initializations':
	struct Something{
		int x;       // no initialization value (bad)
		int y {};    // value-initialized by default
		int z { 2 }; // explicit default value
	};
	int main(){
		Something s1; // s1.x is uninitialized, s1.y is 0, and s1.z is 2
		return 0;
	}
	// explicit init takes precedence over default

best practice: provide a 'default val'
best practce: prefer value initialization over 'default'
	Fraction f1;        
	Fraction f2 {}; 
	// f2 accounts for anything potentially uninitialized
}
/** PASSING AND RETURNING STRUCTS */
{
structs are generally passed by reference (usually 'const')
	struct Employee{
		int id {};
		int age {};
		double wage {};
	};
	void printEmployee(const Employee& employee) // note pass by reference here
	{
		std::cout << "ID:   " << employee.id << '\n';
		std::cout << "Age:  " << employee.age << '\n';
		std::cout << "Wage: " << employee.wage << '\n';
	}

'temporary structs' can be created as well one time usage:
	printEmployee(Employee { 14, 32, 24.15 });
	// this is a rval and initialized and destroyed by same expression

structs are typically returned by val to avoid dangling
// here temporary is preferred:
	Point3d getZeroPoint(){
		return Point3d { 0.0, 0.0, 0.0 }; // return an unnamed Point3d
	}
// if return type is explicit can even omit the type
	Point3d getZeroPoint(){
		// We already specified the type at the function declaration
		// so we don't need to do so here again
		return { 0.0, 0.0, 0.0 }; // return an unnamed Point3d
	}
	// this is an implicit conversion
}
/** STRUCT MISCELLANY */
{
other program-defined types can be used in structs
types can also be nested within other types
	struct Company{
		struct Employee // accessed via Company::Employee
		{
			int id{};
			int age{};
			double wage{};
		};
		int numberOfEmployees{};
		Employee CEO{}; // Employee is a struct within the Company struct
	};
	int main(){
		Company myCompany{ 7, { 1, 32, 55000.0 } }; // Nested initialization list to initialize Employee
		std::cout << myCompany.CEO.wage << '\n'; // print the CEO's wage
		return 0;
	}

generally members should be owners // not viewers
// aka a pointer a ref, etc. this is to avoid dangling

structs are as large as the sum of its members + padding
	struct Foo1
	{
		short a{}; // will have 2 bytes of padding after a
		int b{};
		short c{}; // will have 2 bytes of padding after c
	};
	struct Foo2
	{
		int b{};
		short a{};
		short c{};
	};
	// foo 1 = 12 bytes, foo 2 = 8 bytes
minimize padding by defining members in decreasing order of size
// largest first, smallest last
}
/** MEMBER SELECTION WITH POINTERS AND REFERENCES */
{
reference are simply aliases so 'operator.' will function
pointers, however need to be dereferenced:
    Employee* ptr{ &joe };
    std::cout << (*ptr).id << '\n';
	// this is rather ugly, however

instead C++ provides the 'arrow operator->'
    Employee* ptr{ &joe };
    std::cout << ptr->id << '\n';
// always use the arrow operator instead of dereferencing and .
}
/** CLASS TEMPLATES */
{
'class template' is definition in instantiating 'class types'
	template <typename T>
	struct Pair{
		T first{};
		T second{};
	};

// templates can be used for functions to take in the template structs
	template <typename T>
	constexpr T max(Pair<T> p){
		return (p.first < p.second ? p.second : p.first);
	}

// or a general template can be used for all types:
	template <typename T>
	void print(T p) // type template parameter will match anything
	{
		std::cout << '[' << p.first << ", " << p.second << ']'; // will only compile if type has first and second members
	}

// std::pair can be used generally to mimic above:
	template <typename T, typename U>
	void print(std::pair<T, U> p){
		// the members of std::pair have predefined names `first` and `second`
		std::cout << '[' << p.first << ", " << p.second << ']';
	}
	int main(){
		std::pair<int, double> p1{ 1, 2.3 }; // a pair holding an int and a double
		std::pair<double, int> p2{ 4.5, 6 }; // a pair holding a double and an int
		std::pair<int, int> p3{ 7, 8 };      // a pair holding two ints
		print(p2);
		return 0;
	}
	// std::pair is basically a struct template with 2 vals
	// typename and class are interchangeable
		template<class T1, class T2>
		struct pair {
			T1 first;
			T2 second;
		};
		int main() {
			std::pair<int, std::string> idName{1, "Alice"};
			std::cout << idName.first << " - " << idName.second << '\n';
		}

'class templates' are also exempt from the ODR
// they are typically defined in the header files themselves
}
/** CLASS TEMPLATE ARGUMENT DEDUCTION (CTAD) AND DEDUCTION GUIDES */
{
C++17 'template classes' can deduce the 'template types' from the initializer
called 'class template argument deduction' aka CTAD
	#include <utility> // for std::pair
	int main()
	{
		std::pair<int, int> p1{ 1, 2 }; // explicitly specify class template std::pair<int, int> (C++11 onward)
		std::pair p2{ 1, 2 };           // CTAD used to deduce std::pair<int, int> from the initializers (C++17)
		return 0;
	}

CTAD is only performed when there are no args present
// below would trigger errors as CTAD isnt initiated:
	#include <utility> // for std::pair
	int main(){
		std::pair<> p1 { 1, 2 };    // error: too few template arguments, both arguments not deduced
		std::pair<int> p2 { 3, 4 }; // error: too few template arguments, second argument not deduced
		return 0;
	}

CTAD C++17 doesnt deduce 'template args' in aggregate templates
instead have to use a 'deduction guide':
	// Here's a deduction guide for our Pair (needed in C++17 only)
	// Pair objects initialized with arguments of type T and U should deduce to Pair<T, U>
	template <typename T, typename U>
	Pair(T, U) -> Pair<T, U>;
// another 1 with only 1 template type
	// Here's a deduction guide for our Pair (needed in C++17 only)
	// Pair objects initialized with arguments of type T and T should deduce to Pair<T>
	template <typename T>
	Pair(T, T) -> Pair<T>;
	// C++20 this isnt necessary anymore

'template params' can also have 'default vals':
	template <typename T=int, typename U=int> // default T and U to type int
	struct Pair
	{
		T first{};
		U second{};
	};

CTAD wont work in the scope of initialization:
	struct Foo{
		std::pair<int, int> p1{ 1, 2 }; // ok, template arguments explicitly specified
		std::pair p2{ 1, 2 };           // compile error, CTAD can't be used in this context
	};
// function scope, however is fine:
	int main(){
		std::pair p3{ 1, 2 };           // ok, CTAD can be used here
		return 0;
	}

CTAD also doesnt work in function params
}
/** ALIAS TEMPLATES */
{
aliases can be used as per usual:
	using Point = Pair<int>; // create normal type alias

'alias template' used to instantiate type aliases
// these dont have to declare distinct types
	// Here's our alias template
	// Alias templates must be defined in global scope
	template <typename T>
	using Coord = Pair<T>; // Coord is an alias for Pair<T>

	// Our print function template needs to know that Coord's template parameter T is a type template parameter
	template <typename T>
	void print(const Coord<T>& c){
		std::cout << c.first << ' ' << c.second << '\n';
	}

'template aliases' must be defined in global scope (like all templates)
CTAD doesnt work in function params so 'template args' need to be explicitly stated
	template <typename T>
	void print(const Coord<T>& c){
		std::cout << c.first << ' ' << c.second << '\n';
	}
}


