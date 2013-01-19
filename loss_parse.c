// Lossy Scheme
//
// Copyright 2013 Martin Pool


#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "loss.h"

const char *program = "loss_parse";


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s FILENAME\n", program);
        return 1;
    }
    const char *filename = argv[1];

    FILE *input = fopen(filename, "r");
    if (!input) {
        fprintf(stderr, "%s: couldn't open %s: %s\n",
                program, filename, strerror(errno));
        return 2;
    }
    loss_object *parsed = loss_parse(input, false);
    loss_print_object(parsed, stdout);
    fputs("\n", stdout);

    return 0;
}
