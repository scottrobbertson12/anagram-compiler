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




#define NEW_DARRAY_IMPL(Type)\
	Darray##Type darray##Type##_new() {\
		Darray##Type d = malloc(sizeof(darray##Type));\
		d->len = 0;\
	       	d->vals = 0;\
		d->count = 0;\
	       	return d;\
       	}\
	void darray##Type##_resize(Darray##Type d, int len){\
		if(d==0) return;\
		if(len == 0){\
		       	FOR(i,0,d->count+1,Type##_delete(d->vals[i]);); d->vals = realloc(d->vals,0);\
			d->len=0; d->count=0;}\
		else if(len < d->count){\
			FOR(i,len,d->count+1,Type##_delete(d->vals[i]););\
		} else {\
			d->vals = realloc(d->vals, len);\
			d->len = len;\
		}\
	}\
	void darray##Type##_insert(Darray##Type d, Type a) {\
		if(d==0) return;\
		if((d->count+1) < d->len ){ d->vals[(d->count)++] = a; }\
		else {\
		       	darray##Type##_resize(d,(d->len>0)?(d->len*2):8);\
			d->vals[(d->count)++]=a;\
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


