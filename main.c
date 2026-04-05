#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RULES 10
#define MAX_PROD 10
#define MAX_LEN 50

typedef struct {
    char lhs;
    char rhs[MAX_PROD][MAX_LEN];
    int count;
} Rule;

Rule grammar[MAX_RULES];
int ruleCount = 0;

// Remove newline
void clean(char *str) {
    str[strcspn(str, "\n")] = 0;
}

// Add rule (safe input)
void addRule() {
    char input[MAX_LEN];

    printf("\nEnter Non-Terminal (e.g., E): ");
    fflush(stdout);
    fgets(input, MAX_LEN, stdin);
    grammar[ruleCount].lhs = input[0];

    printf("Enter number of productions: ");
    fflush(stdout);
    fgets(input, MAX_LEN, stdin);
    grammar[ruleCount].count = atoi(input);

    for (int i = 0; i < grammar[ruleCount].count; i++) {
        printf("Production %d: ", i + 1);
        fflush(stdout);
        fgets(grammar[ruleCount].rhs[i], MAX_LEN, stdin);
        clean(grammar[ruleCount].rhs[i]);
    }

    ruleCount++;
}

// Print grammar
void printGrammar() {
    printf("\nGrammar:\n");
    for (int i = 0; i < ruleCount; i++) {
        printf("%c -> ", grammar[i].lhs);
        for (int j = 0; j < grammar[i].count; j++) {
            printf("%s", grammar[i].rhs[j]);
            if (j != grammar[i].count - 1)
                printf(" | ");
        }
        printf("\n");
    }
}

// Left recursion removal
void removeLeftRecursion() {
    for (int i = 0; i < ruleCount; i++) {
        char A = grammar[i].lhs;

        char alpha[MAX_PROD][MAX_LEN];
        char beta[MAX_PROD][MAX_LEN];
        int a = 0, b = 0;

        for (int j = 0; j < grammar[i].count; j++) {
            if (grammar[i].rhs[j][0] == A) {
                strcpy(alpha[a++], grammar[i].rhs[j] + 1);
            } else {
                strcpy(beta[b++], grammar[i].rhs[j]);
            }
        }

        if (a > 0) {
            char newLHS = A + 1;

            grammar[i].count = 0;

            for (int j = 0; j < b; j++) {
                sprintf(grammar[i].rhs[grammar[i].count++], "%s%c", beta[j], newLHS);
            }

            grammar[ruleCount].lhs = newLHS;
            grammar[ruleCount].count = 0;

            for (int j = 0; j < a; j++) {
                sprintf(grammar[ruleCount].rhs[grammar[ruleCount].count++], "%s%c", alpha[j], newLHS);
            }

            strcpy(grammar[ruleCount].rhs[grammar[ruleCount].count++], "e");
            ruleCount++;
        }
    }
}

// Left factoring
void leftFactoring() {
    for (int i = 0; i < ruleCount; i++) {
        if (grammar[i].count < 2) continue;

        char prefix = grammar[i].rhs[0][0];
        int same = 1;

        for (int j = 1; j < grammar[i].count; j++) {
            if (grammar[i].rhs[j][0] != prefix) {
                same = 0;
                break;
            }
        }

        if (same) {
            char newLHS = grammar[i].lhs + 2;

            Rule newRule;
            newRule.lhs = newLHS;
            newRule.count = 0;

            for (int j = 0; j < grammar[i].count; j++) {
                strcpy(newRule.rhs[newRule.count++], grammar[i].rhs[j] + 1);
            }

            grammar[i].count = 1;
            sprintf(grammar[i].rhs[0], "%c%c", prefix, newLHS);

            grammar[ruleCount++] = newRule;
        }
    }
}

int main() {
    char input[MAX_LEN];
    int n;

    printf("===== Grammar Optimizer =====\n");

    printf("Enter number of rules: \n> ");
    fflush(stdout);
    fgets(input, MAX_LEN, stdin);

    n = atoi(input);

    for (int i = 0; i < n; i++) {
        addRule();
    }

    printf("\n--- Original Grammar ---");
    printGrammar();

    removeLeftRecursion();
    leftFactoring();

    printf("\n--- Optimized Grammar ---");
    printGrammar();

    return 0;
}