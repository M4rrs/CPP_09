#include "PMergeMe.hpp"

/* SCROLL ALL THE WAY DOWN FOR THE MAIN CONSTRUCTOR USED IN THIS PROGRAM */

/*========================== OCF ==========================*/

PMergeMe::PMergeMe( void ) {}

PMergeMe::~PMergeMe( void ) {}

PMergeMe::PMergeMe( const PMergeMe &copy ) {
	*this = copy;
}

PMergeMe &PMergeMe::operator=( const PMergeMe &assign ) {
	
	return (*this);
}

/*=========================================================*/

template < typename T >
T store( std::string arg ) {
	std::istringstream str(arg);
	int temp;
	T cont;

	while (s >> temp) {
		if (temp < 0)
			throw std::logic_error("Occurence of negative values.");
		else
			cont.push_back(temp);
	}
	return (cont);
}

template <typename T>
void checkDup( T cont ) {

	std::T::iterator it1;
	std::T::iterator it2;

	for (it1 = cont.begin(); it1 != cont.end(); it1++) {
		for (it2 = it1; it2 != cont.end(); it2++) {
			if (*it1 == *it2)
				throw std::logic_error("Duplicate values found.");
		}
	}
}

PMergeMe::PMergeMe( std::string arg ) : _before(arg) {

	if (arg.find_first_not_of("0123456789 ") != std::string::npos)
		throw std::logic_error("Occurence of non-digit values.");

	_vec = store< std::vector<int> >(arg);
	_list = store< std::list<int> >(arg);
}