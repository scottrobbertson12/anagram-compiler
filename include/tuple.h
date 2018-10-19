#pragma once

typedef struct {
	void** contents;
	int len;
} *Tuple, tuple;

Tuple tuple_new(int len, ...);
