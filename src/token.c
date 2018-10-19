#include<token.h>
#include<tstring.h>
#include<math.h>
#include<stdio.h>

NEW_DARRAY_IMPL(Token, token);

Token Token_new(TokenType type, String s){
	Token t = malloc(sizeof(token));
	t->value = s;
	t->type = type;
	return t;
}

String Token_print(Token t){
	if(t == 0){
		return 0;
	}
	int length = string_length(t->value) + 5 + floor(log10(abs(t->type))) + 10;
	char* value = malloc(sizeof(char) * length);
	sprintf(value,"( %s:%i )",c_string(t->value),t->type);
	value[length-1]='\0';
	String s = string_new(value);
	free(value);
	return s;
}

Token Token_delete(Token t){
	if(t && t->value){
		string_delete(t->value);
		free(t);
		return 0;
	}
	return t;
}
