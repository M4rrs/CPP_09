#include <sstream>
#include <iostream>

int main( void ) {
	std::string str = "123 3183";

	std::stringstream s(str);
	std::string temp;

	if (str.find_first_not_of("0123456789 ") != std::string::npos) {
		std::cerr << "Doesnt read tab" << std::endl;
		return 1;
	}

	while (s >> temp) {
		std::cout << "this char: " << temp << std::endl;
	}

}