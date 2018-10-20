#pragma once
#include<stdlib.h>

#include<tstring.h>
extern string* keywords;
void keywords_delete();

typedef enum {
	KW_PROGRAM=0,
	KW_LIBRARY,
	KW_FUNCTION,
	KW_CLASS,
	KW_INTERFACE,

	KW_RETURN,
	KW_ENTRY,

	KW_AND,
	KW_OR,
	KW_XOR,
	KW_EQUALS,

	KW_END,

	TOK_EOF,
	TOK_ERROR,	

	TOK_IDENTIFIER,
	TOK_NUMBER,

	TOK_ADD,
	TOK_SUB,
	TOK_MUL,
	TOK_DIV,

	TOK_LPAREN,
	TOK_RPAREN,

	TOK_RBRACKET,
	TOK_LBRACKET,

	TOK_LBRACE,
	TOK_RBRACE,

	TOK_HASH,
	TOK_SEMICOLON,
} tokenType;

typedef struct {
	string value;
	tokenType type;
	int line, col;
} *token, Token;

NEW_DARRAY_DEF(token)

token token_new(tokenType type, string value, int line, int col);
string token_print(token t);
token token_delete(token t);
