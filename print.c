#include <stdio.h>

#include "loss.h"

void loss_print_list_body(const loss_object *cons, bool needspace, FILE *out) {
    const loss_object *hd = cons->val.cons.hd,
        *tl = cons->val.cons.tl;
    if (!hd && !tl)
        // simple empty list
        return;
    loss_print_object(hd, needspace, out);
    if (!tl)
        return;
    if (hd && tl->type == CONS) {
        // Normal list
        loss_print_list_body(tl, true, out);
    } else {
        // General cons cell format
        fputs(". ", out);
        loss_print_object(tl, false, out);
    }
}

// Print any object to a stdio stream
//
// If needspace is true, a space will be printed before objects that must
// be space separated from non-parens.
void loss_print_object(const loss_object *obj, bool needspace, FILE *out) {
    if (needspace)
        fputs(" ", out);

    if (!obj) {
        fputs("nil", out);
    } else if (obj->type == INT) {
        fprintf(out, "%ld", obj->val.integer);
    } else if (obj->type == CONS) {
        fputs("(", out);
        loss_print_list_body(obj, false, out);
        fputs(")", out);
    } else if (obj->type == SYMBOL) {
        const char *sym = obj->val.symbol;
        fprintf(out, "%s", sym);
    } else if (obj->type == NATIVE) {
        fprintf(out, "<native \"%s\">", obj->val.native.name);
    } else {
        fprintf(out, "<unprintable type=%#x> ", obj->type);
    }
}

// vim: et sw=4
