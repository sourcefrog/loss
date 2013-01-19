#include <assert.h>
#include <string.h>

#include "loss.h"


void loss_alist_append(lossobj *alist, lossobj *name, lossobj *value) {
    lossobj *pair = loss_cons_new_pair(name, value);
    loss_list_append(alist, pair);
}


lossobj *loss_alist_lookup_sz(
    const lossobj *alist,
    const char *name) {
    if (!alist)
        return NULL;
    assert(alist->type == CONS);
    // First element in the list; should be a pair.
    lossobj *hd = alist->val.cons.hd;
    assert(hd->type == CONS);
    // alists should only contain strings.
    lossobj *key = hd->val.cons.hd;
    assert(key);
    assert(key->type == STRING);
    if (!strcmp(key->val.string, name))
        return hd->val.cons.tl;
    else
        return loss_alist_lookup_sz(alist->val.cons.tl, name);
}