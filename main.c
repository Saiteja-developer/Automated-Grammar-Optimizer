#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_RULES 10
#define MAX_PROD 10
#define MAX_LEN 50

typedef struct {
    char lhs[10];                      // supports E'
    char rhs[MAX_PROD][MAX_LEN];
    int count;
} Rule;

Rule grammar[MAX_RULES];
int ruleCount = 0;
int optimized = 0;

/* ----------- UTIL ----------- */

void clean(char *str) {
    str[strcspn(str, "\n")] = 0;
}

int isValidNonTerminal(char *str) {
    return isupper(str[0]);
}

int ruleExists(char *lhs) {
    for (int i = 0; i < ruleCount; i++) {
        if (strcmp(grammar[i].lhs, lhs) == 0)
            return 1;
    }
    return 0;
}

/* Create E' */
void makePrime(char *base, char *result) {
    sprintf(result, "%s'", base);
}

/* ----------- ADD RULE ----------- */

void addRule() {
    if (ruleCount >= MAX_RULES) {
        printf("Max rules reached!\n");
        return;
    }

    char input[MAX_LEN];

    printf("\nEnter Non-Terminal (A-Z): ");
    fgets(input, MAX_LEN, stdin);
    clean(input);

    if (!isValidNonTerminal(input)) {
        printf("Invalid non-terminal!\n");
        return;
    }

    if (ruleExists(input)) {
        printf("Rule already exists!\n");
        return;
    }

    strcpy(grammar[ruleCount].lhs, input);

    printf("Enter number of productions: ");
    fgets(input, MAX_LEN, stdin);
    int count = atoi(input);

    if (count <= 0 || count > MAX_PROD) {
        printf("Invalid production count!\n");
        return;
    }

    grammar[ruleCount].count = count;

    for (int i = 0; i < count; i++) {
        printf("Production %d: ", i + 1);
        fgets(grammar[ruleCount].rhs[i], MAX_LEN, stdin);
        clean(grammar[ruleCount].rhs[i]);
    }

    ruleCount++;
    optimized = 0;
    printf("Rule added!\n");
}

/* ----------- FILE INPUT ----------- */

void loadFromFile() {
    ruleCount = 0;
    optimized = 0;
    FILE *fp = fopen("input.txt", "r");

    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    char line[MAX_LEN];

    while (fgets(line, MAX_LEN, fp)) {
        clean(line);

        char lhs[10];
        sscanf(line, "%[^-]->", lhs);

        if (!isValidNonTerminal(lhs) || ruleExists(lhs))
            continue;

        strcpy(grammar[ruleCount].lhs, lhs);

        char *rhs = strstr(line, "->") + 2;
        char *token = strtok(rhs, "|");

        int i = 0;
        while (token != NULL) {
            strcpy(grammar[ruleCount].rhs[i++], token);
            token = strtok(NULL, "|");
        }

        grammar[ruleCount].count = i;
        ruleCount++;
    }

    fclose(fp);
    optimized = 0;
    printf("Grammar loaded!\n");
}

/* ----------- PRINT ----------- */

void printGrammar() {
    if (ruleCount == 0) {
        printf("No grammar available!\n");
        return;
    }

    printf("\nGrammar:\n");
    for (int i = 0; i < ruleCount; i++) {
        printf("%s -> ", grammar[i].lhs);
        for (int j = 0; j < grammar[i].count; j++) {
            printf("%s", grammar[i].rhs[j]);
            if (j != grammar[i].count - 1)
                printf(" | ");
        }
        printf("\n");
    }
}

/* ----------- LEFT RECURSION (CORRECT) ----------- */

void removeLeftRecursion() {
    int initialCount = ruleCount;

    for (int i = 0; i < initialCount; i++) {
        char A[10];
        strcpy(A, grammar[i].lhs);

        char alpha[MAX_PROD][MAX_LEN];
        char beta[MAX_PROD][MAX_LEN];
        int a = 0, b = 0;

        for (int j = 0; j < grammar[i].count; j++) {
            if (strncmp(grammar[i].rhs[j], A, strlen(A)) == 0) {
                strcpy(alpha[a++], grammar[i].rhs[j] + strlen(A));
            } else {
                strcpy(beta[b++], grammar[i].rhs[j]);
            }
        }

        if (a > 0) {
            char Aprime[10];
            makePrime(A, Aprime);

            // A -> β A'
            grammar[i].count = 0;
            for (int j = 0; j < b; j++) {
                sprintf(grammar[i].rhs[grammar[i].count++], "%s%s", beta[j], Aprime);
            }

            // A' rule
            strcpy(grammar[ruleCount].lhs, Aprime);
            grammar[ruleCount].count = 0;

            for (int j = 0; j < a; j++) {
                sprintf(grammar[ruleCount].rhs[grammar[ruleCount].count++], "%s%s", alpha[j], Aprime);
            }

            strcpy(grammar[ruleCount].rhs[grammar[ruleCount].count++], "e");
            ruleCount++;
        }
    }
}

/* ----------- LEFT FACTORING ----------- */

void leftFactoring() {
    int initialCount = ruleCount;

    for (int i = 0; i < initialCount; i++) {
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
            char Aprime[10];
            makePrime(grammar[i].lhs, Aprime);

            Rule newRule;
            strcpy(newRule.lhs, Aprime);
            newRule.count = 0;

            for (int j = 0; j < grammar[i].count; j++) {
                strcpy(newRule.rhs[newRule.count++], grammar[i].rhs[j] + 1);
            }

            grammar[i].count = 1;
            sprintf(grammar[i].rhs[0], "%c%s", prefix, Aprime);

            grammar[ruleCount++] = newRule;
        }
    }
}

/* ----------- OPTIMIZE ----------- */

void optimizeGrammar() {
    if (ruleCount == 0) {
        printf("No grammar to optimize!\n");
        return;
    }

    if (optimized) {
        printf("Already optimized!\n");
        return;
    }

    printf("\n--- Original Grammar ---\n");
    printGrammar();

    removeLeftRecursion();
    leftFactoring();

    optimized = 1;

    printf("\n--- Optimized Grammar ---\n");
    printGrammar();
}

/* ----------- MENU ----------- */

void menu() {
    char input[MAX_LEN];
    int choice;

    while (1) {
        printf("\n===== Grammar Optimizer =====\n");
        printf("1. Add Grammar\n");
        printf("2. Load from File\n");
        printf("3. Show Grammar\n");
        printf("4. Optimize Grammar\n");
        printf("5. Exit\n");
        printf("Enter choice: ");

        fgets(input, MAX_LEN, stdin);
        choice = atoi(input);

        switch (choice) {
            case 1: addRule(); break;
            case 2: loadFromFile(); break;
            case 3: printGrammar(); break;
            case 4: optimizeGrammar(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}

/* ----------- MAIN ----------- */

int main() {
    menu();
    return 0;
}