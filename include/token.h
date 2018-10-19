#pragma once
#include<stdlib.h>

#include<tstring.h>

typedef enum {
	TOK_EOF,
	TOK_ERROR,	
	TOK_IDENTIFIER,
	TOK_NUMBER,
	TOK_ADD,
	TOK_SUB,
	TOK_MUL,
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_RBRACKET,
	TOK_LBRACKET,
} TokenType;

typedef struct {
	String value;
	TokenType type;

} *Token, token;

NEW_DARRAY_DEF(Token)

Token Token_new(TokenType type, String value);
String Token_print(Token t);
Token Token_delete(Token t);
