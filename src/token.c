#include<token.h>
#include<tstring.h>
#include<math.h>
#include<stdio.h>

NEW_DARRAY_IMPL(token);

string *keywords = 0;

void keywords_init(){
	keywords = malloc(sizeof(String) * KW_END);
	keywords[KW_PROGRAM] = string_new("program");
	keywords[KW_LIBRARY] = string_new("library");
	keywords[KW_FUNCTION] = string_new("function");
	keywords[KW_RETURN] = string_new("return");
	keywords[KW_ENTRY] = string_new("entry");
}

void keywords_delete(){
	for(int i = 0; i < KW_END; i++){
		string_delete(keywords[i]);
	}
	free(keywords);
	keywords = 0;
}

token token_new(tokenType type, string s, int line, int col){
	if(!keywords)
		keywords_init();
	token t = malloc(sizeof(Token));
	t->value = s;
	t->type = type;
	t->line = line;
	t->col = col;
	return t;
}

int int_length(int i){
	int length = 0;
	while(i != 0){
		length++;
		i=i/10;
	}
	return length;
}

#define PAD_LENGTH 11
string token_print(token t){
	if(t == 0){
		return 0;
	}

	int length = string_length(t->value) + PAD_LENGTH + int_length(t->type) + int_length(t->line) + int_length(t->col)+5;
	char* value = malloc(sizeof(char) * length + 1);

	sprintf(value,"( %i:%i '%s':'%i' )",t->line, t->col, c_string(t->value),t->type);

	value[length-1]='\0';

	string s = string_new(value);
	free(value);

	return s;
}

token token_delete(token t){
	if(t && t->value){
		string_delete(t->value);
		free(t);
		return 0;
	}
	return t;
}
