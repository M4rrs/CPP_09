#pragma once

#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

class PMergeMe {
	private:
		std::list< int > _list;
		std::vector< int > _vec;

		std::string _before;
		int _range;
		float _timeList;
		float _timeVec;

		PMergeMe( void );

	public:
		PMergeMe( std::string arg );
		PMergeMe( const PMergeMe &copy );
		PMergeMe &operator=( const PMergeMe &assign );
		~PMergeMe( void );
};