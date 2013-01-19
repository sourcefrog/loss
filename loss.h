// Lossy Scheme: global header.
//
// Copyright 2013 Martin Pool


#ifndef _LOSS_H
#define _LOSS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


typedef struct {
    char *s;                    // nul-terminated string value
    size_t n;                   // == strlen(s)
} loss_string;


typedef struct loss_object loss_object;

// A cons cell, with two downward pointers
typedef struct loss_cons {
    loss_object *hd, *tl;
} loss_cons;


// A discriminated-union object.
struct loss_object {
    enum {
        CONS,
        INT,
        SYMBOL
    } type;
    union {
        int64_t integer;
        loss_cons cons;
        char *symbol;
    } val;
};

void loss_tokenize(FILE *input);
loss_string *loss_read_token(FILE *input);

loss_object *loss_cons_new(void);

loss_object *loss_parse(FILE *input, bool in_sublist);
FILE *loss_open_input(const char *filename);

loss_object *loss_int_from_string(const char *);

void loss_list_append(loss_object *, loss_object *);

void loss_print_object(const loss_object *obj, bool needspace, FILE *out);

loss_object *loss_symbol_from_string(const char *s);

loss_object *loss_eval(loss_object *obj);

loss_string *loss_string_char(char ch);
void loss_string_push(loss_string *tok, char ch);
void loss_string_free(loss_string *);

#endif                          // _LOSS_H
