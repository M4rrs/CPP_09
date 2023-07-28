#include "PMergeMe.hpp"

int main( int ac, char **av ) {
	try {
		if (ac == 2) {
			std::string str(av[1]);
			PMergeMe sorting(str);
		}
		else
			std::cerr << "Error: Invalid number of arguments. Usage: ./PmergeMe <integer string>" << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	return 0;
}