#include "PMergeMe.hpp"

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
	std::stringstream str(arg);
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

PMergeMe::PMergeMe( std::string arg ) : _before(arg) {
	if (arg.find_first_not_of("0123456789 ") != std::string::npos)
		throw std::logic_error("Occurence of non-digit values.");

	_vec = store< std::vector<int> >(arg);
	_list = store< std::list<int> >(arg);
}