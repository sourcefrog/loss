// Lossy Scheme: global header.
//
// Copyright 2013 Martin Pool


#ifndef _LOSS_H
#define _LOSS_H

#include <stdlib.h>


typedef struct {
	char *s; // nul-terminated string value
	size_t n;  // == strlen(s)
} loss_string;


// A cons cell, with two downward pointers
typedef struct loss_cons {
	struct loss_object *hd, *tl;
} loss_cons;


// A discriminated-union loss object.
typedef struct {
	enum {
		STRING,
		CONS
	} type;
} loss_object;

#endif // _LOSS_H
