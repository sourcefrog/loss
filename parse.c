// Lossy Scheme: parser.
//
// Copyright 2013 Martin Pool


#include <ctype.h>

#include "loss.h"


// Parse a sequence of tokens into a list.
//
// Parens introduce a list that continues until the closing paren.
// Numbers are converted to ints.
// Everything else is left as a symbol.
loss_object *loss_parse(FILE *input) {
    loss_string *tok;
    loss_object *result = loss_cons_new();

    while ((tok = loss_read_token(input))) {
        printf("token: %s\n", tok->s);
        if (isdigit(tok->s[0])) {
            loss_object *num = loss_int_from_string(tok->s);
            loss_list_append(result, num);
        }
    }

    return result;
}
