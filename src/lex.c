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

Token get_string(String code){
	return Token_new(TOK_ERROR,string_substring(code,0,1));
}

Token get_token(String code){
	char c = string_char(code,0);
	if(c == '\0'){
		return Token_new(TOK_EOF,string_substring(code,0,1));
	} else if( isAlpha(c) ) {
		get_specific_tok(code, isAlNum, TOK_IDENTIFIER);
	} else if( isNum(c)){
		get_specific_tok(code, isAlNum, TOK_NUMBER);
	} else if(c == '"'){
		return get_string(code);		
	} else {
		switch(c){
			case '+': return Token_new(TOK_ADD, string_substring(code, 0, 1));
				  break;
			case '-': return Token_new(TOK_SUB, string_substring(code, 0, 1));
				  break;
			default: return Token_new(TOK_ERROR,string_substring(code, 0, 1));
				 break;
		}
	}
	return 0;
}

DARRAY(Token) get_tokens(String code){
	DARRAY(Token) t = DARRAY_NEW(Token);

	code = string_substring(code, 0, string_length(code));
	while(string_length(code) != 0){
		Token tok = get_token(code);
		DARRAY_ADD(Token, t, tok);
		String c2 = string_substring(code, string_length(tok->value), string_length(code)-string_length(tok->value));
		string_delete(code);
		code = c2;
		while(string_length(code) != 0 && string_char(code,0) == ' '){
			String c = string_substring(code,1,string_length(code)-1);
			string_delete(code);
			code = c;
		}
	}
	string_delete(code);
	return t;
}
