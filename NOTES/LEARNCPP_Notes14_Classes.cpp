/** INTRODUCTION TO OBJE TED PROGRAMMING */
{
OOP focuses on program-defined data types that contain properties && behaviour
// code that looks like this is OOP:
	you.eat(apple);
	// the object itself owns the behavior of eating
// as opposed to procedural programming:
	eat(you, apple);
	// procedural programming: logic isolated from data it works on

4 pillars of OOP (APIE):
	inheritence
	encapsulation
	abstraction
	polymorphism
}
/** INTRODUCTION TO CLASSES */
{
issue with structs: they dont document/enforce invariants
'class invariant': a condition that must be 'true' through the lifespan of an object
consider the following:
	#include <iostream>
	struct Fraction{
		int numerator { 0 };
		int denominator { 1 }; // class invariant: should never be 0
	};
	void printFractionValue(const Fraction& f){
		 std::cout << f.numerator / f.denominator << '\n';
	}
	int main(){
		Fraction f { 5, 0 };   // create a Fraction with a zero denominator
		printFractionValue(f); // cause divide by zero error
		return 0;
	}
	// nothing explicitly prevents the class invariant from an invalid val

relying on users to maintain invariants isnt maintainable
thus, enforcement mechanism at the point of initialization would be nice

classes are the solution:
	class Employee
	{
		int m_id {};
		int m_age {};
		double m_wage {};
	};
	// most of the std are classes; std::string && std::string_view
}
/** MEMBER FUNCTIONS */
{
'class' supports member functions aka 'member functions'
// an example:
	#include <iostream>
	struct Date{
		int year {};
		int month {};
		int day {};
		void print() // defines a member function named print
		{
			std::cout << year << '/' << month << '/' << day;
		}
	};
	int main(){
		Date today { 2020, 10, 14 }; // aggregate initialize our struct
		today.day = 16; // member variables accessed using member selection operator (.)
		today.print();  // member functions also accessed using member selection operator (.)
		return 0;
	}
	
member functions are implicitly 'inline' thus adhere with ODR
member functions can also be forward declared in the 'class definition'
the targeted object of a member function call is implicitly the caller
non-member vars must be declared before usage
// the compiler does a trick: it forward declares the premature functions
// and the lists their definitions at the end of the struct
member vars inside a 'class definition' dont have such restriction
// generally avoid using other members inside initializers
member functions can also be overloaded
in C structs only have data members
in C++ structs can have both
// generally structs should avoid constructors which make them no longer aggregates
}
/** CONST CLASS OBJECTS AND CONST MEMBER FUNCTIONS */
{
'class type objects (struct, class, union)' can also be 'const'
their vals must be initialized at creation && cant be modified
'constexpr' also is allowed
'non const members function' cannot be called by 'non-const functions'
	#include <iostream>
	struct Date{
		int year {};
		int month {};
		int day {};
		void print(){
			std::cout << year << '/' << month << '/' << day;
		}
	};
	int main(){
		const Date today { 2020, 10, 14 }; // const
		today.print();  // compile error: can't call non-const member function
		return 0;
	}
	
// to address this const can be used to mark a const member function
// guarantees it wont modify the object or call any non-const member
    void print() const // now a const member function
    {
        std::cout << year << '/' << month << '/' << day;
    }
	// const functions can modify non-members like local vars and params
	// they can also call non-const non-member functions
// tldr: const member func cannot modify the implicit object nor call non-const functions on the implicit object
// a const member function can be called on non-const objects

overloading can also be done via 'constness of member functions'
	struct Something{
		void print(){
			std::cout << "non-const\n";
		}
		void print() const{
			std::cout << "const\n";
		}
	};
	
// overloading in this manner is only done when return val needs to differ in constness
// this is very rare:
	int main(){
		Something s1{};
		s1.print(); // calls print()
		const Something s2{};
		s2.print(); // calls print() const
		return 0;
	}
}
/** PUBLIC AND PRIVATE MEMBERS AND ACCESS SPECIFIERS */
{
each member of a 'class type' has an access level
C++ has 3 levels: 'public, private, protected'
structs have 'public' members (unless otherwise stated)
// public members can be accessed by other members of the same class
// they can also be accessed by outside members aka 'the public'

classes have 'private' members (unless otherwise stated)
C++ aggregates also cannot have any 'non-public' vars:
	#include <iostream>
	class Date // now a class instead of a struct
	{
		// class members are private by default, can only be accessed by other members
		int m_year {};     // private by default
		int m_month {};    // private by default
		int m_day {};      // private by default
		void print() const // private by default
		{
			// private members can be accessed in member functions
			std::cout << m_year << '/' << m_month << '/' << m_day;
		}
	};
	int main(){
		Date today { 2020, 10, 14 }; // compile error: can no longer use aggregate initialization
		// private members can not be accessed by the public
		today.m_day = 16; // compile error: the m_day member is private
		today.print();    // compile error: the print() member function is private
		return 0;
	}
	
m_ prefix is used conventionally in naming C++ 'private vars'
access specifiers can be used to denote access of all following members
	class Date
	{
	// Any members defined here would default to private
	public: // here's our public access specifier
		void print() const // public due to above public: specifier
		{
			// members can access other private members
			std::cout << m_year << '/' << m_month << '/' << m_day;
		}
	private: // here's our private access specifier
		int m_year { 2020 };  // private due to above private: specifier
		int m_month { 14 }; // private due to above private: specifier
		int m_day { 10 };   // private due to above private: specifier
	};

structs should avoid access altogether
// structs should be aggregates hence can only have public members
classes generally only have 'protected/private' vars
access levels work on a 'per-class' basis:
	#include <iostream>
	#include <string>
	#include <string_view>
	class Person{
	private:
		std::string m_name{};

	public:
		void kisses(const Person& p) const{
			std::cout << m_name << " kisses " << p.m_name << '\n';
		}

		void setName(std::string_view name){
			m_name = name;
		}
	};
	int main(){
		Person joe;
		joe.setName("Joe");
		Person kate;
		kate.setName("Kate");
		joe.kisses(kate);
		return 0;
	}
	// even though joe and kate are distinct objects
	// they have access to each other's names because theyre the same type

the only difference between 'struct' && 'class':
'struct' members are 'public', 'class' members are 'private'
// also inheritance is also public/private
}
/** ACCESS FUNCTIONS */
{
access functions are trivial functions that retrieve/change 'private vars'
	getters are 'public functions' that get a 'private var'
	// also called accessors
	setters are 'public functions' that change a 'private var'
	// also called mutators

there are no standardized naming conventions
// they cnn simply be prefixed:
	int getDay() const { return m_day; }  // getter
	void setDay(int day) { m_day = day; } // setter
// or overloaded:
	int day() const { return m_day; }  // getter
	void day(int day) { m_day = day; } // setter
// or a mixture (set prefix only):
	int day() const { return m_day; }     // getter
	void setDay(int day) { m_day = day; } // setter

getters should 'return by val' || 'const lval ref'
}
/** MEMBER FUNCTIONS RETURNING REFERENCES TO DATA MEMBERS */
{
member functions can 'return by reference' as well
generally it should match the data member's type
getters can use 'auto' to deduce the type
// however, this obscures the actual type so prefer explicit return types
// dont return non-const private data members
	// this subverts the access system
'const member functions' cannot retrn 'non-const member vars'
}
/** THE BENEFITS OF DATA HIDING (ENCAPSULATION) */
{
implementation: the code that makes up the behavior itself
interface: how a user interacts with the object
'data-hiding': enforces the seperation of implementation && interface
'encapsulation' refers to 2 things:
	the enclosing of 1/more items in a container
	the bundling of data && functions on instances of an object
// prefer non-member functions when possible

ordering members in a 'class':
// schools of thought:
	'private members' first then 'public functions'
	'public functions' first then 'private members'
	// modern C++ tends towards the second one
}
/** INTRODUCTION TO CONSTRUCTORS */
{
'constructors': member function that is called after a 'non-aggregate class' is created
'constructors' dont create objects, the constructor initializes
however, assuming no matching constructor is found, it can prevent the compiler from creating an object
'aggregates' cannot have constructors
constructors must have identical name to 'class' && no 'return val'
constructors shouldnt be 'const'
// they need to initialize the object being constructed
normally a 'non-const member function' cannot act upon a 'const object'
however per the C++standard, 'const' doesnt apply to objects under construction
hence, constructors arent bound by 'constness'
} 
/** CONSTRUCTOR MEMBER INITIALIZER LISTS */
{
member initializer list constructor:
	class Foo{
	private:
		int m_x {};
		int m_y {};
	public:
		Foo(int x, int y)
			: m_x { x }, m_y { y } // here's our member initialization list
		{
			std::cout << "Foo(" << x << ", " << y << ") constructed\n";
		}
		void print() const{
			std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
		}
	};

members are initialized in order in which they are defined in the 'class'
// NOT the order in the member init list
// best pratice: init list should match class definition order
the priotity init order is as follows:
	member init list
	'default initializer'
	no initializer
	// if member init exists, then default init is ignored
	
bodies of constructor functions are oft left empty
print statements/logs can be used documentation
// generally do not put assignments in the constructor
when an invariant is invalidated, the constructor 'fails'
// the best thing to do is generally throw an exception
}
/** DEFAULT CONSTRUCTORS AND DEFAULT ARGUMENTS */
{
'default constructor': can be called with no args
	class Foo{
	public:
		Foo() // default constructor
		{}
	}; // called with Foo foo{}; or Foo foo();

'value init' && 'default init' via constructor are basically identical:
	Foo foo{}; // value initialization, calls Foo() default constructor
	Foo foo2;  // default initialization, calls Foo() default constructor
	// generally value is safer

constructors can have 'default args'
    Foo(int x=0, int y=0) // has default arguments
        : m_x { x }
        , m_y { y }
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
    }
// in this case:
    Foo foo1{};     // calls Foo(int, int) constructor using default arguments
    Foo foo2{6, 7}; // calls Foo(int, int) constructor

constructors can also be overloaded:
	public:
		Foo() // default constructor
		{
			std::cout << "Foo constructed\n";
		}

		Foo(int x, int y) // non-default constructor
			: m_x { x }, m_y { y }
		{
			std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
		}
	// this allows for different methods of construction
	// a corollary: classes should only have 1 default constructor:
	// otherwise it wont be able to disambiguate:
	public:
		Foo() // default constructor
		{
			std::cout << "Foo constructed\n";
		}

		Foo(int x=1, int y=2) // default constructor
			: m_x { x }, m_y { y }
		{
			std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
		}

assuming no constructor is provided, compiler gens one:
	class Foo{
	private:
		int m_x{};
		int m_y{};
		// Note: no constructors declared
	};
	// compiler generates: 
	public:
    Foo() // implicitly generated default constructor
    {
    }
	// this is called a implicit default constructor
	// allows default init

'= default' can be used to generate an 'explicit default constructor':
	class Foo{
	private:
		int m_x {};
		int m_y {};
	public:
		Foo() = default; // generates an explicitly defaulted default constructor
		Foo(int x, int y)
			: m_x { x }, m_y { y }
		{
			std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
		}
	};
	// in this case, an implicit one wouldnt have been generated

the only difference between 'user-defined' && 'implicit/explicit':
	'implicit/explicit' are 'zero initialized'
	'user defined' is 'default initialized'
constructors make the 'class' non-aggregate
}
/** DELEGATING CONSTRUCTORS */
{
generally dont call a constructor from the body of another constructor
constructor chaining/delegating constructors can be done:
	public:
		Employee(std::string_view name)
			: Employee{ name, 0 } // delegate initialization to Employee(std::string_view, int) constructor
		{
		}
		Employee(std::string_view name, int id)
			: m_name{ name }, m_id { id } // actually initializes the members
		{
			std::cout << "Employee " << m_name << " created\n";
		}

a delegating constructor cannot initialize
// consider using delegators to reduce repeated code
}
/** TEMPORARY CLASS OBJECTS */
{
'temporary object': has no name, exists single expressions
	int main(){
		// Case 1: Pass variable
		IntPair p { 3, 4 };
		print(p);
		// Case 2: Construct temporary IntPair and pass to function
		print(IntPair { 5, 6 } );
		// Case 3: Implicitly convert { 7, 8 } to a temporary Intpair and pass to function
		print( { 7, 8 } );
		return 0;
	}
}
/** INTRODUCTION TO THE COPY CONSTRUCTOR */
{
copy constructor: contructs with copy of obj with same type
assuming a copy constructor isnt provided, an implicit one is created
an explicitly defined copy constructor:
    // Copy constructor
    Fraction(const Fraction& fraction)
        // Initialize our members using the corresponding member of the parameter
        : m_numerator{ fraction.m_numerator }
        , m_denominator{ fraction.m_denominator }
    {
        std::cout << "Copy constructor called\n"; // just to prove it works
    }
	// copy contructors should have no side effects other than copying
	// prefer the implicit copy constructor
	// copy in param must be a reference to lval

copy constructor also invoked when passing by val:
    Fraction f{ 5, 3 };
    printFraction(f); // f is copied into the function parameter using copy constructor
	// also invoked when returning an rval

copy constructor can also be explicitly requested: 
    Fraction(const Fraction& fraction) = default;
they can also be prevented from copying:
	Fraction(const Fraction& fraction) = delete;
	// attempting to create a copy now will cause a compile error

'the rule of three':
assuming a 'class' needs a userdefined copy constructor, destructor, copy assignment op
then it should have all three
C++11: expanded to 'rule of 5':
added a move constructor && move assignment op
}
/** CLASS INITIALIZATION AND COPY ELISION */
{
list init disallowed narrowing conversions
copy init only considers non-explict constructors/conversions
list init prioritizes matching list constructors over others
consider the following:
	#include <iostream>
	class Something{
		int m_x{};
	public:
		Something(int x)
			: m_x{ x }
		{
			std::cout << "Normal constructor\n";
		}
		Something(const Something& s)
			: m_x { s.m_x }
		{
			std::cout << "Copy constructor\n";
		}
		void print() const { std::cout << "Something(" << m_x << ")\n"; }
	};
	int main(){
		Something s { Something { 5 } }; // focus on this line
		s.print();
		return 0;
	}

copy elision: allows compiler to optimize away unnecessary copies
elision bypasses the 'as-if rule': it is allowed to optimize away even when there are side effects
}
/** CONVERTING CONSTRUCTORS AND THE EXPLICIT KEYWORD */
{
user-defined conversions allow conversions of user-defined types
'explicit' can be used to prevent usage as a converting constructor
// only allowed direct and direct list init
public:
    explicit Dollars(int d) // now explicit
        : m_dollars{ d }
    {
    }
	// print(5) cannot call because dollars(int) is explicit
	// workaround: print(Dollars{5});
	// static_cast also works: print(static_cast<Dollars>(5)); 

'return vals' can also be implicit conversions:
	Foo getFoo(){
		// explicit Foo() cases
		return Foo{ };   // ok
		return { };      // error: can't implicitly convert initializer list to Foo

		// explicit Foo(int) cases
		return 5;        // error: can't implicitly convert int to Foo
		return Foo{ 5 }; // ok
		return { 5 };    // error: can't implicitly convert initializer list to Foo
	}

it is best practice to make anything that accepts a single arg 'explicit'
'copy' && 'move' constructors shouldnt be make 'explicit'
// these are typically not made explicit:
'default constructors with no params'
'constructors that accept multiple args'
// should be made explicit: 
contructors that take a single arg

}
/** CONSTEXPR AGGREGATES AND CLASSES */
{
member functions can be made 'constexpr'
aggregates implicitly support 'constexpr'
an obj cant be 'constexpr' unless the type is a literal type
non-aggregates dont qualify
a summary of what is a literal type:
	Scalar types (those holding a single value, such as fundamental types && pointers)
	Reference types
	Most aggregates
	Classes that have a 'constexpr constructor'

constructors can also be made 'constexpr'
	constexpr Pair(int x, int y): m_x { x }, m_y { y } {} // now constexpr

'constexpr members functions' may be 'const/non-const'
}