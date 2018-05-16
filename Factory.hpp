/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 12:01:16 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/03 14:35:58 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTORY_HPP
# define FACTORY_HPP

# include "IOperand.hpp"

class Factory {
	private:
		Factory(void);
		Factory(Factory const &);
		Factory & operator=(Factory const &);

		static	Factory * _singleton;
		static IOperand const *(Factory::*_arrayFunction[5])(std::string const &);

		IOperand const * createInt8 ( std::string const & value );
		IOperand const * createInt16 ( std::string const & value );
		IOperand const * createInt32 ( std::string const & value );
		IOperand const * createFloat ( std::string const & value );
		IOperand const * createDouble ( std::string const & value );

	public:
		static Factory & get(void);

		IOperand const * createOperand( eOperandType type, std::string const & value );

		~Factory(void);

};

#endif
