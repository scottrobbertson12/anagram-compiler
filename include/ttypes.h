#pragma once

typedef enum {
	BOOL_FALSE,
	BOOL_TRUE,
} bool;

#define FOR(I,S,E,C) for(int I=S; I<E; I++) { C }

#define DARRAY(Type) Darray##Type
#define DARRAY_NEW(Type) darray##Type##_new()
#define DARRAY_GET(Type, d, i) darray##Type##_get(d, i)
#define DARRAY_ADD(Type, d, v) darray##Type##_insert(d,v)
#define DARRAY_DELETE(Type,d) darray##Type##_delete(d)

#include<stdlib.h>

///! Darray##Type##Definitions
// This structure holds a generic darray
// The length is the actualy number of items
// that can fit in the array
// the count is the number of items actually in the array
#define NEW_DARRAY_DEF(Type)\
       	typedef struct {\
	       	int len;\
		int count;\
	       	Type* vals;\
       	} *Darray##Type, darray##Type;\
	Darray##Type darray##Type##_new();\
	void darray##Type##_resize(Darray##Type d, int len);\
	void darray##Type##_insert(Darray##Type d, Type a);\
	Type darray##Type##_get(Darray##Type d, int i);\
	void darray##Type##_delete(Darray##Type d);




#define NEW_DARRAY_IMPL(Type,type)\
	Darray##Type darray##Type##_new() {\
		Darray##Type d = malloc(sizeof(darray##Type));\
		d->vals = malloc(sizeof(type) * 9);\
		d->len = 8;\
		d->count = 0;\
	       	return d;\
       	}\
	void darray##Type##_resize(Darray##Type d, int len){\
		if(d==0) return;\
		if(len < d->count){\
			printf("resizing darray from %i to %i\n", d->len, len);\
			FOR(i,len,d->count,Type##_delete(d->vals[i]);); d->vals = realloc(d->vals,len);\
		} else {\
			d->vals = realloc(d->vals, len);\
			d->len = len;\
		}\
	}\
	void darray##Type##_insert(Darray##Type d, Type a) {\
		if(d==0) return;\
		if((d->count+1) < d->len ){ d->vals[(d->count)] = a; (d->count)++; }\
		else {\
		       	darray##Type##_resize(d,(d->len*2));\
			d->vals[(d->count)]=a; (d->count)++;\
	       	}\
	}\
	Type darray##Type##_get(Darray##Type d, int i) {\
		if(d==0) return 0;\
		if((d->count < i)) return 0;\
		return d->vals[i];\
	}\
	void darray##Type##_delete(Darray##Type d){\
		darray##Type##_resize(d, 0);\
		free(d);\
	}


