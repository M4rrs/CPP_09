#include "PMergeMe.hpp"

/* I followed this guide https://github.com/PunkChameleon/ford-johnson-merge-insertion-sort ^.^ */

/* SCROLL ALL THE WAY DOWN FOR THE MAIN CONSTRUCTOR USED IN THIS PROGRAM */

/*========================== OCF ==========================*/

PMergeMe::PMergeMe( void ) {}

PMergeMe::~PMergeMe( void ) {}

PMergeMe::PMergeMe( const PMergeMe &copy ) {
	*this = copy;
}

PMergeMe &PMergeMe::operator=( const PMergeMe &assign ) {
	if (this != &assign) {
		this->_range = assign._range;
		this->_timeList = assign._timeList;
		this->_timeVec = assign._timeVec;
		this->_odd = assign._odd;
		this->_before = assign._before;
		std::copy(assign._vec.begin(), assign._vec.end(), std::back_inserter(this->_vec));
		std::copy(assign._list.begin(), assign._list.end(), std::back_inserter(this->_list));
	}
	return (*this);
}

/*======================== UTILITIES =========================*/

template <typename T>
void checkDup( T cont ) {

	typename T::iterator it1;
	typename T::iterator it2;

	for (it1 = cont.begin(); it1 != cont.end(); it1++) {
		for (it2 = std::next(it1); it2 != cont.end(); it2++) {
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

void timeStamp( timeval &time ) {
	gettimeofday(&time, NULL);
}

double elapsedTime( timeval &start, timeval &end ) {
	return (((end.tv_sec - start.tv_sec) * TIME + (end.tv_usec - start.tv_usec)) / 1e+6);
}

void PMergeMe::printResults( void ) {

	std::vector<int>::iterator vecIt;
	std::list<int>::iterator listIt;

	std::cout << CYAN << "================================================================================" << CLEAR << std::endl;
	std::cout << "Before:\n" << _before << std::endl;

	std::cout << CYAN << "================================================================================" << CLEAR << std::endl;
	std::cout << "Vector After:\n";
	for (vecIt = _vec.begin(); vecIt != _vec.end(); vecIt++) {
		std::cout << *vecIt;
		if (std::next(vecIt) != _vec.end())
			std::cout << " ";
	}
	std::cout << std::endl;
	std::cout << CYAN << "================================================================================" << CLEAR << std::endl;
	std::cout << "List After:\n";
	for (listIt = _list.begin(); listIt != _list.end(); listIt++) {
		std::cout << *listIt;
		if (std::next(listIt) != _list.end())
			std::cout << " ";
	}
	std::cout << std::endl;

	std::cout << CYAN << "================================================================================" << CLEAR << std::endl;
	std::cout << "Time to process a range of " << _range << " elements with std::vector<int> : "
			<< std::fixed << std::setprecision(5) << GREEN << _timeVec << " us" << CLEAR 
			<< std::endl;

	std::cout << "Time to process a range of " << _range << " elements with std::list<int> : "
			<< std::fixed << std::setprecision(5) << GREEN << _timeList << " us" << CLEAR
			<< std::endl;

	std::cout << CYAN << "================================================================================" << CLEAR << std::endl;
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

// The reason why the list version is different is because lists don't
// support random access like vectors.
void insertion( std::list< std::pair<int, int> > &pairs, int size ) {
	std::list< std::pair<int, int> >::iterator current = pairs.begin();
	std::list< std::pair<int, int> >::iterator sortedEnd = pairs.begin();

	for (int i = 0; i < size; i++) {
		std::pair<int, int> value = *current;
		std::list< std::pair<int, int> >::iterator correctPos = pairs.begin();

		while (correctPos != current && correctPos->second < value.second)
			correctPos++;

		if (correctPos != current) {
			pairs.erase(current);
			pairs.insert(correctPos, value);
			current = sortedEnd;
		}
		sortedEnd = current;
		current++;
	}
}

/*========================= MERGE SORT =============================*/
// Here's where shit gets complicated.

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
		S.insert(S.begin() + (it - S.begin()), pend.at(jacob - 1));
		pend.at(jacob - 1) = -1;
	}

	for (int i = 0; i < pendSize; i++) {
		if (pend.at(i) != -1) {
			std::vector<int>::iterator it = std::lower_bound(S.begin(), S.end(), pend.at(i));
			S.insert(S.begin() + (it - S.begin()), pend.at(i));
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
			}	
			temp.insert(lower, *it);
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

/*=================================== WHERE THE ALGORITHMS ALGORITHMIZE ======================================*/
/* Get ready boys and girls because I'm about to learn you a new thing. The Ford-Johnson Merge Insertion Sort 
* 1. First we catch the odd number. If the container has even elements, we're good to go; but if it's odd
* 	 then we temporarily store it in another variable and pop it from the container.
* 2. Next we store the elements into a container of pairs. The pairs are stored with the smaller value on the 
*	 left, and bigger on the right -> container< std::pair<smaller, bigger> >
* 3. Then comes the insertion part of this method. We sort the container of pairs based on the second pair value.
*	 It kind of looks like this. -> Container[ p1<s1, b1>, p2<s2, b2>, p3<s3, b3> ...] where (b) is the second value.
*	 The element to be sorted (or inserted) is the last pair. Stored as lastEle. Sorting from back to front.
* 4. Then comes Merge. It gets a bit confusing here, especially with the use of the Jacobsthal numbers.
*	 From the sorted pairs that we had earlier (pair<first, second>) we then split them into two separate containers
*	 called 'pend', 'S'; where pend contains pair->first, and S holds pair->second.
*	 Before we enter the harrowing Jacobsthal numbers, we insert the first value of pend to the top of S,
*	 because by logic, the first value of pend will definitely be smaller than all of S.
*	 NOW, we utilise the use of Jacobsthal numbers to telepathically figure out how to insert the other numbers into S.
*	 When calculating Jacobsthal numbers, we start from J(2) because the first numbers are 0 and 1 which we don't need to use.
*	 The jacobNum will tell us the position in S where the value in pend - which we are pointing to - should be placed.
*	 to store the value from pend that we just inserted, and that value in pend is set to -1, to mark as inserted.
*	 The next loop simply inserts the values with lowerbound, because the jacobNum calculated may have been too large.
*	 Don't ask how jacobsthal works, it just does. The idea isn't to be the most efficient, it's to have the least comparisons.
* 5. After this, most of the numbers are sorted. All that's left is to insert that one remaining number we
*	 saved at the beginning. This is just a matter of simply finding the lower bound and inserting it into S.
*	 Then the original container to be sorted is cleared, and the values of the sorted container, 'S' is copied to
* 	 the original.
*/

void PMergeMe::algoVec( void ) {
	int remain;
	std::vector< std::pair<int, int> > pairs;
	std::vector<int> pend;
	std::vector<int> S;

	_range = _vec.size();
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
			S.insert(S.begin() + (it - S.begin()), remain);
	}

	_vec.clear();
	_vec = S;

	if (!std::is_sorted(_vec.begin(), _vec.end()))
		throw std::logic_error("Vector sort failed.");
}

void PMergeMe::algoList( void ) {
	int remain;
	std::list< std::pair<int, int> > pairs;
	std::list<int> pend;
	std::list<int> S;

	_range = _list.size();
	parity();
	if (_odd) {
		remain = _list.back();
		_list.pop_back();
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

	timeval vecStart, listStart, vecEnd, listEnd;

	if (arg.find_first_not_of("0123456789 ") != std::string::npos)
		throw std::logic_error("Occurence of non-digit values.");
	
	timeStamp(vecStart);
	_vec = store< std::vector<int> >(arg);
	if (std::is_sorted(_vec.begin(), _vec.end()))
		throw std::logic_error("Sequence already sorted.");
	checkDup(_vec);
	algoVec();
	timeStamp(vecEnd);
	_timeVec = elapsedTime(vecStart, vecEnd);

	timeStamp(listStart);
	_list = store< std::list<int> >(arg);
	checkDup(_list);
	algoList();
	timeStamp(listEnd);
	_timeList = elapsedTime(listStart, listEnd);

	printResults();
}
