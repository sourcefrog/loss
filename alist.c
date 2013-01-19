#include <assert.h>
#include <string.h>

#include "loss.h"


void loss_alist_append(loss_object *alist, loss_object *name, loss_object *value) {
    loss_object *pair = loss_cons_new_pair(name, value);
    loss_list_append(alist, pair);
}


loss_object *loss_alist_lookup_sz(
    const loss_object *alist,
    const char *name) {
    if (!alist)
        return NULL;
    assert(alist->type == CONS);
    // First element in the list; should be a pair.
    loss_object *hd = alist->val.cons.hd;
    assert(hd->type == CONS);
    // alists should only contain strings.
    loss_object *key = hd->val.cons.hd;
    assert(key);
    assert(key->type == STRING);
    if (!strcmp(key->val.string, name))
        return hd->val.cons.tl;
    else
        return loss_alist_lookup_sz(alist->val.cons.tl, name);
}