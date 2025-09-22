/** INTRODUCTION TO CONTAINERS AND ARRAYS */
{
'container': type that stores unnamed objects aka 'elements'
'size': num of 'elements' in a container
most 'container' are homogenous: can only have 'elements' of same type
'array': contiguous block of memory
	std::vector, std::array, c-style array
}
/** INTRODUCTION TO STD::VECTOR AND LIST CONSTRUCTORS */
{
std::vector is a temp that takes in a type
	#include <vector>
	int main(){
		// Value initialization (uses default constructor)
		std::vector<int> empty{}; // vector containing 0 int elements
		return 0;
	}

op[] can be used to access 'elements' via index
// [] doesnt do bounds checking, if invalid index is given, undefined behavior
arrays allow random access
std::vector has constructor number of elements
	std::vector<int> data( 10 );

array in program-defined type:
// direct init is disallowed:
	struct Foo{
		std::vector<int> v{ std::vector<int>(8) }; // ok
	};

std::vector cannot be made 'constexpr'
}
/** STD::VECTOR AND THE UNSIGNED LENGTH AND SUBSCRIPT PROBLEM */
{
'size_type' usually an alias 'std::size_t'
getting the size:
	#include <iostream>
	#include <vector>
	int main()
	{
		std::vector prime { 2, 3, 5, 7, 11 };
		std::cout << "length: " << prime.size() << '\n'; // returns length as type `size_type` (alias for `std::size_t`)
		return 0;
	}
// C++17
	#include <iostream>
	#include <vector>
	int main()
	{
		std::vector prime { 2, 3, 5, 7, 11 };
		std::cout << "length: " << std::size(prime); // C++17, returns length as type `size_type` (alias for `std::size_t`)

		return 0;
	}
// since they return std::size_t itll result in narrowing error
// static_cast is necessary here
	#include <iostream>
	#include <vector>
	int main()
	{
		std::vector prime { 2, 3, 5, 7, 11 };
		int length { static_cast<int>(prime.size()) }; // static_cast return value to int
		std::cout << "length: " << length ;
		return 0;
	}
// C++20
// this will return a signed type:
	#include <iostream>
	#include <vector>
	int main()
	{
		std::vector prime{ 2, 3, 5, 7, 11 };
		std::cout << "length: " << std::ssize(prime); // C++20, returns length as a large signed integral type

		return 0;
	}
// [] doesnt have bounds checking, .at() does:
	#include <iostream>
	#include <vector>
	int main()
	{
		std::vector prime{ 2, 3, 5, 7, 11 };
		std::cout << prime.at(3); // print the value of element with index 3
		std::cout << prime.at(9); // invalid index (throws exception)
		return 0;
	}
	// .at() is safer, but slower than []
}
/** PASSING STD::VECTOR */
{
std::vector is expensive to copy, hence pass by ref is usual
// type info should be stated in params:
	void passByRef(const std::vector<int>& arr) // we must explicitly specify <int> here
	{
		std::cout << arr[0] << '\n';
	}

templates used when arrays need different types:
	template <typename T>
	void passByRef(const std::vector<T>& arr)
	{
		std::cout << arr[0] << '\n';
	}
// or a template that will accept anything with [] op
	template <typename T>
	void passByRef(const T& arr) // will accept any type of object that has an overloaded operator[]
	{
		std::cout << arr[0] << '\n';
	}
// C++20 auto can be used as well to similar effect:
	void passByRef(const auto& arr) // abbreviated function template
	{
		std::cout << arr[0] << '\n';
	}
}
/** ARRAYS AND LOOPS */
{
index of array can be used in loops
	#include <iostream>
	#include <vector>
	int main(){
		std::vector testScore { 84, 92, 76, 81, 56 };
		std::size_t length { testScore.size() };

		int average { 0 };
		for (std::size_t index{ 0 }; index < length; ++index) // index from 0 to length-1
			average += testScore[index];                      // add the value of element with index `index`
		average /= static_cast<int>(length);                  // calculate the average

		std::cout << "The class average is: " << average << '\n';
		return 0;
	}
accessing each element of a container has a few names:
	'traversal' && 'iteration'
}
/** ARRAYS, LOOPS, AND SIGN CHALLENGE SOLUTIONS */
{
'decltype' resoloves to the type of array
// arr is some non-reference type
	for (decltype(arr)::size_type index { 0 }; index < arr.size(); ++index)

'std::ptrdiff_t' can be used as the signd 'std::size_t'
C++23 can use Z suffix to denote literal val of 'std::ptrdiff_t'
	for (auto index{ 0Z }; index < static_cast<std::ptrdiff_t>(arr.size()); ++index)
	
'std::ssize' outputs signd array size as 'ptrdiff_t'
    for (auto index{ std::ssize(arr)-1 }; index >= 0; --index) // std::ssize introduced in C++20
        std::cout << arr[static_cast<std::size_t>(index)] << ' ';
	
'.data' can be used to index underlying c-style array
// allows for both unsigned and signed indices
	   auto length { static_cast<Index>(arr.size()) };  // in C++20, prefer std::ssize()
    for (auto index{ length - 1 }; index >= 0; --index)
        std::cout << arr.data()[index] << ' '; 

// generally just avoid indices altogether
// use iterators and range-based for loops (for each)
}
/** RANGE-BASED FOR LOOPS (FOR-EACH) */
{
'range-based for loops' can traverse a container without direct indexing
// also known as for each loops
    std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
    for (int num : fibonacci) // iterate over array fibonacci and copy each value into `num`
       std::cout << num << ' '; // print the current value of `num`
// the first field for for each loop should match the type of the array
// favor for each loops over regular loops for arrays
above can also be deduced via 'auto'
    for (auto num : fibonacci) // compiler will deduce type of num to be `int`
       std::cout << num << ' ';
// this is also best practice
element declarations can be made 'const reference'
// string is expensive to copy
    std::vector<std::string> words{ "peter", "likes", "frozen", "yogurt" };
    for (const auto& word : words) // word is now a const reference
        std::cout << word << ' ';
		
general rules range-based loops:
	auto when you want to modify copies of the elements
	auto& when you want to modify the original elements
	const auto& otherwise (when you just need to view the original elements)

range-based loops only interate forwards, but a reverse view can be generated
    for (const auto& word : std::views::reverse(words)) // create a reverse view
        std::cout << word << ' ';
}
/** ARRAY INDEXING AND LENGTH USING ENUMERATORS */
{
unscoped enums can be used to document specific array indices:
	#include <vector>
	namespace Students{
		enum Names{
			kenny, // 0
			kyle, // 1
			stan, // 2
			butters, // 3
			cartman, // 4
			max_students // 5
		};
	}
	int main(){
		std::vector testScores { 78, 94, 66, 77, 14 };
		testScores[Students::stan] = 76; // we are now updating the test score belonging to stan
		return 0;
	}

a count enumerator helps record the number of enumerators:
    enum Names
    {
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        // add future enumerators here
        max_students // 5
    };

count can also be used with assert to make sure container has valid length:
	assert(std::size(testScores) == max_students);
	// for constexpr arrays use static_assert

scoped enums can also be used, but must be converted via some methods:
// static_cast:
	#include <iostream>
	#include <vector>
	enum class StudentNames{
		kenny, // 0
		kyle, // 1
		stan, // 2
		butters, // 3
		cartman, // 4
		max_students // 5
	};
	int main(){
		std::vector<int> testScores(static_cast<int>(StudentNames::max_students));
		testScores[static_cast<int>(StudentNames::stan)] = 76;
		std::cout << "The class has " << static_cast<int>(StudentNames::max_students) << " students\n";
		return 0;
	}
// or overload the unary operator: 
	constexpr auto operator+(StudentNames a) noexcept
	{
		return static_cast<std::underlying_type_t<StudentNames>>(a);
	}
}
/** STD::VECTOR RESIZING AND CAPACITY */
{
'resize()' can be used to set another desired length
    std::vector v{ 0, 1, 2 }; // create vector with 3 elements
    v.resize(5);              // resize to 5 elements
// the original elements are preserved
// the new elements are value initialized (default init and zero init)
// they can also be resized to be smaller
'capacity': how much memory has been allocated
'length': how many elements in usage
'capacity()' can be used to get the capacity of a vector
// reallocation is expensive
// vector indexing is based on length not capacity
// capacity is managed automatically
decreasing a vectors length wont decrease it's capacity
'shrink_to_fit()' can shrink the vector's capacity to match the length
// use in cases where there are large number of unused elements
// is non-binding so implementation may choose to ignore it
}
/** STD::VECTOR AND STACK BEHAVIOR */
{
a stack is last-in, first-out (LIFO)
	'stack' in programming is a data type where insertion/removal occurs in LIFO
	'push' element on top of stack
	'pop' remove top element from stack
	'top/peek' get the top element without removing
	'empty' check stack empty
	'size' count how many elements are on stack
std::vector, std::deque, std::list all allow stack behavior

// some stack functions with std::vector:
	push_back() add element on top of stack
	pop_back() remove top element from stack: returns 'void'
	back() get top element without removal
	emplace_back() potentially more efficient 'push_back'
push_back() && emplace_back() will reallocate memory when needed
reserve() changes the capacity but no length

use 'emplace_back' when creating a temp obj to pass
use 'push_back' when obj already exists
}

