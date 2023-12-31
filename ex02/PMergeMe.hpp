#pragma once

#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <sys/time.h>
#include <iomanip>

#define CYAN "\033[36;1m"
#define GREEN "\033[32m"
#define CLEAR "\033[0m"
#define TIME 1000000.0

class PMergeMe {
	private:
		std::list< int > _list;
		std::vector< int > _vec;

		std::string _before;
		int _range;
		double _timeList;
		double _timeVec;
		bool _odd;
		PMergeMe( void );

	public:
		PMergeMe( std::string arg );
		PMergeMe( const PMergeMe &copy );
		PMergeMe &operator=( const PMergeMe &assign );
		~PMergeMe( void );

		void parity( void );
		void printResults( void );
		void algoVec( void );
		void algoList( void );
};