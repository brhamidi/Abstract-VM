/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 12:06:09 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/07 13:41:21 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Lexer.hpp"
#include "Parser.hpp"
#include <iomanip>
#include "Abstrack.hpp"
#include "Factory.hpp"

std::string nameForType(TokenType t)
{
	switch(t)
	{
		case INSTR  : return std::string("INSTR");
		case ACTION  : return std::string("ACTION");
		case VALUE  : return std::string("VALUE");
		case SEP  : return std::string("SEP");
	}
	return std::string("UNKNOWN");
}

void	printErrorList(std::list<std::string> list)
{
	for (auto e : list)
		std::cout << e << std::endl;
	std::exit(1);
}

void	printSymTab(std::list<struct Token> list)
{
	std::cout << std::setw(10) << "symbol" << " | " << std::setw(15) << "value" << " | " << std::endl;
	std::cout << std::setfill ('-') << std::setw (25 + 6) << " " << std::setfill(' ') << std::endl;
	for (auto t : list)
		std::cout << std::setw(10) << nameForType(t.type) << " | "
			<< std::setw(15) << t.value << " | " << std::endl;
}

int		main(int ac, char **av)
{
	Lexer	lex(ac, av);
	Parser	parse;

	if ( lex.getError() )
		printErrorList(lex.getErrorList());

	parse.parse( lex.getSymTab() );
	if ( parse.getError() )
		printErrorList(parse.getErrorList());
	
	Abstrack vm ( lex.getSymTab() );
	return (0);
}
