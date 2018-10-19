#include<stdio.h>

#include<common.h>
#include<tstring.h>
#include<ttypes.h>
#include<token.h>
#include<lex.h>

int main(void){
	String s = string_new("function test");
	DARRAY(Token) tokens = get_tokens(s);
	FOR(i,0,tokens->count,
			String v = Token_print(DARRAY_GET(Token,tokens,i));
			printf("%s\n", c_string(v));
			string_delete(v););


	DARRAY_DELETE(Token,tokens);	
	string_delete(s);
	return RETURN_NO_ERROR;
}
