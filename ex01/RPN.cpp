#include "RPN.hpp"

RPN::RPN( void ) {}

RPN::~RPN( void ) {}

RPN::RPN( const RPN &copy ) {
	*this = copy;
}

RPN &RPN::operator=( const RPN &assign ) {
	if (this != &assign) {
		_stack = assign._stack;
	}
	return (*this);
}

/*======================================================================*/

void RPN::calculate( std::string str ) {

	if (str.find_first_not_of(INPUT) != std::string::npos)
		throw std::logic_error("Invalid values in input.");

	std::stringstream input(str);
	std::string token;

	while (input >> token) {
		if (token.find_first_of(OP) != std::string::npos)
			this->do_op(token[0]);
		else
			this->_stack.push(std::stoi(token));
	}
	this->printResults();
}

void RPN::do_op( char token ) {
	if (this->_stack.size() < 2)
		throw std::logic_error("Insufficient values in stack.");

	int num2 = this->_stack.top();
	this->_stack.pop();
	int num1 = this->_stack.top();
	this->_stack.pop();
	
	if (token == '+')
		this->_stack.push(num1 + num2);
	else if (token == '-')
		this->_stack.push(num1 - num2);
	else if (token == '*')
		this->_stack.push(num1 * num2);
	else if (token == '/') {
		if (num2 == 0)
			throw std::logic_error("Division by zero.");
		else
			this->_stack.push(num1 / num2);
	}
}

void RPN::printResults( void ) const {
	if (this->_stack.size() != 1)
		throw std::logic_error("Operation error. Stack containing more than 1 element.");
	
	std::cout << this->_stack.top() << std::endl;
}