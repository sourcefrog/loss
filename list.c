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


// Append a to the list in o.  *o must be a cons cell at the start of a
// proper (possibly empty) list.
void loss_list_append(loss_object *o, loss_object *a) {
again:
    assert(o->type == CONS);
    loss_cons *cell = &o->val.cons;
    if (!cell->hd) {
        // First item in an empty list
        assert(cell->tl == NULL);
        cell->hd = a;
        return;
    } else if (cell->tl) {
        // Continue down the list
        o = cell->tl;
        goto again;
    } else {
        // We're on the last occupied cell; we need to insert a new
        // cell and then put the value in there.
        o = cell->tl = loss_cons_new();
        goto again;
    }
}
