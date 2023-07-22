#include "BitcoinExchange.hpp"

/*============================= CONSTRUCTOR ============================*/

BitcoinExchange::BitcoinExchange( void ) {
	std::cout << CYAN <<  "BitcoinExchange constructed." << RESET << std::endl;
}

/*============================= DESTRUCTOR ============================*/

BitcoinExchange::~BitcoinExchange( void ) {
	std::cout << CYAN << "BitcoinExchange destructed." << RESET << std::endl;
}

/*============================= COPY CONSTRUCTOR ============================*/

BitcoinExchange::BitcoinExchange( const BitcoinExchange &copy ) {
	*this = copy;
	std::cout << CYAN << "BitcoinExchange cloned." << RESET << std::endl;
}

/*============================= OVERLOADED OPERATOR ============================*/

BitcoinExchange &BitcoinExchange::operator=( const BitcoinExchange &assign ) {
	this->_data.insert(assign._data.begin(), assign._data.end());
	return (*this);
}

/*============================= PUBLIC ============================*/

void	BitcoinExchange::save( std::string date, std::string price ) {
	this->_data.insert(std::pair< std::string, float >(date, std::stof(price)));
}

void BitcoinExchange::calculatePrice( std::string date, float price ) {

	std::map<std::string, float>::iterator btcDate;

	btcDate = this->_data.upper_bound(date);
	if (btcDate != this->_data.begin())
		--btcDate;
	std::cout << date << " => " << price << " = "
			<< (btcDate->second * price) << std::endl;
}

/*=================================================================*/

bool validDate( std::string date ) {
	if (date.length() != 10) {
		std::cerr << "Error: Invalid date format." << std::endl;
		return false;
	}

	int year = std::stoi(date.substr(0, 4));
	int month = std::stoi(date.substr(5, 2));
	int day = std::stoi(date.substr(8, 2));
	
	if (year < 2009 || year > 2022 || month < 1 || month > 12 || day < 1 || day > 31) {
		std::cerr << "Error: Invalid date range" 
				<< " => " << year << "-" << month << "-" << day
				<< std::endl;
		return false;
	}
	return true;
}

bool validPrice( std::string price ) {
	float value;

	if (price.find_first_not_of("0123456789.") != std::string::npos) {
		std::cerr << "Error: Invalid price value." << std::endl;
		return false;
	}

	try {
		value = std::stof(price);
	}
	catch (std::out_of_range &e) {
		std::cerr << "Error: Price value out of range." << std::endl;
		return false;
	}
	catch (std::invalid_argument &e) {
		std::cerr << "Error: Invalid price value." << std::endl;
		return false;
	}
	
	if (value < 0 || value >= INT_MAX) {
		std::cerr << "Error: Price value out of range." << std::endl;
		return false;
	}

	return true;
}