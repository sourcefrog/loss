#include <stdio.h>

#include "loss.h"

void loss_print_list_body(const loss_cons *cons, FILE *out) {
    if (!cons->hd && !cons->tl)
        // simple empty list
        return;
    loss_print_object(cons->hd, out);
    if (!cons->tl)
        return;
    if (cons->hd && cons->tl->type == CONS) {
        // Normal list
        loss_print_list_body(&cons->tl->val.cons, out);
    } else {
        // General cons cell format
        fputs(". ", out);
        loss_print_object(cons->tl, out);
    }
}

// Print any object to a stdio stream
void loss_print_object(const loss_object *obj, FILE *out) {
    if (!obj) {
        fputs("nil", out);
    } else if (obj->type == INT) {
        fprintf(out, "%ld ", obj->val.integer);
    } else if (obj->type == CONS) {
        const loss_cons *cons = &obj->val.cons;
        fputs("(", out);
        loss_print_list_body(cons, out);
        fputs(")", out);
    } else if (obj->type == SYMBOL) {
        const char *sym = obj->val.symbol;
        fprintf(out, "%s ", sym);
    } else {
        fprintf(out, "<unprintable type=%#x> ", obj->type);
    }
}

// vim: et sw=4
