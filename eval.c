// Copyright 2013 Martin Pool

#include <assert.h>

#include "loss.h"


// Call a function (native or lisp).
loss_object *loss_call(loss_object *fn,
                       loss_object *env,
                       loss_object *args)
{
    switch (fn->type) {
    case NATIVE:
        return (fn->val.native.fn)(env, args);
    default:
        fprintf(stderr, "loss: object is not callable: ");
        loss_print_object(fn, false, stderr);
        fputc('\n', stderr);
        return NULL;
    }
}


loss_object *loss_eval_list(loss_object *env,
                            loss_object *expr) {
    loss_object *fn = expr->val.cons.hd;
    assert(fn);

    loss_object *fn_value = loss_eval(env, fn);
    assert(fn_value);

    // Call must be a proper list
    loss_object *tl = expr->val.cons.tl;
    assert(!tl || tl->type == CONS);

    return loss_call(fn_value, env, tl);
}


// Evaluate an expression and return the result.
//
// Integers evaluate to themselves.
// Symbols evaluate to the binding of the symbol within the environment.
// Lists are the result of calling the first object with the arguments.
loss_object *loss_eval(loss_object *env, loss_object *expr) {
    if (!expr)
        return NULL;
    switch (expr->type) {
    case INT:
        return expr;
    case SYMBOL:
        return loss_alist_lookup_sz(env, expr->val.symbol);
    case CONS:
        return loss_eval_list(env, expr);
    default:
        fprintf(stderr, "loss: can't eval object type %#x\n", expr->type);
        abort();
    }
}
