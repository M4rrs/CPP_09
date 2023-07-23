#include "RPN.hpp"

int main( int ac, char **av ) {
	if (ac != 2) {
		std::cerr << "Incorrect input. Usage: ./RPN <string>" << std::endl;
		return 1;
	}

	RPN rpn;
	try {
		rpn.calculate(av[1]);
	}
	catch ( std::exception &e ) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}