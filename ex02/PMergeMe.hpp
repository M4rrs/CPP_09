#pragma once

#include <list>
#include <vector>
#include <iostream>
#include <algorithm>

class PMergeMe {
	private:
		std::list< int > _list;
		std::vector< int > _vec;

	public:
		PMergeMe( void );
		PMergeMe( const PMergeMe &copy );
		PMergeMe &operator=( const PMergeMe &assign );
		~PMergeMe( void );
};