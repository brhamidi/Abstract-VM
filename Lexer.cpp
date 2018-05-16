/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 16:37:14 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/07 13:06:05 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"
#include <list>
#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <cstring>
#include <cstdio>
#include <fstream>

Lexer::Lexer(void): _error(false) {}

Lexer::Lexer(int ac, char **av): _error(false)
{
	if (ac == 1)
		this->_tokenizer(std::cin);
	else
	{
		std::ifstream ifs (av[1], std::ifstream::in);
		if (ifs.is_open())
		{
			this->_tokenizer(ifs, 0x01);
			ifs.close();
		}
		else
		{
			std::cout << "Error: opening file." << std::endl;
			this->_error = true;
		}
	}
}

Lexer::~Lexer(void) {}

Lexer::Lexer(Lexer const & rhs)
{
	*this = rhs;
}

Lexer & Lexer::operator=(Lexer const & rhs)
{
	this->_symTab = rhs.getSymTab();
	this->_error = rhs.getError();
	return *this;
}

void	Lexer::_cleanLine(char *line) const
{
	char *tmp = strchr(line, COMMENT_CHAR);
	if (tmp)
		*tmp = '\0';
}

void	Lexer::_nextToken(char *instruction, int &column) const
{
	if (column != -1)
		while (instruction[++column] && instruction[column] != ' ' && instruction[column] != '\t');
	while (instruction[++column] && (instruction[column] == ' ' || instruction[column] == '\t'));
}

struct Token Lexer::_getToken(TokenType t, const char *buf, int col, int raw) const
{
	struct Token token;

	token.type = t;
	if (buf != nullptr)
		token.value = std::string(buf);
	else
		token.value = std::string(" ");
	token.col = col;
	token.raw = raw;
	return token;
}

std::string Lexer::_generateError(const char *buf, int raw, int col)  const
{
	return "\033[31mLexical error\033[0m: " + std::to_string(raw)
		+ ":" +std::to_string(col + 1)
			+ " unknown identifier '\033[33m" + buf + "\033[0m'.";
}

void	Lexer::_matchToken(char *buf, int raw, int col)
{
	std::cmatch match;
	std::regex pattern;

	for (auto e : this->_patternMap)
	{
		pattern = e.first;
		std::regex_match (buf, match, pattern);
		if (match.str() != "")
		{
			this->_symTab.push_back( this->_getToken(e.second, buf, col, raw) );
			return ;
		}
	}
	this->_error = true;
	this->_errorList.push_back( this->_generateError(buf, raw, col) );
}

void	Lexer::_tokenizer(std::istream & istream, int mode)
{
	char		*line;
	std::string	tmp;
	int			raw = 1;
	int			col;
	char		*buf;

	while (std::getline(istream, tmp))
	{
		line = new char [ tmp.size() + 1 ];
		std::strcpy(line, tmp.c_str());
		if (mode == 0  && std::string(line) == ";;")
		{
			delete [] line;
			break ;
		}
		col = -1;

		this->_cleanLine(line);
		buf = std::strtok(line, " \t\r");

		while (buf != NULL)
		{
			this->_nextToken(line, col);
			this->_matchToken(buf, raw, col);
			buf = std::strtok(NULL, " \t\r");
		}
		if (this->_symTab.size() && this->_symTab.back().type != TokenType::SEP)
			this->_symTab.push_back( this->_getToken(TokenType::SEP, "new line" , col, raw) );
		++raw;
		delete [] line;
	}
}

bool				Lexer::getError(void) const
{
	return this->_error;
}

std::list<std::string>	Lexer::getErrorList(void) const
{
	return this->_errorList;
}

std::list<Token> Lexer::getSymTab(void) const
{
	return this->_symTab;
}

std::map<std::string, TokenType> Lexer::_patternMap =
{
	{"(int(8|16|32)\\(([-]?[0-9]+)\\))|(((double|float)\\(([-]?[0-9]+\\.[0-9]+)\\)))", TokenType::VALUE},
	{"and|or|pop|dump|add|sub|mul|div|mod|exit|print", TokenType::ACTION},
	{"push|assert", TokenType::INSTR}
};
