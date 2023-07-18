#include "BitcoinExchange.hpp"

/*============================= CONSTRUCTOR ============================*/

BitcoinExchange::BitcoinExchange( void ) {
	std::cout << "BitcoinExchange constructed." << std::endl;
}

/*============================= DESTRUCTOR ============================*/

BitcoinExchange::~BitcoinExchange( void ) {
	std::cout << "BitcoinExchange destructed." << std::endl;
}

/*============================= COPY CONSTRUCTOR ============================*/

BitcoinExchange::BitcoinExchange( const BitcoinExchange &copy ) {
	*this = copy;
	std::cout << "BitcoinExchange cloned." << std::endl;
}

/*============================= OVERLOADED OPERATOR ============================*/

BitcoinExchange &BitcoinExchange::operator=( const BitcoinExchange &assign ) {
	this->_data.insert(assign._data.begin(), assign._data.end());
	return (*this);
}

/*============================= PUBLIC ============================*/
