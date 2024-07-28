#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

enum token_id {
    NUMBER,
    OPERATOR
};

struct token {
    enum token_id id;
    double value; // operators will be here too
};

int main(void) {
    puts("Enter an expression.");

    char expr[128];
    fgets(expr, sizeof expr, stdin);
    *strchr(expr, '\n') = 0; // string limit

    struct token tokens[64]; // array of tokens
    int toklen = 0; // len of array

    // Get all tokens (separator = space)
    for (char *tok = strtok(expr, " "); tok; tok = strtok(0, " ")) {
        if (isdigit(tok[0])) { // if number
            double d;
            sscanf(tok, "%lf", &d); // convert string to double
            
            tokens[toklen++] = (struct token) {
                NUMBER,
                d
            };
        } else { // if operator
            tokens[toklen++] = (struct token) {
                OPERATOR,
                tok[0] // select operator (1 symbol)
            };
        }
    }

    double stack[64]; // stack for counting
    int stacklen = 0;

    // Do Reverse Polish Notation
    for (int i = 0; i < toklen; i++) { // for each token
        if (tokens[i].id == NUMBER) { // if number
            stack[stacklen++] = tokens[i].value; // push to stack
        } else { // if operator
            switch ((char) tokens[i].value) {
                case '+':
                    stack[stacklen-2] += stack[stacklen-1]; // add
                    break;
                case '-':
                    stack[stacklen-2] -= stack[stacklen-1]; // sub
                    break;
                case '*':
                    stack[stacklen-2] *= stack[stacklen-1]; // mul
                    break;
                case '/':
                    stack[stacklen-2] /= stack[stacklen-1]; // div
            }
            stacklen--;
        }
    }

    printf("Value: %g\n", stack[0]);

    return 0;
}