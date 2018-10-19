#pragma once
#include<ttypes.h>

typedef struct {
	char* value;
	int len;
} *String, string;

String string_new(const char* value);
bool string_equal(String a, String b);
int string_compare(String a, String b);
String string_delete(String s);
char* c_string(String s);
int string_length(String s);
char string_char(String s, int i);
String string_substring(String s, int start, int end);
