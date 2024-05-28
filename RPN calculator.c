#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>


void push(float stack[], float value, int *currStack) {
    int i = *currStack;

    while (i != 0) {
        stack[i] = stack[i-1];
        i--;
    }

    stack[0] = value;
    *currStack += 1;
}

int pop(float stack[], char operation, int *currStack) {
    int i;

    switch (operation) {
        case '+':
            stack[0] = stack[1] + stack[0];
            break;
        case '-':
            stack[0] = stack[1] - stack[0];
            break;
        case '*':
            stack[0] = stack[1] * stack[0];
            break;
        case '/':
            if (stack[0] != 0) {
                stack[0] = stack[1] / stack[0];
            } else {
                printf("\t\t\tError: Division by zero.\n");
                return -1;
            }
            break;
        default:
            printf("\t\t\tInvalid character.\n");
            return -1;
    }

    for (i = 1; i < *currStack - 1; i++) {
        stack[i] = stack[i + 1];
    }

    *currStack -= 1;
    return 0;
}

int decode(char *input, float *outval) {
    int currStack = 0;
    char *token;
    float stack[100]; 

    token = strtok(input, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(stack, atof(token), &currStack);
        } else if (strlen(token) == 1 && strchr("+-*/", token[0])) {
            if (currStack < 2) {
                printf("\t\t\tError: Invalid RPN expression.\n");
                return -1;
            }
            if (pop(stack, token[0], &currStack) == -1) {
                return -1;
            }
        } else {
            printf("\t\t\tInvalid token: %s\n", token);
            return -1;
        }
        token = strtok(NULL, " ");
    }

    if (currStack != 1) {
        printf("\t\t\tError: Invalid RPN expression.\n");
        return -1;
    }

    *outval = stack[0];
    return 0;
}

int main() {
    char input[256];
    float result;

    printf("\t\t=================================\n");
    printf("\t\t|\t RPN Calculator\t\t|\n");
    printf("\t\t=================================\n");

    printf("\t ------------------------------------------------\n");
    printf("\t|                Instructions                    |\n");
    printf("\t|");
    printf("  1. Enter your RPN expression with spaces.     ");
    printf("|\n");
    printf("\t|");
    printf("     separating each number and operator.       ");
    printf("|\n");
    printf("\t|");
    printf("  2. You can use the operators + , - , * and /  ");
    printf("|\n");
    printf("\t|            -> Enter 'x' to exit <-             |\n");
    printf("\t ------------------------------------------------\n");

    while (1) {
        printf("\n\n\t=> Enter an RPN expression: ");
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "x") == 0 || strcmp(input, "X") == 0) {
            printf("\t\tExiting RPN Calculator. Goodbye!\n");
            break;
        }

        if (decode(input, &result) == 0) {
            printf("\t\t    ------------------------\n");
            printf("\t\t      The answer is: %.3f\n", result);
            printf("\t\t    ------------------------\n");
        } else {
            printf("\t\t\tError in processing the RPN expression.\n");
        }
    }

    return 0;
}