#include "PMergeMe.hpp"

/* SCROLL ALL THE WAY DOWN FOR THE MAIN CONSTRUCTOR USED IN THIS PROGRAM */

/*========================== OCF ==========================*/

PMergeMe::PMergeMe( void ) {}

PMergeMe::~PMergeMe( void ) {}

// PMergeMe::PMergeMe( const PMergeMe &copy ) {
// 	*this = copy;
// }

// PMergeMe &PMergeMe::operator=( const PMergeMe &assign ) {
	
// 	return (*this);
// }

/*======================== UTILITIES =========================*/

template <typename T>
void checkDup( T cont ) {

	typename T::iterator it1;
	typename T::iterator it2;

	for (it1 = cont.begin(); it1 != cont.end(); it1++) {
		for (it2 = it1; it2 != cont.end(); it2++) {
			if (*it1 == *it2)
				throw std::logic_error("Duplicate values found.");
		}
	}
}

// Simple sets to odd or even.
void PMergeMe::parity( void ) {
	if ((_vec.size() % 2) == 1 || (_list.size() % 2) == 1)
		_odd = true;
	else
		_odd = false;
}

float timeStamp( void ) {
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_usec + time.tv_sec * 1000000);
}

float elapsedTime( float start ) {
	return (timeStamp() - start / 1000000.0);
}

void PMergeMe::printResults( void ) {

	std::vector<int>::iterator vecIt;
	std::list<int>::iterator listIt;

	std::cout << "Before: " << _before << std::endl;

	std::cout << "Vector After: ";
	int count = 0;
	for (vecIt = _vec.begin(); vecIt != _vec.end(); vecIt++) {
		if (count < 6) {
			std::cout << *vecIt;
			if (std::next(vecIt) != _vec.end())
				std::cout << " ";
		}
		else
			break;
		count++;
	}
	if (count == 6 && vecIt != _vec.end())
		std::cout << "[...]";
	std::cout << std::endl;

	std::cout << "List After: ";
	count = 0;
	for (listIt = _list.begin(); listIt != _list.end(); listIt++) {
		if (count < 6) {
			std::cout << *listIt;
			if (std::next(listIt) != _list.end())
				std::cout << " ";
		}
		else
			break;
		count++;
	}
	if (count == 6 && listIt != _list.end())
		std::cout << "[...]";
	std::cout << std::endl;

	std::cout << "Time to process a range of " << _range << " elements with std::vector<int> : "
			<< _timeVec << "us." << std::endl;

	std::cout << "Time to process a range of " << _range << " elements with std::list<int> : "
			<< _timeList << "us." << std::endl;
}

/*=============================== STORING ==================================*/
template < typename T >
T store( std::string arg ) {
	std::istringstream str(arg);
	int temp;
	T cont;

	while (str >> temp) {
		if (temp < 0)
			throw std::logic_error("Occurence of negative values.");
		else
			cont.push_back(temp);
	}
	return (cont);
}

template < typename Pair, typename C >
Pair storePairs( C cont ) {
	
	typename C::iterator it;
	int num1, num2;
	Pair resultCont;

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

/*========================= INSERTION SORT =============================*/

void insertion( std::vector< std::pair<int, int> > &pairs, int size ) {
	if (size == 1)
		return ;

	insertion(pairs, size - 1);

	std::pair<int, int> lastEle = pairs[size - 1];
	int i = size - 2;

	while (i >= 0 && pairs[i].second > lastEle.second) {
		pairs[i + 1] = pairs[i];
		i--;
	}

	pairs[i + 1] = lastEle;
}

/* Okay hear me out I know this looks confusing.*/
void insertion( std::list< std::pair<int, int> > &pairs, int size ) {
	std::list< std::pair<int, int> >::iterator left = pairs.begin();
	left++;

	(void)size;
	for (; left != pairs.end(); left++) {
		std::pair<int, int> lastEle = *left;
		std::list< std::pair<int, int> >::iterator right = left;

		while (right != pairs.begin() && std::prev(right)->second > lastEle.second)
			--right;

		pairs.insert(std::next(right), lastEle);
		pairs.erase(left);
	}
}

/*========================= MERGE SORT =============================*/
// Here's where shit gets complicated.

//Listen, the FJMI uses jacobsthal numbers for merging, why? Idk.
//Don't ask about the recursion, just know that that's how it is.
static int jacobsthal( int i ) {
	if (i == 0)
		return 0;
	if (i == 1)
		return 1;

	return (jacobsthal(i - 1) + 2 * jacobsthal(i - 2));
}

void mergeSort( std::vector<int> &pend, std::vector<int> &S ) {
	std::vector<int> temp;
	int pendSize = pend.size();

	for (int i = 2; i < pendSize; i++) {
		int jacob = jacobsthal(i);

		if (jacob > pendSize)
			break;
		temp.push_back(pend.at(jacob - 1));
		std::vector<int>::iterator it = std::lower_bound(S.begin(), S.end(), pend.at(jacob - 1));
		S.insert(S.begin(), (it - S.begin()), pend.at(jacob - 1));
		pend.at(jacob - 1) = -1;
	}

	for (int i = 0; i < pendSize; i++) {
		if (i != -1) {
			std::vector<int>::iterator it = std::lower_bound(S.begin(), S.end(), pend.at(i));
			S.insert(S.begin(), (it - S.begin()), pend.at(i));
			temp.push_back(pend.at(i));
		}
	}
}

void mergeSort( std::list<int> &pend, std::list<int> &S ) {
	std::list<int> temp;
	int pendSize = pend.size();
	
	for (int i = 2; i < pendSize; i++) {
		int jacob = jacobsthal(i);

		if (jacob > pendSize)
			break;
		std::list<int>::iterator jacobPos = pend.begin();
		std::advance(jacobPos, jacob - 1);
		temp.push_back(*jacobPos);

		std::list<int>::iterator lower;
		for (lower = S.begin(); lower != S.end(); lower++) {
			if (*lower > *jacobPos)
				break;
		}
		temp.insert(lower, *jacobPos);
		*jacobPos = -1;
	}

	std::list<int>::iterator it;
	for (it = pend.begin(); it != pend.end(); it++) {
		if (*it != -1) {
			temp.push_back(*it);
			std::list<int>::iterator lower;
			for (lower = S.begin(); lower != S.end(); lower++) {
				if (*lower > *it)
					break;
				temp.insert(lower, *it);
			}	
		}
	}
	pend.clear();
	pend = temp;
}

template < typename Pair, typename Cont >
void merge( Pair &pairs, Cont &pend, Cont &S ) {

	for (typename Pair::iterator it = pairs.begin(); it != pairs.end(); it++) {
		pend.push_back(it->first);
		S.push_back(it->second);
	}

	S.insert(S.begin(), pend.front());
	if (!pend.empty())
		pend.erase(pend.begin());

	mergeSort(pend, S);
}

/*==================================================================*/

void PMergeMe::algoVec( void ) {
	int remain;
	std::vector< std::pair<int, int> > pairs;
	std::vector<int> pend;
	std::vector<int> S;

	parity();
	if (_odd) {
		remain = _vec.back();
		_vec.pop_back();
	}

	pairs = storePairs< std::vector< std::pair<int, int> >, std::vector<int> >(_vec);
	insertion(pairs, pairs.size());
	merge< std::vector< std::pair<int, int> >, std::vector<int> >(pairs, pend, S);

	if (_odd) {
		std::vector<int>::iterator it = std::lower_bound(S.begin(), S.end(), remain);
		if (it == S.end())
			S.push_back(remain);
		else
			S.insert(S.begin(), (it - S.begin()), remain);
	}

	_vec.clear();
	_vec = S;

	std::vector<int>::iterator it;
	for (it = _vec.begin(); it != _vec.end(); it++)
		std::cout << *it << std::endl;
	if (!std::is_sorted(_vec.begin(), _vec.end()))
		throw std::logic_error("Vector sort failed.");
}

void PMergeMe::algoList( void ) {
	int remain;
	std::list< std::pair<int, int> > pairs;
	std::list<int> pend;
	std::list<int> S;

	parity();
	if (_odd) {
		remain = _vec.back();
		_vec.pop_back();
	}

	pairs = storePairs< std::list< std::pair<int, int> >, std::list<int> >(_list);
	insertion(pairs, pairs.size());
	merge< std::list< std::pair<int, int> >, std::list<int> >(pairs, pend, S);

	if (_odd) {
		std::list<int>::iterator it = std::lower_bound(S.begin(), S.end(), remain);
		if (it == S.end())
			S.push_back(remain);
		else
			S.insert(it, remain);
	}

	_list.clear();
	_list = S;

	if (!std::is_sorted(_list.begin(), _list.end()))
		throw std::logic_error("List sort failed.");
}

/*===================== START OF PMERGEME =======================*/

PMergeMe::PMergeMe( std::string arg ) : _before(arg) {


	if (arg.find_first_not_of("0123456789 ") != std::string::npos)
		throw std::logic_error("Occurence of non-digit values.");
	
	float start = timeStamp();
	_vec = store< std::vector<int> >(arg);
	// std::vector<int>::iterator it;
	// for (it = _vec.begin(); it != _vec.end(); it++)
	// 	std::cout << *it << std::endl;
	algoVec();
	_timeVec = elapsedTime(start);

	start = timeStamp();
	_list = store< std::list<int> >(arg);
	// for (it = _list.begin(); it != _list.end(); it++)
	// 	std::cout << *it << std::endl;
	algoList();
	_timeList = elapsedTime(start);

	printResults();
}

// std::cout << "\033[36;1mProblem here?\033[0m" << std::endl;
