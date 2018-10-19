#include<stdio.h>

#include<common.h>
#include<tstring.h>
#include<ttypes.h>
#include<token.h>
#include<lex.h>

int main(void){
	String s = string_new("94324testing another function");
	DARRAY(Token) tokens = get_tokens(s);
	DARRAY_DELETE(Token,tokens);	
	string_delete(s);
	return RETURN_NO_ERROR;
}
