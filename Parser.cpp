/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 16:03:01 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/07 13:06:48 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include <list>
#include "Lexer.hpp"

Parser::Parser(void) : _error(false) {}

Parser::~Parser(void) {}

Parser::Parser(const Parser & o)
{
	*this = o;
}

Parser & Parser::operator=(const Parser & rhs)
{
	this->_error = rhs.getError();
	this->_errorList = rhs.getErrorList();
	return *this;
}

bool	Parser::getError(void) const
{
	return this->_error;
}

std::list<std::string> Parser::getErrorList(void) const
{
	return this->_errorList;
}

std::string Parser::_generateError(const struct Token & token)  const
{
	return "\033[31mParser error\033[0m: " + 
		std::to_string(token.raw) + ":" +
		std::to_string(token.col + 1) + " '\033[33m" + token.value + "\033[0m'";
}

bool	Parser::_compute(const_it curr_token, const_it end, State curr_state, const bool error)
{
	if (curr_token == end)
		return this->_error;
	const State newState = Parser::_fsm[curr_state][curr_token->type];
	if (newState == State::REJECTED)
		this->_error = true;
	if (newState == State::REJECTED && ! error)
		this->_errorList.push_back(this->_generateError(* curr_token));
	return _compute(std::next(curr_token , 1), end, newState, newState == State::REJECTED ? true : false);
}

bool	Parser::parse(const std::list<struct Token> & list)
{
	const_it begin = list.cbegin();
	const_it end = list.cend();
	return this->_compute(begin, end, State::INITIAL, false);
}

State   Parser::_fsm[4][4] = {
	{State::FINISH, State::INPROGRESS, State::REJECTED, State::INITIAL},
	{State::REJECTED, State::REJECTED, State::FINISH, State::REJECTED},
	{State::REJECTED, State::REJECTED, State::REJECTED, State::INITIAL},
	{State::REJECTED, State::REJECTED, State::REJECTED, State::INITIAL}
};
