// Copyright 2013 Martin Pool


#include "loss.h"


lossobj *loss_int_new(int64_t val) {
    lossobj *r = calloc(1, sizeof *r);
    r->type = INT;
    r->val.integer = val;
    return r;
}


lossobj *loss_int_from_string(const char *s) {
    // TODO(mbp): Error if it's not completely a string
    return loss_int_new(atol(s));
}
