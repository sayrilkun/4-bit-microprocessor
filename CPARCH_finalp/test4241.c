#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "4241.h"

void print_results(processor * p) {
    printf("Final state:\n");
    printf("r0: %X\tr1: %X\n", p->r0, p->r1);

    printf("Memory:\n");
    int i;
    for (i = 0; i < 16; ++i) {
        printf("%X ", p->mem[i]);
        if ((i + 1) % 4 == 0) {
            printf("\n");
        }
    }
}

byte * read_program_file(FILE * f) {
    byte * mem = malloc(sizeof(byte) * 16);
    if (mem == NULL) {
        return NULL;
    }
    memset(mem, 0, 16);

    int i;
    char hex[2] = "\0\0";
    for (i = 0; i < 16; ++i) {
        if (!fread(hex, 1, 1, f)) {
            break;
        } else if (isxdigit(hex[0])) {
            mem[i] = (byte)strtol(hex, NULL, 16);
        } else {
            i--;
            continue;
        }
    }

    return mem;
}

int main(int argc, char * argv[]) {

    byte * memory;

    if (argc > 1) {
        char * filename = argv[1];
        FILE * file = fopen(filename, "r");
        memory = read_program_file(file);
        fclose(file);
    } else {
        memory = read_program_file(stdin);        
    }

    processor * results;
    results = run(memory);

    if (results == NULL) {
        printf("An error occurred running the program.\n");
    } else {
        print_results(results);
    }

    free(memory);
    free(results);

    return 0;
}