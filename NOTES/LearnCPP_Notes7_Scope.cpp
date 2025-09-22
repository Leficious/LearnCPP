/** COMPOUND STATEMENTS (BLOCKS) */
{
'{}' indicates a block
tells compiler to treat as single statement; can be anywhere a normal statement is
'{}' can be nested unlike functions; when done so known as the 'inner block' (vs 'outer block')
'nesting depth' = max number of nested blocks one can be inside in a given functions
C++ standard: compilers support 256 levels of nesting (though they dont all)
best practice: nesting depth < 3
}
/** USER-DEFINED NAMESPACES AND THE SCOPE RESOLUTION OPERATOR */ 
{
a 'namespace' is a way to group related identifiers (like classes, functions, variables, constants, etc.)
'namespace' contents exist like lifetime variables/functions: they dont support OOP like classes
'namespace' exists to prevent naming conflicts:
	namespace NamespaceIdentifier{
		// content of namespace here
	}

generally 'namespace' identifier's first letter is capitalized
namespaces are accessed via 'scope resolution operator ::'
	namespace Foo {
		int doSomething(int x, int y){
			return x + y;
		}
	}
	namespace Goo{
		int doSomething(int x, int y){
			return x - y;
		}
	}
	int main(){
		std::cout << Foo::doSomething(4, 3) << '\n'; // use the doSomething() that exists in namespace Foo
		return 0;
	}

when '::' is used with no identifier it looks in the 'global namespace'
when identifier is used in 'namespace' it attempts to find match within its own 'namespace'
// if nothing is found, containing namespaces are checked until global (last)
// this outputs: 'Hello there':
	#include <iostream>
	void print() { 	// this print() lives in the global namespace
		std::cout << " there\n";
	}
	namespace Foo{
		void print() {	// this print() lives in the Foo namespace
			std::cout << "Hello";
		}

		void printHelloThere(){
			print();   // calls print() in Foo namespace
			::print(); // calls print() in global namespace
		}
	}
	int main(){
		Foo::printHelloThere();
		return 0;
	}

cpp && header definition + forward declarations:
// add.h
	#ifndef ADD_H
	#define ADD_H
	namespace BasicMath{
		int add(int x, int y);
	}
	#endif

// add.cpp
	#include "add.h"
	namespace BasicMath{
		int add(int x, int y){
			return x + y;
		}
	}
// main.cpp
	#include "add.h" // for BasicMath::add()
	#include <iostream>
	int main(){
		std::cout << BasicMath::add(4, 3) << '\n';
		return 0;
	}

it is ok to have 'namespace blocks' with same identifier in different places
// in circle.h
	namespace BasicMath{
		constexpr double pi{ 3.14 };
	}
// in growth.h
	namespace BasicMath{
		constexpr double e{ 2.7 };
	}
// in main.cpp
	#include "circle.h" // for BasicMath::pi
	#include "growth.h" // for BasicMath::e
	#include <iostream>
	int main(){
		std::cout << BasicMath::pi << '\n';
		std::cout << BasicMath::e << '\n';
		return 0;
	}

std does so a lot; each stdlibrary header has declarations inside std 'namespace block'
prevents 1 massive header file
theoritically user can add to 'std namespace' but c++ prohibits it generally
// do not add custom functionality to the std namespace.
namespaces can also be nested
// how to nest it is stylistic choice
	#include <iostream>
	namespace Foo{
		namespace Goo{
			int add(int x, int y){
				return x + y;
			}
		}
	}
	int main(){
		std::cout << Foo::Goo::add(1, 2) << '\n'; // accessed via 2 '::'
		return 0;
	}
	
// C++17 this is also acceptable after
// if Foo doesnt exist already, compiler implicitly creates
	namespace Foo::Goo {
		int add(int x, int y){
			return x + y;
		}
	}
	
chains of namespaces can be declared as vars with aliases
	namespace Active = Foo::Goo; // active now refers to Foo::Goo
// ensures non-destructive workflow when changing namespaces
	namespace Active = Buu::Tuu; // active now refers to Buu::Tuu

namespaces best in large projects with lots of 3rd-party libraries
smaller projects usually !necessary
code that is intended to be distributes MUST be namespaces to prevent conflicts
// a top level namespace usually is enough 
avoid more than 3 levels of 'namespace' nesting 
}
/** LOCAL VARIABLES */
{
C++ doesnt have specific attribute that defines local var
when an identifies cannot be accessed, it is 'out of scope'
// local vars have block scope:
	int main(){
		int i { 5 }; // i enters scope here
		double d { 4.0 }; // d enters scope here
		return 0;
	} // d and i go out of scope here
	
// function params part of function body block
	int max(int x, int y){ // x and y enter scope here
		int max{ (x > y) ? x : y }; // max enters scope here
		return max;
	} // max, y, and x leave scope here
	
// all var identifiers within scope must be unique:
	void someFunction(int x){
		int x{}; // compilation failure due to name collision with function parameter
	}
// local variables have automatic storage duration: 
// hence theyre sometimes called 'automatic vars'
	int main(){
		int i { 5 }; // i created and initialized here
		double d { 4.0 }; // d created and initialized here
		return 0;
	} // d and i are destroyed here

local vars have no linkage: linkage determines whether a declaration of that same identifier in different scope refers to the same object
local variables have no linkage: each declaration of an identifier with no linkage refers to a unique object function
// scope determines whether an identifer can be seen and used
// duration defines the rules for when var is created and destroyed
// lifetime is the actual time between creation and destruction
// linkage determines whether multiple declarations of an object refer to the same object
	int main(){
		int x { 2 }; // local variable, no linkage
		{ 
			int x { 3 }; // this declaration of x refers to a different object than the previous x
		}
		return 0;
	}

vars should be defined in most limited scope;
'x' is only used in a single block, it should be defined in that block
}
/** INTRODUCTION TO GLOBAL VARIABLES */
{
C++ vars can be declared outside of a function, hence 'global vars'
'global vars' are usually declared at top of file below includes
'global vars' have 'global namespace scope' sometimes called 'file scope'
// global vars can be inside a user-defined namespace
// best practice is to define global vars in a namespace rather than global namespace
// below g_x is limited to scope of Foo but Foo::g_x is still accessible globally
	#include <iostream>
	namespace Foo { // Foo is defined in the global scope
		int g_x {}; // g_x is now inside the Foo namespace, but is still a global variable
	}

'global vars' are created before 'main()' && destroyed after it ends
such is called 'static duration'; vars with 'static duration' are calld 'static vars'
conventionally 'global vars' in 'global namespace' are prefixed with 'g' || 'g_' 
'global vars' within user-defined 'namespace' doesnt need prefix
// global vars' are zero-initialized by default
// local cars are non-initialized by default
	int g_x;       // no explicit initializer (zero-initialized by default)
	int g_y {};    // value initialized (resulting in zero-initialization)
	int g_z { 1 }; // list initialized with specific value

'global vars' can be made 'const' && 'constexpr'
as with all constants, 'const/constexpr global vars' must be initialized
// non const global vars should generally be avoided
	const int g_x;     // error: constant variables must be initialized
	constexpr int g_w; // error: constexpr variables must be initialized
	const int g_y { 1 };     // const global variable g_y, initialized with a value
	constexpr int g_z { 2 }; // constexpr global variable g_z, initialized with a value
}
/** VARIABLE SHADOWING (NAME HIDING) */
{
when a nested block has a var with same identifier as a var in an outer block it becomes shadowed
the nested var hides the outer var in areas where they are both in scope
generally called 'name hiding' || 'shadowing'
// when inside a nested block there's no way to access the shadowed var
	#include <iostream>
	int main(){ // outer block
		int apples { 5 }; // here's the outer block apples
		{ // nested block
			// apples refers to outer block apples here
			std::cout << apples << '\n'; // print value of outer block apples
			int apples{ 0 }; // define apples in the scope of the nested block

			// apples now refers to the nested block apples
			// the outer block apples is temporarily hidden

			apples = 10; // this assigns value 10 to nested block apples, not outer block apples
			std::cout << apples << '\n'; // print value of nested block apples
		} // nested block apples destroyed
		std::cout << apples << '\n'; // prints value of outer block apples
		return 0;
	} // outer block apples destroyed
	
'local vars' can shadow 'global vars' as well
	#include <iostream>
	int value { 5 }; // global variable
	void foo(){
		std::cout << "global variable value: " << value << '\n'; // value is not shadowed here, so this refers to the global value
	}
	int main(){
		int value { 7 }; // hides the global variable value (wherever local variable value is in scope)
		++value; // increments local value, not global value
		std::cout << "local variable value: " << value << '\n';
		foo();
		return 0;
	} // local value is destroyed
// in this case :: can be used to specify the global var if needed
generally variable shadowing should be avoided
}
/** INTERNAL LINKAGE */
{
an identifier's linkage determines whether other declarations of that name refer to the same object
hence local vars have 'no linkage'
'global var' can have 'internal linkage' || 'external linkage'
'internal linkage' = can be seen/used in single translation unit but NOT others
'global var' with 'internal linkage' is called 'internal var'
	static int g_x{}; // non-constant globals have external linkage by default, but can be given internal linkage via the static keyword
	const int g_y{ 1 }; // const globals have internal linkage by default
	constexpr int g_z{ 2 }; // constexpr globals have internal linkage by default

functions have 'external linkage' but 'static' can change them to be 'interal linkage'
objects with 'internal linkage' are independant entities && dont violate the ODR
generally 'static' to label 'internal linkage' isnt convention anymore
unnamed 'namespace' is used in lieu
'internal linkage' is desirable when:
there's an identifier we dont want accessible to other files
we want to avoid pedantic naming conventions && collisions
modern development recommends making every var unused in other files 'internal linkage'
}
/** EXTERNAL LINKAGE AND VARIABLE FORWARD DECLARATIONS */
{
'external linkage' indicates an indentifier can be used by other files
'external linkage' makes things visible to the linker, thus allows:
	connection of identifier from one translation unit to another
	deduplicate 'inline' identifiers so one canon definition remains
	
functions have 'external linkage' unless otherwise defined
in order to call a function from another file a forward declaration is necessary
forward declaration tells linker about existence of function in that file
'global vars' with 'external linkage' are called 'external vars'
// extern constexpr is useless because constexpr cannot be forward declared
	extern const int g_y { 3 }; // const globals can be defined as extern, making them external
	extern constexpr int g_z { 3 }; // constexpr globals can be defined as extern, making them external 
	int g_x { 2 }; // non-constant globals are external by default (no need to use extern)

to use an 'external var' a forward declaration is necessary
function forward declarations dont need 'extern' unlike vars
// for an uninitialized non-const global var do not use extern, C++ will think of it as a forward declaration
	extern int g_x;       // this extern is a forward declaration of a variable named g_x that is defined somewhere else
	extern const int g_y; // this extern is a forward declaration of a const variable named g_y that is defined somewhere else

//extern can be both a ext linkage marker and a forward declaration marker
	// non-constant
	int g_x;        // variable definition (no initializer)
	int g_x { 1 };  // variable definition (w/ initializer)
	extern int g_x; // forward declaration (no initializer)
	extern int g_x { 1 }; // variable definition (w/ initializer)
	// constant
	extern const int g_y { 1 }; // variable definition (const requires initializers)
	extern const int g_y;       // forward declaration (no initializer)

generally only use 'extern' in 'global var forward declaration' || 'const global var definitions'
}
/* WHY (NON-CONST) GLOBAL VARIABLES ARE EVIL **/
{
generally avoid 'global vars' that arent 'const'; prefer 'local vars'
'global vars' flexibility is also dangerous: any function can modify it
the var may have been changed elsewhere && it isnt immediately obvious
	#include <iostream>
	int g_mode; // declare global variable (will be zero-initialized by default)
	void doSomething(){
		g_mode = 2; // set the global g_mode variable to 2
	}
	int main(){
		g_mode = 1; // note: this sets the global g_mode variable to 1.  It does not declare a local g_mode variable!
		doSomething();
		// Programmer still expects g_mode to be 1
		// But doSomething changed it to 2!
		if (g_mode == 1){
			std::cout << "No threat detected.\n";
		}
		else{
			std::cout << "Launching nuclear missiles...\n";
		}
		return 0;
	}
	
g_mode may be changed/referenced hundreds of times in a given program
to track down bugs one would have to dissect exactly when && where everything that effects it happens
'static vars' which includes 'global vars' are initialized before 'int main()' in phases
	'static initialization': 2 subphases
		'constant initialization': 'global vars' with 'constexpr' are initialized to assigned values
		'zero initialization': 'gloval vars' initializers are zero-initialized
	'dynamic initialization': non-'constexpr' 'global vars' are initialized
generally (in a single file) 'globar vars' are initialized in order of definition
// there are a few exceptions in dynamic initialization
	#include <iostream>
	int initX();  // forward declaration
	int initY();  // forward declaration
	int g_x{ initX() }; // g_x is initialized first
	int g_y{ initY() };
	int initX(){
		return g_y; // g_y isn't initialized when this is called
	}
	int initY(){
		return 5;
	}
	int main(){
		std::cout << g_x << ' ' << g_y << '\n';
	}

across files 'static var' initialization is ambiguous: 'static initialization order fiasco'
dont init objects with 'static' duration with objects from a different translation unit
'global vars' should avoid 'dynamic initilization' due to order issues
usage of 'non-const global vars' is rare; in cases where theres a many to one relationship
	a log file: there's a single log file to write to in a program that all files need access to
	a global random number generator	// see later chapter 8
	
'non-const global var' general guidelines:
	there should only ever be one of the thing the variable represents in the program
	its use should be ubiquitous throughout the program
'global var' usage best practice:
	ideally should be in 'namespace'
	no 'namespace' identifiers should have prefix 'g' || 'g_' 
	instead of direct access via 'extern' indirect access via a helper function (inherently 'extern')
	// constants.cpp
		namespace constants{
			constexpr double gravity { 9.8 }; // has internal linkage, is accessible only within this file
		}
		double getGravity() // has external linkage, can be accessed by other files
		{
			return constants::gravity;
		}
	// main.cpp
		#include <iostream>
		double getGravity(); // forward declaration
		int main(){
			std::cout << getGravity() << '\n';
			return 0;
		}
	
	instead of directly passing in 'global var' to function bodies, use a param instead to pass by arg
		#include <iostream>
		namespace constants{
			constexpr double gravity { 9.8 };
		}
		// This function can calculate the instant velocity for any gravity value (more useful)
		double instantVelocity(int time, double gravity){
			return gravity * time;
		}
		int main(){
			std::cout << instantVelocity(5, constants::gravity) << '\n'; // pass our constant to the function as a parameter
			return 0;
		}
}
/** INLINE FUNCTIONS AND VARIABLES */
{
creating a function has overheads: known as 'function calls'
larger functions dont really care: smaller ones its more significant
'inline expansion' replaces code with the functions definition
allows further optimizations by the compiler such as constant expression
'inlines' can cause the executable size to grow
use 'inline' only when there are simple functions (less than a few statements)
every function either 'may be expanded' || 'cant be expanded'
// most functions may be expanded so the compiler makes the call
// a function whose definition is in another translation unit cant be expanded
best pratice: dont use 'inline expansion'  

modernly, 'inline' can be used to mark a function that can be defined in multiple translation units
// this allows them to bypass the ODR
there are 2 primary requirements:
	the compiler needs to see the full definition of the 'inline' function
	every definition must be identical
compilers will consolidate 'inline' functions into a single definition:
// main.cpp
	#include <iostream>
	double circumference(double radius); // forward declaration
	inline double pi() { return 3.14159; }
	int main(){
		std::cout << pi() << '\n';
		std::cout << circumference(2.0) << '\n';
		return 0;
	}
//math.cpp
	inline double pi() { return 3.14159; }
	double circumference(double radius){
		return 2.0 * pi() * radius;
	}
without 'inline' here the ODR would be broken
with 'inline' the function is deduplicated to comform to the ODR
'inline functions' are typically in header files at the top
'header-only libraries' make use of them (so no cpp file is necessary)
best practice: generally avoid 'inline' unless defining in header file 
}
/** SHARING GLOBAL CONSTANTS ACROSS MULTIPLE FILES (USING INLINE VARIABLES) */
{
certain values are need to be shared in many places
prior to C++17 the solution:
	create a header file
	define a 'namespace'
	add 'constexpr' vars inside
	'#include' the header where needed
'const' globals have 'internal linkage' so each cpp file with header will get a seperate variable
// most of the time the compiler will optimize these away due to constexpr
// can be taxing on compile times
// changing the header requires recompiling

post C++17 solution:
'global const inline vars' can have more than one definition assuming theyre identical
they can be defined in a header file && '#include' in any CPP file
// this avoid both duplication and ODR violations
// constexpr functions are implicitly inline, constexpr vars are not so they must be marked
// constants.h
	#ifndef CONSTANTS_H
	#define CONSTANTS_H
	namespace constants{
		inline constexpr double pi { 3.14159 }; // note: now inline constexpr
		inline constexpr double avogadro { 6.0221413e23 };
		inline constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
		// ... other related constants
	}
	#endif
// main.cpp
	#include "constants.h"
	#include <iostream>
	int main(){
		std::cout << "Enter a radius: ";
		double radius{};
		std::cin >> radius;
		std::cout << "The circumference is: " << 2 * radius * constants::pi << '\n';
		return 0;
	}
}
/** STATIC LOCAL VARIABLES */
{
'static global var' gives 'interal linkage'
'static local var' changes duration from 'automatic' to 'static' 
var is now created at start of program just like 'global var'\
hence will retain value even when out of scope
'static' local vars are zero-initialized 
best practice: use 's_' to prefix 'static' vars
'const static local var' are generally okay to use.
'non-const static local var' should generally be avoided
'non-const static local var' shouldnt alter program flow
}
/** USING DECLARATIONS AND USING DIRECTIVES */
{
qualified name is a name that includes an associated scope '::'
'using' allows usage of an unqualified name after specifying the qualified name
// using declarations are generally acceptable
// using-statements have block scope normally
// if done in a namespace (including global then they have file scope)
	#include <iostream>
	int main(){
	   using std::cout; // this using declaration tells the compiler that cout should resolve to std::cout
	   cout << "Hello world!\n"; // so no std:: prefix is needed here!
	   return 0;
	} // the using declaration expires at the end of the current scope
directives allows unqualified access to all the names in the 'namespace'
// this increases chance of naming collisions
dont use 'using-statements' in header files || before an include
theres no way to revert a 'using-statement' the closest thing would be with {} due to block scope
best practice: generally avoid 'using-statement' && use qualifiers with '::'
}
/** UNNAMED AND INLINE NAMESPACES */
{
'unnamed namespaces' are treated like part of the parent 'namespace'
it makes all of its contents internally linked basically 'static'
they shouldnt be used in header files generally

'inline namespace' are treated like part of the parent 'namespace'
theyre used to version content; they dont affect linkage
	#include <iostream>
	inline namespace V1 // declare an inline namespace named V1{
		void doSomething()
		{
			std::cout << "V1\n";
		}
	}
	namespace V2 // declare a normal namespace named V2{
		void doSomething()
		{
			std::cout << "V2\n";
		}
	}
	int main(){
		V1::doSomething(); // calls the V1 version of doSomething()
		V2::doSomething(); // calls the V2 version of doSomething()
		doSomething(); // calls the inline version of doSomething() (which is V1)
		return 0;
	}
}