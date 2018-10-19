#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include<tstring.h>
#include<ttypes.h>

String string_new(const char* value){
	String s = malloc(sizeof(string));

	s->len = strlen(value);
	s->value = malloc(s->len+1);
	strcpy(s->value,value);
	s->value[s->len] = '\0';

	return s;
}

char* c_string(String s){
	if(s == 0 || s->value == 0)
		return 0;
	return s->value;
}

bool string_equal(String a, String b){
	if (a && b){
	       	if(a->len == b->len && a->len != 0){
			return strcmp(a->value, b->value) == 0;
	       	} else {
		       	return 0;
	       	}
	} else {
		return -255;
	}
}

int string_compare(String a, String b){
	if(a && b){
		return strcmp(a->value,b->value);
	} else {
		return -255;
	}
}

String string_delete(String s){
	if(s && s->value){
		free(s->value);
		s->len = 0;
		free(s);
		return 0;
	}
	return s;
}

int string_length(String s){
	if(s){
		return s->len;
	}
	return 0;
}

char string_char(String s, int i){
	if(s && s->len > i){
		return s->value[i];
	}
	return 0;
}

#include<stdio.h>
String string_substring(String s, int start, int nchars){
	if(nchars> 0 && string_length(s) >= start+nchars){
		char* val = malloc(sizeof(char) * (nchars+1));	
		strncpy(val,c_string(s)+start,nchars);
		val[nchars]= '\0';
		String sub = string_new(val);
		free(val);
		return sub;
	} 
	return 0;
}
