/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 16:03:03 by bhamidi           #+#    #+#             */
/*   Updated: 2018/04/27 19:31:08 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <iostream>
# include <list>
# include "Lexer.hpp"

typedef const std::list<struct Token>::const_iterator const_it;

enum State {
	INITIAL, INPROGRESS, FINISH, REJECTED
};

class Parser
{
	private:
		std::string				_generateError(const struct Token & ) const;
		bool					_compute(const_it, const_it, State, bool);
		std::list<std::string> 	_errorList;
		bool					_error;

	public:
		Parser(void);
		~Parser(void);
		Parser(const Parser &);
		Parser & operator=(const Parser &);

		static State			_fsm[4][4];

		bool					parse(const std::list<struct Token> &);
		bool					getError(void) const;
		std::list<std::string>	getErrorList(void) const;
};

#endif
