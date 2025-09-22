/** THE HIDDEN “THIS” POINTER AND MEMBER FUNCTION CHAINING */
{
'this': 'const pointer' holds address of implicit obj
	void print() const { std::cout << m_id; }       // implicit use of this
	void print() const { std::cout << this->m_id; } // explicit use of this

'this' can also be used to retrn the implicit obj
    Calc& add(int value) { m_value += value; return *this; }
    Calc& sub(int value) { m_value -= value; return *this; }
    Calc& mult(int value) { m_value *= value; return *this; }
// this can now be used to chain:
	calc.add(5).sub(3).mult(4); // method chaining
	// this always points to implicit obj so null check isnt necessary

can also be used to reset an object
	void reset(){
		*this = {}; // value initialize a new object and overwrite the implicit object
	}
}
/** CLASSES AND HEADER FILES */
{
member function definitions can be seperated from declaration:
	#include <iostream>
	class Date{
	private:
		int m_year{};
		int m_month{};
		int m_day{};
	public:
		Date(int year, int month, int day); // constructor declaration
		void print() const; // print function declaration
		int getYear() const { return m_year; }
		int getMonth() const { return m_month; }
		int getDay() const  { return m_day; }
	};
	Date::Date(int year, int month, int day) // constructor definition
		: m_year{ year }
		, m_month{ month }
		, m_day{ day }
	{
	}
	void Date::print() const // print function definition
	{
		std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
	};
	int main(){
		const Date d{ 2015, 10, 14 };
		d.print();
		return 0;
	}
// can be broken up into a header and cpp file:
// header
	#ifndef DATE_H
	#define DATE_H
	class Date{
	private:
		int m_year{};
		int m_month{};
		int m_day{};
	public:
		Date(int year, int month, int day);

		void print() const;

		int getYear() const { return m_year; }
		int getMonth() const { return m_month; }
		int getDay() const { return m_day; }
	};
	#endif
// cpp
	#include "Date.h"
	Date::Date(int year, int month, int day) // constructor definition
		: m_year{ year }
		, m_month{ month }
		, m_day{ day }
	{
	}
	void Date::print() const // print function definition
	{
		std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
	};
// best practice: put class definitions in header
// non trivial functions in a seperate cpp file
// trivial access functions within the class itself
}
/** NESTED TYPES (MEMBER TYPES) */
{
types can be nested:
	#include <iostream>
	class Fruit{
	public:
		// FruitType has been moved inside the class, under the public access specifier
			// We've also renamed it Type and made it an enum rather than an enum class
		enum Type{
			apple,
			banana,
			cherry
		};
	private:
		Type m_type {};
		int m_percentageEaten { 0 };
	public:
		Fruit(Type type) :
			m_type { type }
		{
		}
		Type getType() { return m_type;  }
		int getPercentageEaten() { return m_percentageEaten;  }
		bool isCherry() { return m_type == cherry; } // Inside members of Fruit, we no longer need to prefix enumerators with FruitType::
	};
	int main(){
		// Note: Outside the class, we access the enumerators via the Fruit:: prefix now
		Fruit apple { Fruit::apple };
		if (apple.getType() == Fruit::apple)
			std::cout << "I am an apple";
		else
			std::cout << "I am not an apple";
		return 0;
	}
	// generally define them at the top of the class
	// scoping is no longer necessary as the class itself acts as the scope
// typedefs can also be nested

nested classes though uncommon can be done:
// in this case, the nested class cant access the 'this' pointer of outer class
// hence an explicit object must be passed in
// however, can access private vars of outer class
	#include <iostream>
	#include <string>
	#include <string_view>
	class Employee{
	public:
		using IDType = int;
		class Printer{
		public:
			void print(const Employee& e) const{
				// Printer can't access Employee's `this` pointer
				// so we can't print m_name and m_id directly
				// Instead, we have to pass in an Employee object to use
				// Because Printer is a member of Employee,
				// we can access private members e.m_name and e.m_id directly
				std::cout << e.m_name << " has id: " << e.m_id << '\n';
			}
		};
	private:
		std::string m_name{};
		IDType m_id{};
		double m_wage{};
	public:
		Employee(std::string_view name, IDType id, double wage)
			: m_name{ name }
			, m_id{ id }
			, m_wage{ wage }
		{
		}
		// removed the access functions in this example (since they aren't used)
	};
	int main(){
		const Employee john{ "John", 1, 45000 };
		const Employee::Printer p{}; // instantiate an object of the inner class
		p.print(john);
		return 0;
	}

nested types can be forward declared as well:
	#include <iostream>
	class outer{
	public:
		class inner1;   // okay: forward declaration inside the enclosing class okay
		class inner1{}; // okay: definition of forward declared type inside the enclosing class
		class inner2;   // okay: forward declaration inside the enclosing class okay
	};
	class inner2 // okay: definition of forward declared type outside the enclosing class
	{
	};
	int main(){
		return 0;
	}
}
/** INTRODUCTION TO DESTRUCTORS */
{
destructors run when an object is destroyed
destructors have rules:
	The destructor must have the same name as the type, preceded by a tilde (~).
	The destructor cant take arguments.
	The destructor doesnt have a 'return type'
// generally destructors shouldnt be called explicitly
// an example:
	#include <iostream>
	class Simple{
	private:
		int m_id {};
	public:
		Simple(int id)
			: m_id { id }
		{
			std::cout << "Constructing Simple " << m_id << '\n';
		}
		~Simple() // here's our destructor
		{
			std::cout << "Destructing Simple " << m_id << '\n';
		}
		int getID() const { return m_id; }
	};
	int main(){
		// Allocate a Simple
		Simple simple1{ 1 };
		{
			Simple simple2{ 2 };
		} // simple2 dies here
		return 0;
	} // simple1 dies here
// if a class doesnt have a destructor then the compiler generates an implicit one
'std::exit' terminates a program immediately
// no local vars are destroyed, hence no destructors are called
// no cleanup occurs in this case
}
/** CLASS TEMPLATES WITH MEMBER FUNCTIONS */
{
	#include <ios>       // for std::boolalpha
	#include <iostream>
	template <typename T>
	class Pair{
	private:
		T m_first{};
		T m_second{};
	public:
		// When we define a member function inside the class definition,
		// the template parameter declaration belonging to the class applies
		Pair(const T& first, const T& second)
			: m_first{ first }
			, m_second{ second }
		{
		}
		bool isEqual(const Pair<T>& pair);
	};
	// When we define a member function outside the class definition,
	// we need to resupply a template parameter declaration
	template <typename T>
	bool Pair<T>::isEqual(const Pair<T>& pair){
		return m_first == pair.m_first && m_second == pair.m_second;
	}
	int main(){
		Pair p1{ 5, 6 }; // uses CTAD to infer type Pair<int>
		std::cout << std::boolalpha << "isEqual(5, 6): " << p1.isEqual( Pair{5, 6} ) << '\n';
		std::cout << std::boolalpha << "isEqual(5, 7): " << p1.isEqual( Pair{5, 7} ) << '\n';
		return 0;
	}
}
/** STATIC MEMBER VARIABLES */
{
'static member vars' are shared by all instances of the type
'static member vars' exist even when no objects of the type are instantiated
'static inline/constexpr' can be used to adhere to ODR in headers
'auto' may be used in CTAD
	class Foo{
	private:
		auto m_x { 5 };           // auto not allowed for non-static members
		std::pair m_v { 1, 2.3 }; // CTAD not allowed for non-static members
		static inline auto s_x { 5 };           // auto allowed for static members
		static inline std::pair s_v { 1, 2.3 }; // CTAD allowed for static members
	public:
		Foo() {};
	};
}
/** STATIC MEMBER FUNCTIONS */
{
'static members functions' can be called even with no instance of an object
// they also have no 'this pointer'
'static member functions' should also be made 'inline' in headers
a 'static class' is preferable to a 'namespace' due to access
}
/** FRIEND NON-MEMBER FUNCTIONS */
{
'friend' allows function to have access to 'private/protected'
	#include <iostream>
	class Accumulator{
	private:
		int m_value { 0 };
	public:
		void add(int value) { m_value += value; }
		// Here is the friend declaration that makes non-member function void print(const Accumulator& accumulator) a friend of Accumulator
		friend void print(const Accumulator& accumulator);
	};
	void print(const Accumulator& accumulator){
		// Because print() is a friend of Accumulator
		// it can access the private members of Accumulator
		std::cout << accumulator.m_value;
	}
	int main(){
		Accumulator acc{};
		acc.add(5); // add 5 to the accumulator
		print(acc); // call the print() non-member function
		return 0;
	}
	// print isnt a member function, but can access the values
when a 'friend' function is defined in type, it isnt a member
its treated as a non-member function
	#include <iostream>
	class Accumulator{
	private:
		int m_value { 0 };
	public:
		void add(int value) { m_value += value; }
		// Friend functions defined inside a class are non-member functions
		friend void print(const Accumulator& accumulator){
			// Because print() is a friend of Accumulator
			// it can access the private members of Accumulator
			std::cout << accumulator.m_value;
		}
	};
	int main(){
		Accumulator acc{};
		acc.add(5); // add 5 to the accumulator
		print(acc); // call the print() non-member function
		return 0;
	}
a function can have multiple 'friends':
	class Humidity; // forward declaration of Humidity
	class Temperature{
	private:
		int m_temp { 0 };
	public:
		explicit Temperature(int temp) : m_temp { temp } { }
		friend void printWeather(const Temperature& temperature, const Humidity& humidity); // forward declaration needed for this line
	};

	class Humidity{
	private:
		int m_humidity { 0 };
	public:
		explicit Humidity(int humidity) : m_humidity { humidity } {  }
		friend void printWeather(const Temperature& temperature, const Humidity& humidity);
	};
	// forward declare is needed so temp knows what humidity is
}
/** FRIEND CLASSES AND FRIEND MEMBER FUNCTIONS */
{
'friend class' can access 'private/protected' of other type
	#include <iostream>
	class Storage{
	private:
		int m_nValue {};
		double m_dValue {};
	public:
		Storage(int nValue, double dValue)
		   : m_nValue { nValue }, m_dValue { dValue }
		{ }

		// Make the Display class a friend of Storage
		friend class Display;
	};
	class Display
	{
	private:
		bool m_displayIntFirst {};
	public:
		Display(bool displayIntFirst)
			 : m_displayIntFirst { displayIntFirst }
		{
		}
		// Because Display is a friend of Storage, Display members can access the private members of Storage
		void displayStorage(const Storage& storage){
			if (m_displayIntFirst)
				std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
			else // display double first
				std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
		}
		void setDisplayIntFirst(bool b){
			 m_displayIntFirst = b;
		}
	};
owning type doesnt have 'friend' types '*this' pointer
friendship isnt transitive:
	A friendly with B 
	B friendly with C
	A isnt friendly with C
friendship isnt reciprocal:
	A friendly with B
	B isnt friendly with A
friendship statements can act as forward declarations as well

member functions of another type can also be made friendly
	friend void Display::displayStorage(const Storage& storage);
}
/** REF QUALIFIERS */
{
allow overloadin of function based on rval/lval
	const std::string& getName() const &  { return m_name; } //  & qualifier overloads function to match only lvalue implicit objects, returns by reference
	std::string        getName() const && { return m_name; } // && qualifier overloads function to match only rvalue implicit objects, returns by value
sample usage:
	#include <iostream>
	#include <string>
	#include <string_view>
	class Employee{
	private:
		std::string m_name{};
	public:
		Employee(std::string_view name): m_name { name } {}

		const std::string& getName() const &  { return m_name; } //  & qualifier overloads function to match only lvalue implicit objects
		std::string        getName() const && { return m_name; } // && qualifier overloads function to match only rvalue implicit objects
	};
	// createEmployee() returns an Employee by value (which means the returned value is an rvalue)
	Employee createEmployee(std::string_view name){
		Employee e { name };
		return e;
	}
	int main(){
		Employee joe { "Joe" };
		std::cout << joe.getName() << '\n'; // Joe is an lvalue, so this calls std::string& getName() & (returns a reference)
		std::cout << createEmployee("Frank").getName() << '\n'; // Frank is an rvalue, so this calls std::string getName() && (makes a copy)
		return 0;
	}
// generally this isnt used too much
// qualified and unqualified are mutually exclusive
// they cant be used in interjunction
}
