#pragma once

#include <stack>
#include <sstream>
#include <iostream>

#define CYAN "\033[36;1m"
#define RESET "\033[0m"
#define INPUT "0123456789+-*/ "
#define OP "+-*/"

class RPN {
	private:
		std::stack<int> _stack;
		
	public:
		RPN( void );
		RPN( const RPN &copy );
		RPN &operator=( const RPN &assign );
		~RPN( void );

		void calculate(std::string str);
		void do_op( char token );
		void printResults( void ) const;
};
