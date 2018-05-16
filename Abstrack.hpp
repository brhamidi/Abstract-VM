/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Abstrack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 14:39:35 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/07 13:08:08 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACK_HPP
# define ABSTRACK_HPP

# include "IOperand.hpp"
# include "Lexer.hpp"
# include <list>
# include <map>
# include "Factory.hpp"
# include <exception>
# include <iostream>


class Abstrack;
typedef void (Abstrack::*INSTRFCT)(struct Token const &);
typedef void (Abstrack::*ACTIONFCT)(void); 

class Abstrack {

	private:
		Abstrack(Abstrack const &);
		Abstrack & operator=(Abstrack const &);
		Abstrack(void);
		std::list<IOperand const *>_stack;

		Factory	& _factory;

		static std::map<std::string, eOperandType> _patternMap;
		static std::map<std::string, ACTIONFCT> _actionMap;
		static std::map<std::string, INSTRFCT> _instrMap;

		IOperand const * _getOpe(std::string const &) const;

		void	_clear( void );

		void	_print( void );
		void	_dump( void );
		void	_pop( void );
		void	_mul( void );
		void	_div( void );
		void	_mod( void );
		void	_add( void );
		void	_or( void );
		void	_and( void );
		void	_sub( void );
		void	_push( struct Token const & );
		void	_assert( struct Token const & );

	public:
		~Abstrack(void);
		Abstrack(std::list<struct Token>);
		std::list<IOperand const *> getStack(void) const;

		class stack_error : public std::length_error
		{
			public:
				stack_error(const char *);
				virtual ~stack_error(void) throw();
		};
		class assert_error : public std::logic_error
		{
			public:
				assert_error(const char *);
				virtual ~assert_error(void) throw();
		};
		class not_printable : public std::invalid_argument
		{
			public:
				not_printable(const char *);
				virtual ~not_printable(void) throw();
		};
};

#endif
