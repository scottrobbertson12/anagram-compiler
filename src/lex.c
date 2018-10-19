#include<tstring.h>
#include<token.h>
#include<ttypes.h>

#include<stdio.h>

typedef bool (*checker)(char);

#define isAlpha(c) ((c >= 'a' && c <='z') || (c >= 'A' && c <= 'Z') || (c == '_'))
#define isAlNum(c) (isAlpha(c) || (c >= '0' && c <= '9'))
#define isNum(c) ((c >= '0') && (c <= '9'))

#define get_specific_tok(code,checker,type)\
	int i = 0;\
	char c;\
	while((c=string_char(code, i)) && checker(c)) i++;\
	return Token_new(type, string_substring(code,0,i));

Token get_token(String code){
	char c = string_char(code,0);
	if(c == '\0'){
		return Token_new(TOK_EOF,string_substring(code,0,1));
	} else if( isAlpha(c) ) {
		get_specific_tok(code, isAlNum, TOK_IDENTIFIER);
	} else if( isNum(c)){
		get_specific_tok(code, isAlNum, TOK_NUMBER);
	} else {
		return Token_new(TOK_ERROR,string_substring(code, 0, 1));
	}
	return 0;
}

DARRAY(Token) get_tokens(String code){
	DARRAY(Token) t = DARRAY_NEW(Token);
	DARRAY_ADD(Token, t, get_token(code));
	DARRAY_ADD(Token, t, get_token(code));
	String s1 = Token_print(DARRAY_GET(Token, t, 0));
	String s2 = Token_print(DARRAY_GET(Token, t, 1));
	printf("%s %s\n", c_string(s1), c_string(s2));
	string_delete(s1);
	string_delete(s2);

	return t;
}
