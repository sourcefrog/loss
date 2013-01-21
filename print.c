// Copyright 2013 Martin Pool

#include <inttypes.h>
#include <stdio.h>

#include "loss.h"

void loss_print_list_body(const lossobj *cons,
                          bool needspace,
                          FILE *out) {
    const lossobj *hd = cons->val.cons.hd,
        *tl = cons->val.cons.tl;
    if (!hd && !tl)
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
void loss_print_object(const lossobj *obj, bool needspace, FILE *out) {
    if (needspace)
        fputs(" ", out);

    if (!obj) {
        fputs("nil", out);
        return;
    }

    switch (obj->type) {
    case INT:
        fprintf(out, "%" PRId64, obj->val.integer);
        break;
    case CONS:
        fputs("(", out);
        loss_print_list_body(obj, false, out);
        fputs(")", out);
        break;
    case SYMBOL:
        fprintf(out, "%s", obj->val.symbol);
        break;
    case BUILTIN:
        fprintf(out, "<builtin%s \"%s\">",
                obj->val.builtin.special ? "-special" : "",
                obj->val.builtin.name);
        break;
    default:
        fprintf(out, "<unprintable type=%#x> ", obj->type);
    }
}

// vim: et sw=4
