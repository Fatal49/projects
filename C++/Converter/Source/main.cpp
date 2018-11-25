#include "../headers/Convert.hpp"

using namespace std;
using namespace convert;

int main() {

	Converter myConv;

	cout << "Given: h\n";
	cout << "Converted to -> string -> " << myConv.char_dec_s('h') << endl;
	cout << "Converted to -> int    -> " << myConv.char_dec_i('h') << endl;

	cout << endl;
	cout << "Given: has\n";
	cout << "Converted to -> string -> " << myConv.str_dec_s("has") << endl;
	cout << "Converted to -> int    -> " << myConv.str_dec_i("has") << endl;

	cout << endl;
	cout << "Given: 456\n";
	cout << "Converted to -> string -> " << myConv.str_int("458") << endl;

	cout << endl;
	cout << "Given: n\n";
	cout << "Converted to -> hex -> string -> " << myConv.char_hex_s('n') << endl;

	cout << endl;
	cout << "Given: Note\n";
	cout << "Converted to -> hex -> string -> " << myConv.str_hex_s("Note") << endl;

	cout << endl;
	cout << "Given: 67\n";
	cout << "Converted to -> binary -> string -> " << myConv.int_bin_s(67, 1) << endl;

	cout << endl;
	cout << "Given: 0011 0101 0110\n";
	cout << "Converted to -> decimal -> int -> " << myConv.bin_int_i("0011 0101 0110") << endl;

	return 0;
}
