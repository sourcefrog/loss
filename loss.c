// Lossy Scheme
//
// Copyright 2013 Martin Pool


#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "loss.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: loss FILENAME\n");
        return 1;
    }

    FILE *input = loss_open_input(argv[1]);
    if (!input)
        return 2;

    lossobj *env = loss_cons_new();
    loss_bind_builtins(env);

    lossobj *parsed;
    while ((parsed = loss_parse(input, false))) {
        lossobj *result;
        result = loss_eval(env, parsed);
        if (input == stdin && isatty(0)) {
            loss_print_object(result, false, stdout);
            fputs("\n", stdout);
        }
    }

    return 0;
}
