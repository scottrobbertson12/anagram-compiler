#include<tstring.h>
#include<token.h>
#include<ttypes.h>

#include<stdio.h>

typedef bool (*checker)(char);

#define isAlpha(c) ((c >= 'a' && c <='z') || (c >= 'A' && c <= 'Z') || (c == '_'))
#define isAlNum(c) (isAlpha(c) || (c >= '0' && c <= '9'))
#define isNum(c) ((c >= '0') && (c <= '9'))
#define isWhiteSpace(c) (c==' ' || c=='\n' || c=='\t' || c=='\v')

#define get_specific_tok(code,checker,type)\
	int i = 0;\
	char c;\
	while((c=string_char(code, i)) && checker(c)) i++;\
	return token_new(type, string_substring(code,0,i), line, col);

token get_string(string code, int line, int col){
	return token_new(TOK_ERROR,string_substring(code,0,1), line, col);
}

#define n_character(n,code,type) return token_new(type,string_substring(code, 0, n), line, col);

token get_token(string code, int line, int col){
	char c = string_char(code,0);
	if(c == '\0'){
		return token_new(TOK_EOF,string_substring(code,0,1), line, col);
	} else if( isAlpha(c) ) {
		get_specific_tok(code, isAlNum, TOK_IDENTIFIER);
	} else if( isNum(c)){
		get_specific_tok(code, isAlNum, TOK_NUMBER);
	} else if(c == '"'){
		return get_string(code, line, col);		
	} else {
		switch(c){
			case '+': n_character(1, code, TOK_ADD);
			case '-': n_character(1, code, TOK_SUB);
			case '*': n_character(1, code, TOK_MUL);
			case '(': n_character(1, code, TOK_LPAREN);
			case ')': n_character(1, code, TOK_RPAREN);
			case '{': n_character(1, code, TOK_LBRACKET);
			case '}': n_character(1, code, TOK_RBRACKET);
			case ';': n_character(1, code, TOK_SEMICOLON);
			case '[': n_character(1, code, TOK_LBRACE);
			case ']': n_character(1, code, TOK_RBRACE);
			case '#': n_character(1, code, TOK_HASH);
			default: n_character(1, code, TOK_ERROR);
		}
	}
	return 0;
}

token keyword_check(token tok){
	for(int i = 0; i < KW_END; i++){
		if(string_equal(tok->value, keywords[i]))
			tok->type = i;
	}
	return tok;
}

DARRAY(token) get_tokens(string code){
	int line=0, col=0;
	DARRAY(token) t = DARRAY_NEW(token);

	code = string_substring(code, 0, string_length(code));
	while(string_length(code) != 0){
		token tok = get_token(code, line, col);
		tok = keyword_check(tok);

		DARRAY_ADD(token, t, tok);

		string c2 = string_substring(code, string_length(tok->value), string_length(code)-string_length(tok->value));
		col += string_length(tok->value);
		string_delete(code);
		code = c2;

		while(string_length(code) != 0 && isWhiteSpace(string_char(code,0))){
			if(string_char(code,0) == '\n'){
				line++; 
				col=0;
			}
			string c = string_substring(code,1,string_length(code)-1);
			string_delete(code);
			code = c;
		}
	}
	string_delete(code);
	return t;
}
