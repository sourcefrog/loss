// Lossy Scheme: parser.
//
// Copyright 2013 Martin Pool


#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "loss.h"


#define LOG(...)


FILE *loss_open_input(const char *filename) {
    FILE *input;
    if (!strcmp(filename, "-")) {
        input = stdin;
    } else {
        input = fopen(filename, "r");
        if (!input) {
            fprintf(stderr, "loss: couldn't open %s: %s\n",
                    filename, strerror(errno));
            return NULL;
        }
    }
    return input;
}


// Read one list or primitive from an input file, and return it.
//
// Parens introduce a list that continues until the closing paren,
// and the whole thing is read.
// Numbers are converted to ints and returned directly.
// Everything else is left as a symbol.
//
// in_sublist: If true, we're reading a nested list and it must be
// terminated by a paren, not eof.  If false, we'r reading the top level
// of the file and it must be terminated by eof, not an unmatched paren.
lossobj *loss_parse(FILE *input, bool in_sublist) {
    lossbuf *tok;
    tok = loss_read_token(input);
    if (!tok) {
        if (in_sublist) {
            // TODO: This causes a message, but then we proceed as if the
            // list was properly terminated.  May not matter.
            fprintf(stderr, "loss: unexpected eof in list\n");
        }
        return NULL;
    }
    LOG("token: %s\n", tok->s);
    const char first = tok->s[0];
    if (first == '(') {
        lossobj *sub_list = loss_cons_new();
        lossobj *subobj;
        while ((subobj = loss_parse(input, true))) {
            loss_list_append(sub_list, subobj);
        }
        return sub_list;
    } else if (first == ')') {
        if (!in_sublist)
            fprintf(stderr, "loss: unexpected ')' at top level\n");
        return NULL;
    } else if (isdigit(first))
        return loss_int_from_string(tok->s);
    else
        return loss_symbol_from_string(tok->s);
}


// Read one token from the input file; return it as a string on the
// heap.  Returns NULL for EOF or error.
lossbuf *loss_read_token(FILE *input) {
    int ch;

    while (1) {
        ch = fgetc(input);
        if (ch == EOF) {
            if (!feof(input)) {
                fprintf(stderr, "loss: error reading source: %s\n",
                        strerror(errno));
            }
            return NULL;
        } else if (ch == '(' || ch == ')')
            return lossbuf_char(ch);
        else if (isspace(ch))
            // Just swallow leading whitespace
            ;
        else
            // ch is the start of a non-paren token.
            break;
    }

    // Accumulate characters, starting with ch, until we hit either
    // whitespace or a paren.
    lossbuf *tok = lossbuf_char(ch);
    while (1) {
        int ch = fgetc(input);
        if (ch == EOF) {
            if (!feof(input)) {
                fprintf(stderr, "loss: error reading source: %s\n",
                        strerror(errno));
                return NULL;
            } else
                return tok;
        } else if (ch == '(' || ch == ')') {
            ungetc(ch, input);
            return tok;
        } else if (isspace(ch))
            return tok;
        else
            lossbuf_push(tok, ch);
    }
}


// Read Scheme from the named file; emit a stream of tokens.
void loss_tokenize(FILE *input) {
    lossbuf *tok;
    while ((tok = loss_read_token(input)) != NULL) {
        LOG("token: %s\n", tok->s);
        lossbuf_free(tok);
    }
}


// vim: et sw=4
