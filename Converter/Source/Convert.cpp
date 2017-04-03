#include "../headers/Convert.hpp"

#include <sstream>
using namespace std;

/**
 * Convert namspace
 */
namespace convert {

	/**
	 * class Converter (definitions)
	 */
	
	// Constructors
	Converter::Converter() {}


	/** Methods */

	/**
	 * This function will return the 
	 * appropriate hexadecimal value for
	 * the integer given.
	 * 
	 * @param   x  int
	 * @return     string
	 */
	string Converter::hex(int x) const {
		// Check if x is less than 10
		if ( x < 10 )
			return int_str(x);

		if ( x == 10 )
			return "A";
		else if ( x == 11 )
			return "B";
		else if ( x == 12 )
			return "C";
		else if ( x == 13 )
			return "D";
		else if ( x == 14 )
			return "E";
		else if ( x == 15 )
			return "F";

		return "";
	}


	/**
	 * This function will add padding to 
	 * the given string.
	 * 
	 * @param   str  string&
	 * @return       string&
	 */
	void Converter::padding(string& str) {
		// Check if string length is divisible by 4
		if (str.length() % 4 == 0)
			return;
		else {
			// Add "0" to the string until it's length
			// is not divisible by 4
			while (str.length() % 4 != 0) {
				str.insert(0, "0");
			}
		}	
	}


	/**
	 * This function will seperate every 4 
	 * bits in a string.
	 * 
	 * @param   str  string&
	 * @return       string&
	 */
	void Converter::separate(string& str) {
		// Check if str length is less than than 4
		if (str.length() <= 4)
			return;

		// Create a temperary counter
		int counter = 4;

		// Add whitespaces until the end of string
		while (counter < str.length()) {
			str.insert(counter, " ");
			counter += 5;
		}
	}


	/**
	 * This function will find and remove any
	 * whitespaces detected in the given string.
	 * 
	 * @param  str  string&
	 */
	void Converter::space_check(string& str) {
		// Check if the string is empty
		if (str.empty())
			return;

		// Loop over the string and remove any
		// whitespaces
		for (int index = 0; index != str.length(); index++) 
			if (str[index] == ' ')
				str.erase(index, 1);
	}


	/**
	 * This function will convert an
	 * integer to a string.
	 * 
	 * @param   x  int
	 * @return     string
	 */
	string Converter::int_str(int x) const {
		// Create stringstream
		ostringstream oss;

		// Insert x intp the stream
		oss << x;

		// Return the contents of the stream
		return oss.str();
	}


	/**
	 * This function will convert a string
	 * to an integer.
	 * 
	 * @param   str  const string& 
	 * @return       int
	 */
	int Converter::str_int(const string& str) const {
		// Create stringstreama and give it str
		istringstream iss( str );

		// Temperary int to hold the value of str
		int result;

		// Use the stream to give the value of str
		// to result. If it failes assign 0 to result.
		if ( !(iss >> result) )
			result = 0;

		// Return result
		return result;
	}


	/**
	 * This function will convert a character to 
	 * an integer.
	 * 
	 * @param   x  char
	 * @return     int
	 */
	int Converter::char_int(char x) const {
		return (x - '0');
	}
	
	/** 
	 * This function will convert a character to 
	 * a decimal.
	 * 
	 * @param   c  const char&
	 * @return     string
	 */
	string Converter::char_dec_s(const char& c) const {
		// Create a int to hold the decimal value of c
		int temp = int(c);

		// Convert int to string and return 
		return int_str( temp );
	}


	/**
	 * This function will convert a character to 
	 * a decimal.
	 * 
	 * @param   c  const char&
	 * @return     int
	 */
	int Converter::char_dec_i(const char& c) const {
		// Return and convert c to a decimal
		return int( c );
	}


	/**
	 * This function will convert a string to
	 * a decimal.
	 * 
	 * @param   str  const string& 
	 * @return       string
	 */
	string Converter::str_dec_s(const string& str) const {
		// Check if the string is empty
		if (str.empty())
			return "";

		// Create a temperary int to hold value of string
		int value = 0;

		// Loop through the string
		for (int index = 0; index <= str.size(); index++) {
			// Add the value of the character to the value variable
			value += int( str[index] );
		}

		// Convert int to string and return
		return int_str( value );
	}


	/**
	 * This function will convert a string to
	 * a decimal.
	 * 
	 * @param   str  const string&
	 * @return       int
	 */
	int Converter::str_dec_i(const string& str) const {
		// Check if the string is empty
		if (str.empty())
			return -1;

		// Create a temperary int to hold value of string
		int value = 0;

		// Loop through the string
		for (int index = 0; index <= str.size(); index++) {
			// Add the value of the character to the value variable
			value += int( str[index] );
		}

		// Return the string's value
		return value;
	}


	/**
	 * This function will convert a character 
	 * to a hexidecimal.
	 * 
	 * @param   c  const char& 
	 * @return     string
	 */
	string Converter::char_hex_s(const char& c) const {
		// Convert c to a decimal
		int dec = int( c );

		// Create a temperary string to hold hex value
		string hex = "";

		// Convert decimal to hexidecimal
		while ( dec != 0 ) {
			if ( dec % 16 < 10 )
				hex.insert( 0,  int_str(dec % 16) );
			else
				hex.insert( 0, this->hex(dec % 16) );

			dec /= 16;
		}

		// Return hex
		return hex;
	}


	/**
	 * This function will convert a string into
	 * its hexidecimal value.
	 * 
	 * @param   str  const string& 
	 * @return       string
	 */
	string Converter::str_hex_s(const string& str) const {
		// Get decimal value of str
		int dec = str_dec_i( str );

		// Create a temperary string to hold hex value
		string hex = "";

		// Convert decimal to hexidecimal
		while ( dec != 0 ) {
			if ( dec % 16 < 10 )
				hex.insert( 0,  int_str(dec % 16) );
			else
				hex.insert( 0, this->hex(dec % 16) );

			dec /= 16;
		}

		// Return hex
		return hex;
	}


	/**
	 * This function will convert an integer to a
	 * binary string.
	 * 
	 * @param   x  int
	 * @return     string
	 */
	string Converter::int_bin_s(int decimal, bool _padding) {
		// Create a temperary string 
		string binary = "";

		// Continue until x is not 0
		while (decimal != 0) {
			binary.insert( 0, int_str(decimal % 2) );
			decimal /= 2;
		}

		// Check if padding is true
		if (_padding) 
			padding(binary);

		// Seperate bits if binary length is greater than 4
		if (binary.length() > 4 && _padding == true)
			separate(binary);

		// Return binary
		return binary;
	}


	/**
	 * This function will convert a binary string
	 * to an integer.
	 * 
	 * @param   binary  string
	 * @return          int
	 */
	int Converter::bin_int_i(string binary) {
		// Check for whitespaces, if there are any remove them
		space_check(binary);

		// Create reverse iterators
		string::reverse_iterator rbegin = binary.rbegin();
		string::reverse_iterator rend = binary.rend();

		// Create temperary int to hold value of the binary
		// and a counter
		int decimal = char_int(*rbegin) * 1;
		int counter = 2;

		// Increment rbegin
		++rbegin;

		// Loop over the string
		while (rbegin != rend) {
			decimal += ( char_int(*rbegin) * counter );
			counter *= 2;
			++rbegin;
		}

		// Return decimal
		return decimal;
	}

}

