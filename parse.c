// Lossy Scheme: parser.
//
// Copyright 2013 Martin Pool


#include <ctype.h>
#include <stdio.h>

#include "loss.h"


// Parse a sequence of tokens into a list.
//
// Parens introduce a list that continues until the closing paren.
// Numbers are converted to ints.
// Everything else is left as a symbol.
//
// in_sublist: If true, we're reading a nested list and it must be
// terminated by a paren, not eof.  If false, we'r reading the top level
// of the file and it must be terminated by eof, not an unmatched paren.
//
loss_object *loss_parse(FILE *input, bool in_sublist) {
    loss_string *tok;
    loss_object *result = loss_cons_new();

    while (true) {
        tok = loss_read_token(input);
        if (!tok)
            if (in_sublist) {
                fprintf(stderr, "loss: unexpected eof in list\n");
                return NULL;
            } else
                break;
        printf("token: %s\n", tok->s);
        if (tok->s[0] == '(') {
            loss_object *sub_list = loss_parse(input, true);
            loss_list_append(result, sub_list);
        } else if (tok->s[0] == ')') {
            if (!in_sublist) {
                fprintf(stderr, "loss: unexpected ')' at top level\n");
                return NULL;
            } else
                break;
        } else if (isdigit(tok->s[0])) {
            loss_object *num = loss_int_from_string(tok->s);
            loss_list_append(result, num);
        }
    }
    return result;
}

// vim: et sw=4
