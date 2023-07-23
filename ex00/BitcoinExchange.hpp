#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>
#include <string>
#include <climits>

#define CYAN "\033[36;1m"
#define RESET "\033[0m"

class BitcoinExchange {
	private:
		std::map< std::string, float> _data;

	public:
		BitcoinExchange( void );
		BitcoinExchange( const BitcoinExchange &copy );
		BitcoinExchange &operator=( const BitcoinExchange &assign );
		~BitcoinExchange( void );

		void save( std::string date, std::string value);
		void calculatePrice( std::string date, float price );
		
};

bool validDate( std::string date );
bool validPrice( std::string price );