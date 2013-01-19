#include <stdio.h>

#include "loss.h"

void loss_print_list_body(const loss_cons *cons, bool needspace, FILE *out) {
    if (!cons->hd && !cons->tl)
        // simple empty list
        return;
    loss_print_object(cons->hd, needspace, out);
    if (!cons->tl)
        return;
    if (cons->hd && cons->tl->type == CONS) {
        // Normal list
        loss_print_list_body(&cons->tl->val.cons, true, out);
    } else {
        // General cons cell format
        fputs(". ", out);
        loss_print_object(cons->tl, false, out);
    }
}

// Print any object to a stdio stream
//
// If needspace is true, a space will be printed before objects that must
// be space separated from non-parens.
void loss_print_object(const loss_object *obj, bool needspace, FILE *out) {
    if (!obj) {
        fputs("nil", out);
    } else if (obj->type == INT) {
        if (needspace)
            fputs(" ", out);
        fprintf(out, "%ld", obj->val.integer);
    } else if (obj->type == CONS) {
        if (needspace)
            fputs(" ", out);
        const loss_cons *cons = &obj->val.cons;
        fputs("(", out);
        loss_print_list_body(cons, false, out);
        fputs(")", out);
    } else if (obj->type == SYMBOL) {
        if (needspace)
            fputs(" ", out);
        const char *sym = obj->val.symbol;
        fprintf(out, "%s", sym);
    } else {
        if (needspace)
            fputs(" ", out);
        fprintf(out, "<unprintable type=%#x> ", obj->type);
    }
}

// vim: et sw=4
