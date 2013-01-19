// Lossy Scheme
//
// Copyright 2013 Martin Pool


#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <talloc.h>


#include "loss.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: loss FILENAME\n");
        return 1;
    }
    const char *filename = argv[1];

    FILE *input = fopen(filename, "r");
    if (!input) {
        fprintf(stderr, "loss: couldn't open %s: %s\n",
                filename, strerror(errno));
        return 2;
    }
    loss_object *parsed = loss_parse(input, false);
    loss_print_object(parsed, false, stdout);
    fputs("\n", stdout);

    return 0;
}
