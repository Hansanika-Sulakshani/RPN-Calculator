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