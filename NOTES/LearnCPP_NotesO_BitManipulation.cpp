/** BIT FLAGS AND BIT MANIPULATION VIA STD::BITSET */

modern architectures need at least 1 byte per value
'bool' is wasteful cause it only needs 1 bit (0 && 1)
	bool foo { true }; // bool uses 8 bits so 1 byte of memory

'std::bitset' can pack 8+ bools into compact bytes to save memory
each digit of the bit can be used as bools

// creation of a bitset var using standard library
	#include <bitset>
	std::bitset<8> foo{}; // a bitset containing 8 bits ie: 0000 1000

bit positions are numbered right to left starting from 0
76543210 // bit positions

// some bitset operations
	test()	// return bit true/false
	set()	// set bit to 1
	reset()	// set bit to 0
	flip() 	// toggle bit 0/1

'binary literal' is prefixed with '0b' && seperated in groups of 4 with '
	std::bitset<8> bits{0b0000'0101}
	bits.set(3) 	// result: 0000 1101
	bits.flip(4)	// result: 0001 1101
	bits.reset(4)	// result: 0000 1101

you can map your named bools to a bitset:
// these represent the position of the bits in the bitset
    [[maybe_unused]] constexpr int isHungry   { 0 };
    [[maybe_unused]] constexpr int isSad      { 1 };
    [[maybe_unused]] constexpr int isMad      { 2 };
    [[maybe_unused]] constexpr int isHappy    { 3 };
    [[maybe_unused]] constexpr int isLaughing { 4 };
    [[maybe_unused]] constexpr int isAsleep   { 5 };
    [[maybe_unused]] constexpr int isDead     { 6 };
    [[maybe_unused]] constexpr int isCrying   { 7 };
	
std::bitset<N> stores N bits, but its object size is implementation-defined. 
Most implementations back it with chunks of an 'unsigned' integer type (often 32/64 bits). 
As a result, 'sizeof(std::bitset<N>)' is usually rounded up to the nearest multiple of that chunk size.
usually 8 bytes as a 'unsigned long long' in most x64 architectures && 4 bytes as a 'unsigned long' in most x32 architecture
	std::bitset<8> foo{0b0000'0000} // this is only 1 byte, but will round up to 8
	
// some more functions:
	size() 	// returns number of bits
	count() // returns number of 1 bits
	all() 	// returns bool whether all bits are 1
	any() 	// returns bool whether any bits are 1
	none() 	// returns bool whether all bits are 0
	
/** BITWISE OPERATORS */

bitwise operations are all non-modifying && can be used with integral types && std::bitset

// list of operators (they are all non-modifying)
	// bitwise operations are ENDIAN-IGNOSTIC so << is always MSB and >> always LSB
	// the compiler knows if <</>> should be output/input or bitwise operation based on left operand being an intergral type vs stream
	x << n // LEFT SHIFT by n positions, new bits are 0
		0011 << 1 : is 0110
		0011 << 2 : is 1100
		0011 << 3 : is 1000
		
	x >> n // RIGHT SHIFT by n positions, new bits are 0
		1100 >> 1 : is 0110
		1100 >> 2 : is 0011
		1100 >> 3 : is 0001
		
	~x 		// NOT: all bits in x are flipped
		~0011 is 1100
		
	x | y // OR: bits positions are matched and if 1 is present then evaluates to 1
		0101 | 0111 		: is 0111
		0101 | 1010 | 0000 	: is 1111
		
	x & y // AND: bits positions are matched and if both are 1 evaluetes to 1
		0101 & 0110			: is 0100
		1011 & 1100 & 1010	: is 1000
		
	x ^ y // XOR: if 1 appears an odd number of times, then evaluates to true
	0110 ^ 0010			: is 0100
	0110 ^ 0010 ^ 1111	: is 1011

all aformentioned bitwise operators can be made to assign with = so >>= <<= &= |= ^=
bitwise '~NOT' is unary so just use assignment '=' ie: x = ~x/
bitwise operators promote operands with narrower integral types to 'int/unsigned int' 
'~' && '<<' are width-sensitive so they should be 'static_cast'
avoid bit shifting on integral types smaller than 'int'

/** BIT MANIPULATION WITH BITWISE OPERATORS AND BIT MASKS **/

bit masks can specify what sequence of bits bitwise-operators modify
// a simple definition: uses one bit mask per position 1 denotes that we want the bit to be modified
	#include <cstdint>
	constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
	constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
	constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
	constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
	constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
	constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
	constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
	constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7
	
// a cleaner way using bitwise operators
	constexpr std::uint8_t mask0{ 1 << 0 }; // 0000 0001
	constexpr std::uint8_t mask1{ 1 << 1 }; // 0000 0010
	constexpr std::uint8_t mask2{ 1 << 2 }; // 0000 0100
	constexpr std::uint8_t mask3{ 1 << 3 }; // 0000 1000
	constexpr std::uint8_t mask4{ 1 << 4 }; // 0001 0000
	constexpr std::uint8_t mask5{ 1 << 5 }; // 0010 0000
	constexpr std::uint8_t mask6{ 1 << 6 }; // 0100 0000
	constexpr std::uint8_t mask7{ 1 << 7 }; // 1000 0000
	
// they can also be defined with hexadecimals
	constexpr std::uint8_t mask0{ 0x01 }; // hex for 0000 0001
	constexpr std::uint8_t mask1{ 0x02 }; // hex for 0000 0010
	constexpr std::uint8_t mask2{ 0x04 }; // hex for 0000 0100
	constexpr std::uint8_t mask3{ 0x08 }; // hex for 0000 1000
	constexpr std::uint8_t mask4{ 0x10 }; // hex for 0001 0000
	constexpr std::uint8_t mask5{ 0x20 }; // hex for 0010 0000
	constexpr std::uint8_t mask6{ 0x40 }; // hex for 0100 0000
	constexpr std::uint8_t mask7{ 0x80 }; // hex for 1000 0000
	
bit masks can be used with '&' && the target 
// this tests whether a bit is on 
	static_cast<bool>(0b0000'0101 & mask0)	// output would be 1 (then cast to true)
// set a bit or multiple bits
	0b0000'0101 |= mask1					// output would be 0000 0111 
	0b0000'0101 |= (mask1 | mask7)			// output would be 1000 0111
// reseting/turning off a bit(s)
	0b0000'0101 &= ~mask2 					// output would be 0000 0001
	0b0000'0101 &= ~(mask2 | mask0)			// output would be 0000 0000
	//operator ~ force promotes mask2 to int so may have to static_cast to std::uint_8
// flipping a bit
	0b0000'0101 ^= mask1					// output would be 0000 0111
	0b0000'0101 ^= (mask1 | mask2)			// output would be 0000 0011

'std::bitset' functions can be useful in to change individual bits
bitmasks can modify multiple bits at once as mentioned above

bitmasks should be named based on what the bit they mask represent:
// variables for a game with std::uint_8
	[[maybe_unused]] constexpr std::uint8_t isHungry   { 1 << 0 }; // 0000 0001
	[[maybe_unused]] constexpr std::uint8_t isSad      { 1 << 1 }; // 0000 0010
	[[maybe_unused]] constexpr std::uint8_t isMad      { 1 << 2 }; // 0000 0100
	[[maybe_unused]] constexpr std::uint8_t isHappy    { 1 << 3 }; // 0000 1000
	[[maybe_unused]] constexpr std::uint8_t isLaughing { 1 << 4 }; // 0001 0000
	[[maybe_unused]] constexpr std::uint8_t isAsleep   { 1 << 5 }; // 0010 0000
	[[maybe_unused]] constexpr std::uint8_t isDead     { 1 << 6 }; // 0100 0000
	[[maybe_unused]] constexpr std::uint8_t isCrying   { 1 << 7 }; // 1000 0000
	std::uint8_t me{}; 			// initialized with 0000 0000 so no emotions
	me |= (isHappy | isLaughing)// +happy +laughing
	me &= ~isLaughing 			// -laughing
	
// variables for a game with std::bitset
	[[maybe_unused]] constexpr std::bitset<8> isHungry   { 0b0000'0001 };
	[[maybe_unused]] constexpr std::bitset<8> isSad      { 0b0000'0010 };
	[[maybe_unused]] constexpr std::bitset<8> isMad      { 0b0000'0100 };
	[[maybe_unused]] constexpr std::bitset<8> isHappy    { 0b0000'1000 };
	[[maybe_unused]] constexpr std::bitset<8> isLaughing { 0b0001'0000 };
	[[maybe_unused]] constexpr std::bitset<8> isAsleep   { 0b0010'0000 };
	[[maybe_unused]] constexpr std::bitset<8> isDead     { 0b0100'0000 };
	[[maybe_unused]] constexpr std::bitset<8> isCrying   { 0b1000'0000 };
	std::bitset<8> me{};			// initialized with 0000 0000 so no emotions
	me |= (isHappy | isLaughing);	// +happy +laughing
	me &= ~isLaughing; 				// -laughing
	
// for bitset masks technically aren't necessary when just using as bool so:
    [[maybe_unused]] constexpr int isHungry   { 0 };
    [[maybe_unused]] constexpr int isSad      { 1 };
    [[maybe_unused]] constexpr int isMad      { 2 };
    [[maybe_unused]] constexpr int isHappy    { 3 };
    [[maybe_unused]] constexpr int isLaughing { 4 };
    [[maybe_unused]] constexpr int isAsleep   { 5 };
    [[maybe_unused]] constexpr int isDead     { 6 };
    [[maybe_unused]] constexpr int isCrying   { 7 };
	std::bitset<8> me{};			// initialized with 0000 0000 so no emotions
	me.set(isHappy).set(isLaughing);// +happy +laughing
	me.reset(isLaughing);			// -laughing
	
// you can technically store this in an enum with std::size_t or std::uint8/16/32_t
// bitset functions expect std::size_t so thats the best type for the enum
	enum Emotion : std::size_t {
	  Hungry=0, Sad, Mad, Happy, Laughing, Asleep, Dead, Crying
	};
	std::bitset<8> me{};			// initialized with 0000 0000 so no emotions
	me.set(Happy).set(Laughing);	// +happy +laughing
	me.reset(Laughing);				// -laughing
	
8 'bool' would be 8 bytes
8 'std::uint8_t' + 1 'flag variable' would be 9 bytes
so why use bit manipulation at all?

bitflags are best when there are many identical flags.
so something like emotions; the masks are representations of positions
so instead of having:
	// andrew's emotions
    [[maybe_unused]] bool isAndrewHungry   { false }; 	// 1 byte per pop
    [[maybe_unused]] bool isAndrewSad      { false };
    [[maybe_unused]] bool isAndrewMad      { false };
    [[maybe_unused]] bool isAndrewHappy    { false };
    [[maybe_unused]] bool isAndrewLaughing { false };
    [[maybe_unused]] bool isAndrewAsleep   { false };
    [[maybe_unused]] bool isAndrewDead     { false };
    [[maybe_unused]] bool isAndrewCrying   { false };
	// leland's emotions
	[[maybe_unused]] bool isLelandHungry   { false }; 
    [[maybe_unused]] bool isLelandSad      { false };
    [[maybe_unused]] bool isLelandMad      { false };
    [[maybe_unused]] bool isLelandHappy    { false };
    [[maybe_unused]] bool isLelandLaughing { false };
    [[maybe_unused]] bool isLelandAsleep   { false };
    [[maybe_unused]] bool isLelandDead     { false };
    [[maybe_unused]] bool isLelandCrying   { false }; 	
	// ...however many more people						// 8 bytes * however many people
	// what if people had 64 flags though? 				// 64 bytes * however many people
	
a set of masks can be used && the emotions can simply be stored in a bitset
    [[maybe_unused]] constexpr std:size_t isAndrewHungry   { 0 }; // constexpr so no runtime allocation
    [[maybe_unused]] constexpr std:size_t isAndrewSad      { 1 };
    [[maybe_unused]] constexpr std:size_t isAndrewMad      { 2 };
    [[maybe_unused]] constexpr std:size_t isAndrewHappy    { 3 };
    [[maybe_unused]] constexpr std:size_t isAndrewLaughing { 4 };
    [[maybe_unused]] constexpr std:size_t isAndrewAsleep   { 5 };
    [[maybe_unused]] constexpr std:size_t isAndrewDead     { 6 };
    [[maybe_unused]] constexpr std:size_t isAndrewCrying   { 7 };
	
	std::bitset<8> andrewEmotions{}; 					// 8 bytes on standard 64-bit
	std::bitset<8> lelandEmotions{}; 					// 8 bytes on standard 64-bit
	// ...however many more people						// 8 bytes * however many people
	// what if people had 64 flags though? 				// 8 bytes * however many people
	
bit masks usually modify 1 bit, but some cases can modify many
example 32-bit RGBA on televisions: 
	//RGBA are each respresented as 8 bit unsigned integer
	constexpr std::uint32_t redBits{ 0xFF000000 };
	constexpr std::uint32_t greenBits{ 0x00FF0000 };
	constexpr std::uint32_t blueBits{ 0x0000FF00 };
	constexpr std::uint32_t alphaBits{ 0x000000FF };
	std::uint32_t pixel{};
	// these masks allow manipulation of the individual RGBA channels (8 bits per mask)
	// this is why RGBA and RGB are commonly represented as hex
	
/** CONVERTING INTEGERS BETWEEN BINARY AND DECIMAL REPRESENTATION */

standard numbering system has 0-9 so subsequent digits are '10^n'
binary only has 0 && 1 so subsequent digits are '2^n'

// binary to decimal
ie: 0101 1110 as decimal
	2 ^ 7 = 128 : digit is 0 so : +00
	2 ^ 6 = 64	: digit is 1 so : +64
	2 ^ 5 = 32 	: digit is 0 so : +00
	2 ^ 4 = 16 	: digit is 1 so : +16
	2 ^ 3 = 8 	: digit is 1 so : +08
	2 ^ 2 = 4 	: digit is 1 so : +04
	2 ^ 1 = 2 	: digit is 1 so : +02
	2 ^ 0 = 1	: digit is 0 so : +00
'result'						: /94

// decimal to binary method 1
ie: 148
	148 / 2 = 74 	r0
	74 / 2 = 37 	r0
	37 / 2 = 18 	r1
	18 / 2 = 9 		r0
	9 / 2 = 4 		r1
	4 / 2 = 2 		r0
	2 / 2 = 1 		r0
	1 / 2 = 0 		r1
	'result'	:	/1001 0100

// decimal to binary method 2
working forward, simply ask consecutive questions based in the value of the integer
ie: 148
	148 >= 128 					: 1
	148 !> 128 + 64 			: 10
	148 !> 128 + 32				: 100
	148 >= 128 + 16 = 144		: 1001
	148 !> 144 + 8				: 1001 0
	148 == 144 + 4 = 148		: 1001 01 // the number matches so don't need to continue
	'result'					:/1001 0100
// decimal to binary method 3
divide && strip the remainder
	148/128 = 1 : 1 is odd 		: 1
	148/64 - 2	: 2 is even 	: 0
	148/32 = 4	: 4 is even 	: 0
	148/16 = 9	: 9 is odd 		: 1
	148/8 = 18	: 18 is even 	: 0
	148/4 = 37	: 37 is odd		: 1 // the lowest common denominator so technically don't have to keep going
	148/2 = 74	: 64 is even	: 0
	148/1 = 148	: 148 is even	: 0
	'result'					:/1001 0100
	
// binary addition
	0 + 0 = 0
	0 + 1 = 1
	1 + 0 = 1
	1 + 1 = 0 //carry over 1 to next column
	//examples
	  1001
	  0110
	:/1111
	  0101
	  0101
	:/1010
	  0111
	  0111
	:/1110
	  1000
	  1000
	:/10000
	// a new digit is necessary here just as 9999 goes to 10000

to represent negative numbers '2s complement' is used
'2s complement' uses the first digit to 'wrap' around && uses the first digit as the boundary
hence why a '8-bit signed int' is -128 to 127 && '8-bit unsigned int' is 0 to 255
// normally in unsigned:
	0111 = 7
	1000 = 8
	1001 = 9
	1111 = 15

// signed
	0111 = 7 			// this is the largest possible positive number
	1000 = -8			// this is where it wraps around
	1001 = -8+1	= -7
	1111 = -8+7 = -1

checking whether the first digit in a 'signed int' is 1, we will know whether it is a negative number
assuming it is 1 then inverting it will result in the negative + 1
subtracting 1 will then net the correct value of the binary (which can then be negated)

// decimal to binary (two's compliment) for -5
	0000 0101 // binary for 5
	1111 1010 // invert 
	1111 1011 // +1

// binary to decimal (two's compliment)
	1001 1110	// check that it is signed, if not then just use usual method
	0110 0001 	// invert
	0110 0010 	// +1
				// now convert like usual number
	0110 0010 	=/ 98
	'result'	=/-98