#include <stdio.h>
#include <string.h>
#include "loss.h"

loss_object *loss_symbol_from_string(const char *s) {
    switch (*s) {
        case 0:
        case '(':
        case ')':
        case ' ':
        case '\n':
            fprintf(stderr, "invalid symbol: \"%s\"\n", s);
            abort();
    }
    loss_object *obj = calloc(1, sizeof *obj);
    obj->type = SYMBOL;
    obj->val.symbol = strdup(s);
    return obj;
}

// vim: et sw=4
