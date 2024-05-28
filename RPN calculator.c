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

    return 0;
}