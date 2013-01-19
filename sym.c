#include <stdio.h>
#include <string.h>
#include "loss.h"

lossobj *loss_symbol_from_string(const char *s) {
    switch (*s) {
    case 0:
    case '(':
    case ')':
    case ' ':
    case '\n':
        fprintf(stderr, "invalid symbol: \"%s\"\n", s);
        abort();
    }
    lossobj *obj = calloc(1, sizeof *obj);
    obj->type = SYMBOL;
    obj->val.symbol = strdup(s);
    return obj;
}

// vim: et sw=4
