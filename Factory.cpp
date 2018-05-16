/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 12:02:28 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/05 19:56:21 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"
#include <iostream>
#include <exception>
#include <sstream>
#include <limits>
#include <exception>
#include "Operand.hpp"

Factory::Factory(void) {}

Factory::~Factory(void)
{
	Factory::_singleton = nullptr;
}

Factory & Factory::get(void)
{
	if (! Factory::_singleton)
		Factory::_singleton = new Factory;
	return * Factory::_singleton;
}

IOperand const * Factory::createOperand( eOperandType type, std::string const & value )
{
	return (this->*_arrayFunction[type])(value);
}

IOperand const * Factory::createInt8 ( std::string const & value )
{
	std::stringstream s(value);
	double a ;
	s >> a;
	if (s.fail())
		throw (std::runtime_error("stream conversion failed"));
	if (a < std::numeric_limits<char>::min())
		throw (std::underflow_error("failed to create Int 8"));
	if (a > std::numeric_limits<char>::max())
		throw (std::overflow_error("failed to create Int 8"));
	char c = static_cast<char>(a);
	return new Operand<char>(c, eOperandType::Int8);
}

IOperand const * Factory::createInt16 ( std::string const & value )
{
	std::stringstream s(value);
	double a ;
	s >> a;
	if (s.fail())
		throw (std::runtime_error("stream conversion failed"));
	if (a < std::numeric_limits<short>::min())
		throw (std::underflow_error("failed to create Int 16"));
	if (a > std::numeric_limits<short>::max())
		throw (std::overflow_error("failed to create Int 16"));
	short c = static_cast<short>(a);
	return new Operand<short>(c, eOperandType::Int16);
}

IOperand const * Factory::createInt32 ( std::string const & value )
{
	std::stringstream s(value);
	double a ;
	s >> a;
	if (s.fail())
		throw (std::runtime_error("stream conversion failed"));
	if (a < std::numeric_limits<int>::min())
		throw (std::underflow_error("failed to create Int 32"));
	if (a > std::numeric_limits<int>::max())
		throw (std::overflow_error("failed to create Int 32"));
	int c = static_cast<int>(a);
	return new Operand<int>(c, eOperandType::Int32);
}

IOperand const * Factory::createFloat ( std::string const & value )
{
	std::stringstream s(value);
	double a ;
	s >> a;
	if (s.fail())
		throw (std::runtime_error("stream conversion failed"));
	if (a < std::numeric_limits<float>::min())
		throw (std::underflow_error("failed to create Float"));
	if (a > std::numeric_limits<float>::max())
		throw (std::overflow_error("failed to create Float"));
	float c = static_cast<float>(a);
	return new Operand<float>(c, eOperandType::Float);
}

IOperand const * Factory::createDouble ( std::string const & value )
{
	std::stringstream s(value);
	double a ;
	s >> a;
	if (s.fail())
		throw (std::runtime_error("stream conversion failed"));
	if (a < std::numeric_limits<double>::min())
		throw (std::underflow_error("failed to create Double"));
	if (a > std::numeric_limits<double>::max())
		throw (std::overflow_error("failed to create Double"));
	return new Operand<double>(a, eOperandType::Double);
}

Factory * Factory::_singleton = nullptr;

IOperand const *(Factory::*(Factory::_arrayFunction[5]))(std::string const &) =
{
	&Factory::createInt8,
	&Factory::createInt16,
	&Factory::createInt32,
	&Factory::createFloat,
	&Factory::createDouble
};
