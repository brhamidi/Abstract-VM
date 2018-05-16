/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 13:05:43 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/07 13:17:46 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

#include <iostream>

enum eOperandType {
	Int8 = 0, Int16, Int32, Float, Double
};

class IOperand
{
	public:
		virtual int getPrecision( void ) const = 0;
		virtual eOperandType getType( void ) const = 0;

		virtual IOperand const * operator+( IOperand const & rhs ) const = 0;
		virtual IOperand const * operator-( IOperand const & rhs ) const = 0;
		virtual IOperand const * operator*( IOperand const & rhs ) const = 0;
		virtual IOperand const * operator/( IOperand const & rhs ) const = 0;
		virtual IOperand const * operator%( IOperand const & rhs ) const = 0;
		virtual IOperand const * operator|( IOperand const & rhs ) const = 0;
		virtual IOperand const * operator&( IOperand const & rhs ) const = 0;

		virtual std::string const & toString( void ) const = 0;

		virtual ~IOperand( void ) {}
};

#endif
