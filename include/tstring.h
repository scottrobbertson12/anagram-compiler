#pragma once
#include<ttypes.h>

typedef struct {
	char* value;
	int len;
} *string, String;

string string_new(const char* value);
bool string_equal(string a, string b);
int string_compare(string a, string b);
string string_delete(string s);
char* c_string(string s);
int string_length(string s);
char string_char(string s, int i);
string string_substring(string s, int start, int end);
