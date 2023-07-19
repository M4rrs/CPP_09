#pragma

#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>

class BitcoinExchange {
	private:
		std::map< std::string, float> _data;

	public:
		BitcoinExchange( void );
		BitcoinExchange( const BitcoinExchange &copy );
		BitcoinExchange &operator=( const BitcoinExchange &assign );
		~BitcoinExchange( void );

		void save( std::string date, std::string value);
		// void pop( std::string const date );
		
};

bool validDate( std::string date );
bool validPrice( std::string price );