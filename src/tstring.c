#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include<tstring.h>
#include<ttypes.h>

string string_new(const char* value){
	string s = malloc(sizeof(String));

	s->len = strlen(value);
	s->value = malloc((s->len)+1);
	strcpy(s->value,value);
	s->value[s->len] = '\0';

	return s;
}

char* c_string(string s){
	if(s == 0 || s->value == 0)
		return 0;
	return s->value;
}

bool string_equal(string a, string b){
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

int string_compare(string a, string b){
	if(a && b){
		return strcmp(a->value,b->value);
	} else {
		return -255;
	}
}

string string_delete(string s){
	if(s && s->value){
		free(s->value);
		s->len = 0;
		free(s);
		return 0;
	}
	return s;
}

int string_length(string s){
	if(s){
		return s->len;
	}
	return 0;
}

char string_char(string s, int i){
	if(s && s->len > i){
		return s->value[i];
	}
	return 0;
}

string string_substring(string s, int start, int nchars){
	if(string_length(s) >= start+nchars){
		char* val = malloc(sizeof(char) * (nchars+1));	
		strncpy(val,c_string(s)+start,nchars);
		val[nchars]= '\0';
		string sub = string_new(val);
		free(val);
		return sub;
	}
	return 0;
}
