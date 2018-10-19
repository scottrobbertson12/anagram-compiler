#include<stdlib.h>
#include<stdarg.h>

#include<tuple.h>


Tuple tuple_new(int len,...) {
	va_list args;
	va_start(args, len);

	Tuple t = malloc(sizeof(tuple));
	t->len = len;
	t->contents = malloc(sizeof(void*) * len);

	for(int i = 0; i < len; i++){
		(t->contents)[i] = va_arg(args,void*);
	}

	va_end(args);

	return t;
}
