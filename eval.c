/* Copyright 2012, Martin Pool */

#include "loss.h"

// Evaluate an expression and return the result.
//
// Integers evaluate to themselves.
// Symbols evaluate to the binding of the symbol within the environment.
loss_object *loss_eval(loss_object *env, loss_object *expr) {
    if (!expr)
        return NULL;
    switch (expr->type) {
    case INT:
        return expr;
    case SYMBOL:
        return loss_alist_lookup_sz(env, expr->val.symbol);
    default:
        abort();
    }
}
