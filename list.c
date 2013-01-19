// Lossy Scheme: parser.
//
// Copyright 2013 Martin Pool


#include <assert.h>

#include "loss.h"


loss_object *loss_cons_new(void) {
    loss_object *obj = calloc(1, sizeof *obj);
    assert(obj);
    obj->type = CONS;
    return obj;
}


loss_object *loss_cons_new_pair(loss_object *hd, loss_object *tl) {
    loss_object *c = loss_cons_new();
    c->val.cons.hd = hd;
    c->val.cons.tl = tl;
    return c;
}


// Append a to the list in o.  *o must be a cons cell at the start of a
// proper (possibly empty) list.
void loss_list_append(loss_object *o, loss_object *a) {
again:
    assert(o->type == CONS);
    loss_object *hd = o->val.cons.hd,
        *tl = o->val.cons.tl;
    if (!hd) {
        // First item in an empty list
        assert(tl == NULL);
        o->val.cons.hd = a;
        return;
    } else if (tl) {
        // Continue down the list
        o = tl;
        goto again;
    } else {
        // We're on the last occupied cell; we need to insert a new
        // cell and then put the value in there.
        o = o->val.cons.tl = loss_cons_new();
        goto again;
    }
}
