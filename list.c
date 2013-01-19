// Lossy Scheme: parser.
//
// Copyright 2013 Martin Pool


#include <assert.h>

#include "loss.h"


lossobj *loss_cons_new(void) {
    lossobj *obj = calloc(1, sizeof *obj);
    assert(obj);
    obj->type = CONS;
    return obj;
}

lossobj *loss_cons_new_pair(lossobj *hd, lossobj *tl) {
    lossobj *c = loss_cons_new();
    c->val.cons.hd = hd;
    c->val.cons.tl = tl;
    return c;
}

// Append a to the list in o.  *o must be a cons cell at the start of a
// proper (possibly empty) list.
void loss_list_append(lossobj *o, lossobj *a) {
again:
    assert(o->type == CONS);
    lossobj *hd = o->val.cons.hd,
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

lossobj *loss_list_nth(lossobj *l, int n) {
    while (n > 0) {
        assert(l);
        assert(l->type == CONS);
        l = l->val.cons.tl;
        n--;
    }
    return l->val.cons.hd;
}