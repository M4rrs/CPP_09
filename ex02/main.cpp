#include "PMergeMe.hpp"

int main( int ac, char **av ) {
	try {
		if (ac == 2) {
			std::string str(av[1]);
			PMergeMe sorting(str);
		}
		else
			std::cerr << "Error: Invalid number of arguments. Minimum 2 arguments." << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	return 0;
}

//1. Parse input, check duplicates, check if positive digits.

// I could make private variables to store range, time elapsed, before string and after string.