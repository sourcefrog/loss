// Copyright 2013 Martin Pool

#include <assert.h>

#include "loss.h"

// Create a new builtin-function object.
// Takes ownership of the name.
lossobj *lossbuiltin_new(const char *name, lossbuiltin *fn, bool special) {
    lossobj *o = calloc(1, sizeof *o);
    o->type = BUILTIN;
    o->val.builtin.name = name;
    o->val.builtin.fn = fn;
    o->val.builtin.special = special;
    return o;
}

lossobj *lossbuiltin_plus(lossobj *env, lossobj *args) {
    int64_t result = 0;
    while (args) {
        assert(args->type == CONS);
        lossobj *hd = args->val.cons.hd;
        assert(hd && hd->type == INT);
        result += hd->val.integer;
        args = args->val.cons.tl;
    }
    return loss_int_new(result);
}

lossobj *lossbuiltin_display(lossobj *env, lossobj *args) {
    bool needspace = false;
    while (args) {
        assert(args->type == CONS);
        lossobj *hd = args->val.cons.hd;
        loss_print_object(hd, needspace, stdout);
        args = args->val.cons.tl;
        needspace = true;
    }
    fputc('\n', stdout);
    return NULL;
}

// Should an object be treated as true or false?
// Strictly, in Scheme, only #f should be false
// <http://www.r6rs.org/final/html/r6rs/r6rs-Z-H-8.html#node_sec_5.7>.
bool loss_bool_value(lossobj *val) {
    if (!val)
        return false;
    switch (val->type) {
    case INT:
        return val->val.integer != 0;
    default:
        return true;
    }
}

lossobj *loss_special_if(lossobj *env, lossobj *args) {
    assert(args->type == CONS);
    lossobj *hd = args->val.cons.hd;
    lossobj *val = loss_eval(env, hd);
    bool boolval = loss_bool_value(val);
    if (boolval)
        return loss_eval(env, loss_list_nth(args, 1));
    lossobj *else_expr = loss_list_nth(args, 2);
    if (else_expr)
        return loss_eval(env, else_expr);
    return NULL;
}

void loss_bind_builtin(lossobj *env,
                       const char *name,
                       lossbuiltin * fn,
                       bool special) {
    loss_alist_append(
        env,
        loss_string_strz(name),
        lossbuiltin_new(name, fn, special));
}

// Create alist bindings for all builtin functions into `env`.
void loss_bind_builtins(lossobj *env) {
    loss_bind_builtin(env, "+", lossbuiltin_plus, false);
    loss_bind_builtin(env, "display", lossbuiltin_display, false);
    loss_bind_builtin(env, "if", loss_special_if, true);
}
