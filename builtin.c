// Copyright 2013 Martin Pool

#include <assert.h>

#include "loss.h"

// Create a new builtin-function object.
// Takes ownership of the name.
lossobj *lossbuiltin_new(const char *name, lossbuiltin * fn) {
    lossobj *o = calloc(1, sizeof *o);
    o->type = BUILTIN;
    o->val.builtin.name = name;
    o->val.builtin.fn = fn;
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

void loss_bind_builtin(lossobj *env, const char *name, lossbuiltin * fn) {
    loss_alist_append(
        env,
        loss_string_strz(name),
        lossbuiltin_new(name, fn));
}

// Create alist bindings for all builtin functions into `env`.
void loss_bind_builtins(lossobj *env) {
    loss_bind_builtin(env, "+", lossbuiltin_plus);
    loss_bind_builtin(env, "display", lossbuiltin_display);
}
