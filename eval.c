// Copyright 2013 Martin Pool

#include <assert.h>

#include "loss.h"


// Evaluate each argument in the list, building a parallel list of actual
// argument values.
lossobj *loss_eval_arglist(lossobj *env, lossobj *args) {
    if (!args)
        return args;
    assert(args->type == CONS);
    lossobj *hd = args->val.cons.hd;
    assert(hd);
    return loss_cons_new_pair(
        loss_eval(env, hd),
        loss_eval_arglist(env, args->val.cons.tl));
}

// Call a function (builtin or lisp).
// Evaluates the arguments.
lossobj *loss_call(lossobj *env,
                   lossobj *fn,
                   lossobj *args)
{
    // TODO(mbp): For special forms, don't evaluate the args.
    lossobj *concrete = loss_eval_arglist(env, args);
    switch (fn->type) {
    case BUILTIN:
        return (fn->val.builtin.fn)(env, concrete);
    default:
        fprintf(stderr, "loss: object is not callable: ");
        loss_print_object(fn, false, stderr);
        fputc('\n', stderr);
        return NULL;
    }
}

lossobj *loss_eval_call(lossobj *env,
                        lossobj *expr) {
    lossobj *fn = expr->val.cons.hd;
    assert(fn);
    lossobj *fn_value = loss_eval(env, fn);
    if (!fn_value)
        return fn_value;
    lossobj *tl = expr->val.cons.tl;
    assert(!tl || tl->type == CONS);
    return loss_call(env, fn_value, tl);
}


// Evaluate an expression and return the result.
//
// Integers evaluate to themselves.
// Symbols evaluate to the binding of the symbol within the environment.
// Lists are the result of calling the first object with the arguments.
lossobj *loss_eval(lossobj *env, lossobj *expr) {
    if (!expr)
        return NULL;
    lossobj *result;
    switch (expr->type) {
    case INT:
        return expr;
    case SYMBOL:
        result = loss_alist_lookup_sz(env, expr->val.symbol);
        if (!result) {
            fprintf(stderr, "loss: symbol \"%s\" not defined\n",
                    expr->val.symbol);
        }
        return result;
    case CONS:
        return loss_eval_call(env, expr);
    default:
        fprintf(stderr, "loss: can't eval object type=%#x:", expr->type);
        loss_print_object(expr, false, stderr);
        fputc('\n', stderr);
        abort();
    }
}
