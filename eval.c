// Copyright 2013 Martin Pool

#include <assert.h>

#include "loss.h"


// Call a function (builtin or lisp).
lossobj *loss_call(lossobj *fn,
                       lossobj *env,
                       lossobj *args)
{
    switch (fn->type) {
    case BUILTIN:
        return (fn->val.builtin.fn)(env, args);
    default:
        fprintf(stderr, "loss: object is not callable: ");
        loss_print_object(fn, false, stderr);
        fputc('\n', stderr);
        return NULL;
    }
}


lossobj *loss_eval_list(lossobj *env,
                            lossobj *expr) {
    lossobj *fn = expr->val.cons.hd;
    assert(fn);

    lossobj *fn_value = loss_eval(env, fn);
    assert(fn_value);

    // Call must be a proper list
    lossobj *tl = expr->val.cons.tl;
    assert(!tl || tl->type == CONS);

    return loss_call(fn_value, env, tl);
}


// Evaluate an expression and return the result.
//
// Integers evaluate to themselves.
// Symbols evaluate to the binding of the symbol within the environment.
// Lists are the result of calling the first object with the arguments.
lossobj *loss_eval(lossobj *env, lossobj *expr) {
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
