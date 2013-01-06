// Lossy Scheme
//
// Copyright 2013 Martin Pool


#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <talloc.h>


#include "loss.h"


// Construct a new token containing one character
loss_string * loss_string_char(char ch) {
    loss_string *tok = malloc(sizeof *tok);
    tok->n = 1;
    tok->s = strndup(&ch, 1);
    return tok;
}


// Append one character to an existing token.
void loss_string_push(loss_string *tok, char ch) {
    // n is one-based; string indexes are 0-based.
    size_t new_char_index = tok->n;
    size_t new_nul_index = new_char_index + 1;
    size_t new_buf_size = new_nul_index + 1;
    tok->s = realloc(tok->s, new_buf_size);
    tok->s[new_char_index] = ch;
    tok->s[new_nul_index] = 0;
    tok->n++;
}


void loss_string_free(loss_string *tok) {
    free(tok->s);
    free(tok);
}


// Read one token from the input file; return it as a string on the
// heap.  Returns NULL for EOF or error.
loss_string *loss_read_token(FILE *input) {
    int ch;
   
    while (1) {
        ch = fgetc(input);
        if (ch == EOF) {
            if (!feof(input)) {
                fprintf(stderr, "loss: error reading source: %s\n",
                        strerror(errno));
            }
            return NULL;
        } else if (ch == '(' || ch == ')')
            return loss_string_char(ch);
        else if (isspace(ch)) 
            // Just swallow leading whitespace
            ;
        else
            // ch is the start of a non-paren token.
            break;
    }

    // Accumulate characters, starting with ch, until we hit either
    // whitespace or a paren.
    loss_string *tok = loss_string_char(ch);
    while (1) {
        int ch = fgetc(input);
        if (ch == EOF) {
            if (!feof(input)) {
                fprintf(stderr, "loss: error reading source: %s\n",
                        strerror(errno));
                return NULL;
            } else
                return tok;
        } else if (ch == '(' || ch == ')') {
            ungetc(ch, input);
            return tok;
        } else if (isspace(ch))
            return tok;
        else
            loss_string_push(tok, ch);
    }
}


// Read Scheme from the named file; emit a stream of tokens.
void loss_tokenize(FILE *input) {
    loss_string *tok;
    while ((tok = loss_read_token(input)) != NULL) {
        printf("token: %s\n", tok->s);
        loss_string_free(tok);
    }
}


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
    loss_tokenize(input);
    return 0;
}
