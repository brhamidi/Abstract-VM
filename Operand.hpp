/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 17:17:40 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/07 13:14:17 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
# define OPERAND_HPP

# include "IOperand.hpp"
# include <cmath>
# include <sstream>
# include <iostream>
# include "Factory.hpp"
# include <string>
# include <exception>

template <typename T>
class Operand : public IOperand
{
	private:
		Operand<T>(void) {}
		Operand<T>(Operand<T> const & o) { *this = o; }
		Operand<T> & operator=(Operand<T> const & ) {}

		T			const	_value;
		std::string const * _str;
		eOperandType		_type;
	public:
		Operand<T>( T value, eOperandType type):
			_value(value) , _str(new std::string (std::to_string (value) )), _type(type) {}
		~Operand<T>(void) { delete _str; }

		virtual int getPrecision( void ) const { return this->_type; }
		virtual eOperandType getType( void ) const { return this->_type; }

		virtual std::string const & toString( void ) const { return * this->_str; }

		IOperand const * operator&(IOperand const & rhs) const
		{
			eOperandType	precision;

			precision = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
			std::string sv1 = rhs.toString();
			std::string sv2 = this->toString();
			std::stringstream s(sv1);
			int v1 ;
			int v2 ;
			s >> v1;
			s = std::stringstream(sv2);
			s >> v2;
			return Factory::get().createOperand(precision, std::to_string(v2 & v1));
		}

		IOperand const * operator|(IOperand const & rhs) const
		{
			eOperandType	precision;

			precision = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
			std::string sv1 = rhs.toString();
			std::string sv2 = this->toString();
			std::stringstream s(sv1);
			int v1 ;
			int v2 ;
			s >> v1;
			s = std::stringstream(sv2);
			s >> v2;
			return Factory::get().createOperand(precision, std::to_string(v2 | v1));
		}

		IOperand const * operator+(IOperand const & rhs) const
		{
			eOperandType	precision;

			precision = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
			std::string sv1 = rhs.toString();
			std::string sv2 = this->toString();
			std::stringstream s(sv1);
			double v1 ;
			double v2 ;
			s >> v1;
			s = std::stringstream(sv2);
			s >> v2;
			return Factory::get().createOperand(precision, std::to_string(v2 + v1));
		}

		IOperand const * operator-(IOperand const & rhs) const
		{
			eOperandType	precision;

			precision = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
			std::string sv1 = rhs.toString();
			std::string sv2 = this->toString();
			std::stringstream s(sv1);
			double v1 ;
			double v2 ;
			s >> v1;
			s = std::stringstream(sv2);
			s >> v2;
			return Factory::get().createOperand(precision, std::to_string(v2 - v1));
		}

		IOperand const * operator*(IOperand const & rhs) const
		{
			eOperandType	precision;

			precision = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
			std::string sv1 = rhs.toString();
			std::string sv2 = this->toString();
			std::stringstream s(sv1);
			double v1 ;
			double v2 ;
			s >> v1;
			s = std::stringstream(sv2);
			s >> v2;
			return Factory::get().createOperand(precision, std::to_string(v2 * v1));
		}

		IOperand const * operator/(IOperand const & rhs) const
		{
			eOperandType	precision;

			precision = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
			std::string sv1 = rhs.toString();
			std::string sv2 = this->toString();
			std::stringstream s(sv1);
			double v1 ;
			double v2 ;
			s >> v1;
			if (v1 == 0)
				throw (std::runtime_error("divide by zero"));
			s = std::stringstream(sv2);
			s >> v2;
			return Factory::get().createOperand(precision, std::to_string(v2 / v1));
		}

		IOperand const * operator%(IOperand const & rhs) const
		{
			eOperandType	precision;

			precision = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
			std::string sv1 = rhs.toString();
			std::string sv2 = this->toString();
			std::stringstream s(sv1);
			double v1 ;
			double v2 ;
			s >> v1;
			if (v1 == 0)
				throw (std::runtime_error("modulo by zero"));
			s = std::stringstream(sv2);
			s >> v2;
			return Factory::get().createOperand(precision, std::to_string(std::fmod(v2, v1)));
		}

};

#endif
