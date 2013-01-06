// Lossy Scheme: global header.
//
// Copyright 2013 Martin Pool


#include "loss.h"


loss_object *loss_int_from_string(const char *s) {
    loss_object *r = calloc(1, sizeof *r);
    r->type = INT;
    // TODO(mbp): error out if it's not completely an int
    r->val.integer = atol(s);
    return r;
}
