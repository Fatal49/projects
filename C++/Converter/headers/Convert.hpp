#ifndef _CONVERTER_HPP_
#define _CONVERTER_HPP_

#include <iostream>
#include <string>

/**
 * Convert namspace
 */
namespace convert {

	/**
	 * Converter Class
	 */
	 class Converter {
	 public:

	 	// Constructor
	 	Converter();

	 	// Methods
	 	std::string int_str(int x) const;
	 	int         str_int(const std::string& str) const;
	 	int         char_int(char x) const;

	 	std::string char_dec_s(const char& c) const;
	 	int         char_dec_i(const char& c) const;
	 	std::string str_dec_s(const std::string& str) const; 
	 	int         str_dec_i(const std::string& str) const;

	 	std::string char_hex_s(const char& c) const;
	 	std::string str_hex_s(const std::string& str) const;

	 	std::string int_bin_s(int decimal, bool _padding = false);
	 	int         bin_int_i(std::string binary);

	 private:
	 	std::string  hex(int x) const;
	 	void         padding(std::string& str);
	 	void         separate(std::string& str);
	 	void         space_check(std::string& str);
	 };

}


#endif /* _CONVERTER_HPP_ defined */