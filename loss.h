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

typedef loss_object *(loss_native)(loss_object *, loss_object *);

// A discriminated-union object.
struct loss_object {
    enum {
        CONS,
        INT,
        SYMBOL,
        STRING,
        NATIVE,
    } type;
    union {
        int64_t integer;
        struct {
            loss_object *hd, *tl;
        } cons;
        char *symbol;
        char *string;
        struct {
            const char *name;
            loss_native *fn;
        } native;
    } val;
};


void loss_tokenize(FILE *input);
loss_string *loss_read_token(FILE *input);

loss_object *loss_cons_new(void);
loss_object *loss_cons_new_pair(loss_object *hd, loss_object *tl);

loss_object *loss_parse(FILE *input, bool in_sublist);
FILE *loss_open_input(const char *filename);

loss_object *loss_int_from_string(const char *);

void loss_list_append(loss_object *, loss_object *);

void loss_print_object(const loss_object *obj, bool needspace, FILE *out);

loss_object *loss_symbol_from_string(const char *s);

loss_object *loss_eval(loss_object *env, loss_object *obj);

loss_object *loss_string_strz(const char *);
loss_string *loss_string_char(char ch);
void loss_string_push(loss_string *tok, char ch);
void loss_string_free(loss_string *);

void loss_bind_builtins(loss_object *env);

void loss_alist_append(loss_object *alist, loss_object *name, loss_object *value);
loss_object *loss_alist_lookup_sz(
    const loss_object *alist,
    const char *);

#endif                          // _LOSS_H
