#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

// Define color codes for Windows console
#define RED 12
#define GREEN 10
#define BLUE 9
#define RESET 7

// Function to set the color of the console text
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Function to push a value onto the stack
void push(float stack[], float value, int *currStack) {
    int i = *currStack;

    // Shift all elements up by one position to make room for the new value
    while (i != 0) {
        stack[i] = stack[i-1];
        i--;
    }

    // Insert the new value at the bottom of the stack
    stack[0] = value;
    *currStack += 1;
}

// Function to pop values from the stack and perform the specified operation
int pop(float stack[], char operation, int *currStack) {
    int i;

    // Perform the operation based on the provided operator
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
                // Handle division by zero
                setColor(RED);
                printf("\t\t\tError: Division by zero.\n");
                setColor(RESET);
                return -1;
            }
            break;
        default:
            // Handle invalid operator
            setColor(RED);
            printf("\t\t\tInvalid character.\n");
            setColor(RESET);
            return -1;
    }

    // Shift remaining elements down by one position
    for (i = 1; i < *currStack - 1; i++) {
        stack[i] = stack[i + 1];
    }

    // Decrease stack size
    *currStack -= 1;
    return 0;
}

// Function to decode and evaluate the RPN expression
int decode(char *input, float *outval) {
    int currStack = 0;
    char *token;
    float stack[100];  // assuming a max stack size of 100 for simplicity

    // Tokenize the input string by spaces
    token = strtok(input, " ");
    while (token != NULL) {
        // Check if the token is a number
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            // Push the number onto the stack
            push(stack, atof(token), &currStack);
        } else if (strlen(token) == 1 && strchr("+-*/", token[0])) {
            // Ensure there are at least two operands on the stack
            if (currStack < 2) {
                setColor(RED);
                printf("\t\t\tError: Invalid RPN expression.\n");
                setColor(RESET);
                return -1;
            }
            // Pop and perform the operation
            if (pop(stack, token[0], &currStack) == -1) {
                return -1; // Stop processing if an error occurs in pop
            }
        } else {
            // Handle invalid token
            setColor(RED);
            printf("\t\t\tInvalid token: %s\n", token);
            setColor(RESET);
            return -1;
        }
        token = strtok(NULL, " ");
    }

    // Check if the stack has exactly one element after evaluation
    if (currStack != 1) {
        setColor(RED);
        printf("\t\t\tError: Invalid RPN expression.\n");
        setColor(RESET);
        return -1;
    }

    // Set the output value to the result
    *outval = stack[0];
    return 0;
}

int main() {
    char input[256];
    float result;

    // Print the header of the calculator
    setColor(GREEN);
    printf("\t\t=================================\n");
    printf("\t\t|\t RPN Calculator\t\t|\n");
    printf("\t\t=================================\n");
    setColor(RESET);

    // Instructions for the user
    setColor(RED);
    printf("\t ------------------------------------------------\n");
    printf("\t|                Instructions                    |\n");
    printf("\t|");
    setColor(RESET);
    printf("  1. Enter your RPN expression with spaces.     ");
    setColor(RED);
    printf("|\n");
    printf("\t|");
    setColor(RESET);
    printf("     separating each number and operator.       ");
    setColor(RED);
    printf("|\n");
    printf("\t|");
    setColor(RESET);
    printf("  2. You can use the operators + , - , * and /  ");
    setColor(RED);
    printf("|\n");
    printf("\t|            -> Enter 'x' to exit <-             |\n");
    printf("\t ------------------------------------------------\n");
    setColor(RESET);

    while (1) {
        // Prompt the user for input
        printf("\n\n\t=> Enter an RPN expression: ");
        fgets(input, sizeof(input), stdin);

        // Remove the newline character from the input
        input[strcspn(input, "\n")] = 0;

        // Check if the user wants to exit
        if (strcmp(input, "x") == 0 || strcmp(input, "X") == 0) {
            setColor(GREEN);
            printf("\t\tExiting RPN Calculator. Goodbye!\n");
            setColor(RESET);
            break;
        }

        // Decode and evaluate the RPN expression
        if (decode(input, &result) == 0) {
            // Print the result
            setColor(BLUE);
            printf("\t\t    ------------------------\n");
            printf("\t\t      The answer is: %.3f\n", result);
            printf("\t\t    ------------------------\n");
            setColor(RESET);
        } else {
            // Print an error message if the evaluation fails
            setColor(RED);
            printf("\t\t\tError in processing the RPN expression.\n");
            setColor(RESET);
        }
    }

    return 0;
}