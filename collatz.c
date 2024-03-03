#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct Edge {
    struct Node* destination;
    struct Edge* next;
} Edge;

typedef struct Node {
    int num;
    struct Edge* edges;
} Node;

void calculate_collatz(FILE *dot, long num) {
    long previous_num = num;

    while (num != 1) {
        if (num % 2 == 0)
            num /= 2;
        else   
            num = num * 3 + 1;

        fprintf(dot, "  %ld -> %ld;\n", previous_num, num);
        previous_num = num;
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        exit(1);
    }

    char* endptr;
    long num = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0') {
        printf("Invalid input: %s is not a number\n", argv[1]);
        exit(1);
    }

    char *output_file = "collatz.dot";

    FILE *dot = fopen(output_file, "w");

    if (dot == NULL) {
        fprintf(stderr, "ERROR: could not open file `%s`: %s", output_file ,strerror(errno));
        exit(1);
    }

    fprintf(dot, "digraph Collatz {\n");
    calculate_collatz(dot, num);
    fprintf(dot, "}\n");

    fclose(dot);
}