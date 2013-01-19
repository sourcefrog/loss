/* Copyright 2012, Martin Pool */

#include "loss.h"

// Evaluate an expression and return the result.
//
// Primitive types evaluate to themselves.
loss_object *loss_eval(loss_object *expr) {
again:
    if (!expr)
        return NULL;
    switch (expr->type) {
    case INT:
    case SYMBOL:
        return expr;
    default:
        abort();
    }
}
