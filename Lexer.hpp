/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 16:29:12 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/05 19:18:53 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP

# include <iostream>
# include <list>
# include <regex>
# include <map>

# define COMMENT_CHAR	';'

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

enum TokenType {
	ACTION, INSTR, VALUE, SEP
};

struct Token {
	TokenType	type;
	std::string	value;
	int 		col;
	int 		raw;
};

class Lexer
{
	private:
		Lexer(void);

		std::list<struct Token>	_symTab;
		std::list<std::string> 	_errorList;
		bool					_error;

		static std::map<std::string, TokenType> _patternMap;

		void			_tokenizer(std::istream &, int mode = 0);
		std::string		_generateError(const char *, int, int) const;
		void			_matchToken(char*, int, int);
		void			_cleanLine(char*) const;
		void			_nextToken(char *, int &) const;
		struct Token	_getToken(TokenType, const char*, int, int) const;


	public:
		Lexer(int, char **);
		~Lexer(void);
		Lexer(Lexer const &);
		Lexer & operator=(Lexer const &);

		bool					getError(void) const;
		std::list<struct Token>	getSymTab(void) const;
		std::list<std::string>	getErrorList(void) const;

};

# endif
