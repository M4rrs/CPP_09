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
};