/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Abstrack.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 15:04:12 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/07 13:17:05 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Abstrack.hpp"
#include <list>
#include "Lexer.hpp"
#include <iostream>
#include "IOperand.hpp"
#include <regex>
#include <iterator>
#include "Factory.hpp"
#include <exception>
#include <sstream>
#include "Operand.hpp"
#include <cctype>

Abstrack::stack_error::stack_error(const char * msg)
	: std::length_error(msg)
{
}

Abstrack::stack_error::~stack_error(void) throw()
{
}

Abstrack::assert_error::assert_error(const char * msg)
	: std::logic_error(msg)
{
}

Abstrack::assert_error::~assert_error(void) throw()
{
}

Abstrack::not_printable::not_printable(const char * msg)
	: std::invalid_argument(msg)
{
}

Abstrack::not_printable::~not_printable(void) throw()
{
}

Abstrack::~Abstrack(void)
{
	for (auto e : this->_stack)
		delete e;
	delete & this->_factory;
}

Abstrack::Abstrack(std::list<struct Token> list)
	: _factory( Factory::get() )
{
	for (auto it = list.begin(); it != list.end(); it ++)
	{
		try {
			if (it->value == "exit")
				return ;
			if(it->type == TokenType::ACTION)
				(this->*_actionMap[it->value])();
			else if (it->type == TokenType::INSTR)
				(this->*_instrMap[it->value])( * ++it);
		}
		catch (Abstrack::not_printable const & e)
		{
			std::cout << "Line " << it->raw << ": "<< RED << "not_printable Exception: " << RESET << e.what() << std::endl;
			_clear();
			std::exit(1);
		}
		catch (Abstrack::assert_error const & e)
		{
			std::cout << "Line " << it->raw << ": "<< RED << "assert Exception: " << RESET << e.what() << std::endl;
			_clear();
			std::exit(1);
		}
		catch (Abstrack::stack_error const & e)
		{
			std::cout << "Line " << it->raw << ": "<< RED << "stack Exception: " << RESET << e.what() << std::endl;
			_clear();
			std::exit(1);
		}
		catch (std::overflow_error const & e)
		{
			std::cout << "Line " << it->raw << ": "<< RED << "overflow Exception: " << RESET << e.what() << std::endl;
			_clear();
			std::exit(1);
		}
		catch (std::underflow_error const & e)
		{
			std::cout << "Line " << it->raw << ": " << RED << "underflow Exception: " << RESET << e.what() << std::endl;
			_clear();
			std::exit(1);
		}
		catch (std::runtime_error const & e)
		{
			std::cout << "Line " << it->raw << ": " << RED << "runtime Exception: " << RESET << e.what() << std::endl;
			_clear();
			std::exit(1);
		}
		catch (std::exception const & e)
		{
			std::cout << "Line " << it->raw << ": " << RED << "std::Exception: " << RESET << e.what() << std::endl;
			_clear();
			std::exit(1);
		}
	}
	std::cout << RED << "Error: " << RESET << "exit instruction is missing" << std::endl;
	_clear();
	std::exit(1);
}

void	Abstrack::_print(void)
{
	if (this->_stack.size() == 0)
		throw (Abstrack::stack_error("stack empty"));
	IOperand const * ope = this->_stack.front();
	if (ope->getType() != eOperandType::Int8)
		throw (Abstrack::not_printable("operand with type int8 required"));
	std::stringstream s(ope->toString().c_str());
	double c;
	s >> c;
	char e = static_cast<char>(c);
	if (std::isprint(e))
		std::cout << e << std::endl;
}

void	Abstrack::_dump(void)
{
	for (auto e : this->_stack)
	{
		std::string tmp = e->toString();
		std::cout << tmp << std::endl;
	}
}

void	Abstrack::_pop(void)
{
	if (this->_stack.size() == 0)
		throw (Abstrack::stack_error("stack empty"));
	delete this->_stack.front();
	this->_stack.pop_front();
}

void	Abstrack::_clear(void)
{
	for (auto e : this->_stack)
		delete e;
	delete & this->_factory;
}

void	Abstrack::_mod(void)
{
	if (this->_stack.size() < 2)
		throw (Abstrack::stack_error("stack too small"));
	IOperand const *v1 = this->_stack.front();
	this->_stack.pop_front();
	IOperand const *v2 = this->_stack.front();
	this->_stack.pop_front();

	try {
		this->_stack.push_front( *v2 % *v1 );
	}
	catch (std::overflow_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::underflow_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::runtime_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::exception const & e) {
		delete v1;
		delete v2;
		throw e;
	}
	delete v1;
	delete v2;
}
void	Abstrack::_div(void)
{
	if (this->_stack.size() < 2)
		throw (Abstrack::stack_error("stack too small"));
	IOperand const *v1 = this->_stack.front();
	this->_stack.pop_front();
	IOperand const *v2 = this->_stack.front();
	this->_stack.pop_front();
	try {
		this->_stack.push_front( *v2 / *v1 );
	}
	catch (std::overflow_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::underflow_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::runtime_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::exception const & e) {
		delete v1;
		delete v2;
		throw e;
	}
	delete v1;
	delete v2;
}

void	Abstrack::_sub(void)
{
	if (this->_stack.size() < 2)
		throw (Abstrack::stack_error("stack too small"));
	IOperand const *v1 = this->_stack.front();
	this->_stack.pop_front();
	IOperand const *v2 = this->_stack.front();
	this->_stack.pop_front();
	try {
		this->_stack.push_front( *v2 - *v1 );
	}
	catch (std::overflow_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::underflow_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::runtime_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::exception const & e) {
		delete v1;
		delete v2;
		throw e;
	}
	delete v1;
	delete v2;
}

void	Abstrack::_mul(void)
{
	if (this->_stack.size() < 2)
		throw (Abstrack::stack_error("stack too small"));
	IOperand const *v1 = this->_stack.front();
	this->_stack.pop_front();
	IOperand const *v2 = this->_stack.front();
	this->_stack.pop_front();
	try {
		this->_stack.push_front( *v2 * *v1 );
	}
	catch (std::overflow_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::underflow_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::runtime_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::exception const & e) {
		delete v1;
		delete v2;
		throw e;
	}
	delete v1;
	delete v2;
}

void	Abstrack::_add(void)
{
	if (this->_stack.size() < 2)
		throw (Abstrack::stack_error("stack too small"));
	IOperand const *v1 = this->_stack.front();
	this->_stack.pop_front();
	IOperand const *v2 = this->_stack.front();
	this->_stack.pop_front();
	try {
		this->_stack.push_front( *v2 + *v1 );
	}
	catch (std::overflow_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::underflow_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::runtime_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::exception const & e) {
		delete v1;
		delete v2;
		throw e;
	}
	delete v1;
	delete v2;
}

void	Abstrack::_or(void)
{
	if (this->_stack.size() < 2)
		throw (Abstrack::stack_error("stack too small"));
	IOperand const *v1 = this->_stack.front();
	this->_stack.pop_front();
	IOperand const *v2 = this->_stack.front();
	this->_stack.pop_front();
	if (v1->getPrecision() > eOperandType::Int32 || v2->getPrecision() > eOperandType::Int32)
	{
		delete v1;
		delete v2;
		throw (std::runtime_error("invalid type of operand to bitwise operation"));
	}
	try {
		this->_stack.push_front( *v2 | *v1 );
	}
	catch (std::overflow_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::underflow_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::runtime_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::exception const & e) {
		delete v1;
		delete v2;
		throw e;
	}
	delete v1;
	delete v2;
}

void	Abstrack::_and(void)
{
	if (this->_stack.size() < 2)
		throw (Abstrack::stack_error("stack too small"));
	IOperand const *v1 = this->_stack.front();
	this->_stack.pop_front();
	IOperand const *v2 = this->_stack.front();
	this->_stack.pop_front();
	if (v1->getPrecision() > eOperandType::Int32 || v2->getPrecision() > eOperandType::Int32)
	{
		delete v1;
		delete v2;
		throw (std::runtime_error("invalid type of operand to bitwise operation"));
	}
	try {
		this->_stack.push_front( *v2 & *v1 );
	}
	catch (std::overflow_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::underflow_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::runtime_error const & e)
	{
		delete v1;
		delete v2;
		throw e;
	}
	catch (std::exception const & e) {
		delete v1;
		delete v2;
		throw e;
	}
	delete v1;
	delete v2;
}

void	Abstrack::_assert(struct Token const & token)
{
	if ( this->_stack.empty() )
		throw (Abstrack::stack_error("stack empty"));
	IOperand const * ope = this->_getOpe(token.value);
	if ( ope != nullptr )
	{
		if (ope->getType() != this->_stack.front()->getType() ||
				ope->toString() != this->_stack.front()->toString())
		{
			delete ope;
			throw (Abstrack::assert_error("assertion failed"));
		}
		delete ope;
	}
}



void	Abstrack::_push(struct Token const & token)
{
	IOperand const * ope = this->_getOpe(token.value);
	if (ope != nullptr)
		this->_stack.push_front( ope );
}

IOperand const * Abstrack::_getOpe(std::string const & str) const
{
	std::cmatch match;
	for (auto e : this->_patternMap)
	{
		const std::string s = str;
		std::regex rgx( e.first );
		std::smatch match;

		if (std::regex_search(s.begin(), s.end(), match, rgx))
			return this->_factory.createOperand(e.second, match[1]);
	}
	return nullptr;
}

std::list<IOperand const *>	Abstrack::getStack(void) const
{
	return this->_stack;
}

std::map<std::string, ACTIONFCT> Abstrack::_actionMap =
{
	{"add", &Abstrack::_add},
	{"and", &Abstrack::_and},
	{"or", &Abstrack::_or},
	{"sub", &Abstrack::_sub},
	{"mul", &Abstrack::_mul},
	{"div", &Abstrack::_div},
	{"mod", &Abstrack::_mod},
	{"print", &Abstrack::_print},
	{"dump", &Abstrack::_dump},
	{"pop", &Abstrack::_pop}
};

std::map<std::string, INSTRFCT> Abstrack::_instrMap =
{
	{"push", &Abstrack::_push},
	{"assert", &Abstrack::_assert}
};

std::map<std::string, eOperandType> Abstrack::_patternMap =
{
	{ "int8\\(([-]?\\d+)\\)", eOperandType::Int8 },
	{ "int16\\(([-]?\\d+)\\)", eOperandType::Int16 },
	{ "int32\\(([-]?\\d+)\\)", eOperandType::Int32 },
	{ "float\\(([-]?\\d+\\.\\d+)\\)", eOperandType::Float },
	{ "double\\(([-]?\\d+\\.\\d+)\\)", eOperandType::Double },
};
