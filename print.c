#include <stdio.h>

#include "loss.h"


// Print any object to a stdio stream
void loss_print_object(loss_object *obj, FILE *out) {
    if (!obj) {
        fputs("nil", out);
    } else if (obj->type == INT) {
        fprintf(out, "%ld ", obj->val.integer);
    } else if (obj->type == CONS) {
        // TODO(mbp): Optimize normal lists
        fprintf(out, "( ");
        loss_print_object(obj->val.cons.hd, out);
        fprintf(out, ". ");
        loss_print_object(obj->val.cons.tl, out);
        fprintf(out, ") ");
    } else {
        fprintf(out, "<unprintable type=%#x> ", obj->type);
    }
}

// vim: et sw=4
