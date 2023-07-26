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

/*======================== CHECKS AND VALIDATION =========================*/

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

void PMergeMe::parity( void ) {
	if ((_vec.size() % 2) && (_list.size() % 2))
		_odd = true;
	else
		_odd = false;
}

/*========================================================================*/
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

template < typename Pair, typename C >
Pair storePairs( C cont ) {
	
	std::T::iterator it;
	int num1, num2;
	V resultCont;

	for (it = cont.begin(); it != cont.end(); it++) {
		std::pair<int, int> pair;

		num1 = *it;
		it++;
		num2 = *it;
		if (num1 > num2) {
			pair.first = num2;
			pair.second = num1;
		}
		else {
			pair.first = num1;
			pair.second = num2;			
		}
		
		resultCont.push_back(pair);
	}
	
	return (resultCont);
}

void PMergeMe::algoVec( void ) {
	int remain;
	std::vector< std::pair<int, int> > pairs;

	if (_odd) {
		remain = _vec.back();
		_vec.pop_back();
	}

	pairs = storePairs< std::vector< std::pair<int, int> >, std::vector<int> >(_vec);
}

void PMergeMe::algoList( void ) {
	int remain;

	if (_odd) {
		remain = _vec.back();
		_vec.pop_back();
	}
}
/*===================== START OF PMERGEME =======================*/

PMergeMe::PMergeMe( std::string arg ) : _before(arg) {

	if (arg.find_first_not_of("0123456789 ") != std::string::npos)
		throw std::logic_error("Occurence of non-digit values.");

	_vec = store< std::vector<int> >(arg);
	_list = store< std::list<int> >(arg);
	parity(); //just sets bool to odd or even

	algoVec();
	algoList();
}