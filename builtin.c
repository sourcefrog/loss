// Copyright 2013 Martin Pool

#include <assert.h>

#include "loss.h"

// Create a new builtin-function object.
// Takes ownership of the name.
lossobj *loss_builtin_new(const char *name, loss_builtin * fn) {
    lossobj *o = calloc(1, sizeof *o);
    o->type = BUILTIN;
    o->val.builtin.name = name;
    o->val.builtin.fn = fn;
    return o;
}

lossobj *loss_builtin_plus(lossobj *env, lossobj *args) {
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

void loss_bind_builtin(lossobj *env, const char *name, loss_builtin * fn) {
    loss_alist_append(
        env,
        loss_string_strz(name),
        loss_builtin_new(name, fn));
}

// Create alist bindings for all builtin functions into `env`.
void loss_bind_builtins(lossobj *env) {
    loss_bind_builtin(env, "+", loss_builtin_plus);
}
