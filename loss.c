// Lossy Scheme
//
// Copyright 2013 Martin Pool


#include <ctype.h>
#include <errno.h>
#include <stdio.h>
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

    loss_object *parsed;
    while ((parsed = loss_parse(input, false))) {
        loss_print_object(parsed, false, stdout);
        fputs("\n", stdout);
    }

    return 0;
}
