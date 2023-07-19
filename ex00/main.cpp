#include "BitcoinExchange.hpp"

static int getData( BitcoinExchange &btc ) {
	std::fstream file;
	std::string line;

	std::string date;
	std::string value;

	file.open("data.csv", std::fstream::in);
	if (!file.is_open()) {
		std::cerr << "Error: File could not be opened." << std::endl;
		return 1;
	}
	std::getline(file, line);
	while (std::getline(file, line)) {
		date = line.substr(0, 10);
		try {
			value = line.substr(line.find(",") + 1);
		}
		catch ( std::out_of_range &e ) {
			std::cerr << "No value found." << std::endl;
			continue;
		}
		if (validDate(date) || validPrice(value))
			btc.save(date, value);
	}
	file.close();
	return 0;
}

static int parseData( BitcoinExchange &btc, char *filename ) {
	
}

int main( int ac, char **av ) {

	BitcoinExchange btc;

	if (ac != 2) {
		std::cerr << "Invalid format. Usage: ./btc <filename>" << std::endl;
		return 1;
	}
	if (getData(btc) || parseData(btc, av[1]))
		return 1;

	return 0;
}