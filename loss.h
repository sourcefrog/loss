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
} lossbuf;


typedef struct lossobj lossobj;

typedef lossobj *(lossbuiltin)(lossobj *, lossobj *);

struct lossobj {
    enum {
        CONS,
        INT,
        SYMBOL,
        STRING,
        BUILTIN,
    } type;
    union {
        int64_t integer;
        struct {
            lossobj *hd, *tl;
        } cons;
        char *symbol;
        char *string;
        struct {
            const char *name;
            lossbuiltin *fn;
            bool special;
        } builtin;
    } val;
};


void loss_tokenize(FILE *input);
lossbuf *loss_read_token(FILE *input);

lossobj *loss_cons_new(void);
lossobj *loss_cons_new_pair(lossobj *hd, lossobj *tl);

lossobj *loss_parse(FILE *input, bool in_sublist);
FILE *loss_open_input(const char *filename);

lossobj *loss_int_from_string(const char *);
lossobj *loss_int_new(int64_t val);

void loss_list_append(lossobj *, lossobj *);
lossobj *loss_list_nth(lossobj *l, int n);
int loss_list_len(lossobj *l);

void loss_print_object(const lossobj *obj, bool needspace, FILE *out);

lossobj *loss_symbol_from_string(const char *s);

lossobj *loss_eval(lossobj *env, lossobj *obj);

lossobj *loss_string_strz(const char *);
lossbuf *lossbuf_char(char ch);
void lossbuf_push(lossbuf *tok, char ch);
void lossbuf_free(lossbuf *);

void loss_bind_builtins(lossobj *env);

void loss_alist_append(lossobj *alist, lossobj *name, lossobj *value);
lossobj *loss_alist_lookup_sz(
    const lossobj *alist,
    const char *);

#endif                          // _LOSS_H
