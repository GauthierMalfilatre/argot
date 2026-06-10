/*
** FREE PROJECT, 2026
** ARGOT
** File description:
** Main test file for argot lib
*/

#include "../include/argot.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_test_banner(const char *title)
{
    printf("\n==================================================\n");
    printf(" TESTING: %s\n", title);
    printf("==================================================\n");
}

int main(void)
{
    argotParser parser = {0, NULL};

    // 1. Enregistrement des arguments
    argotAddArgument(&parser, ArgotInt, "port", 'p', false);
    argotAddArgument(&parser, ArgotFloat, "timeout", 't', false);
    argotAddArgument(&parser, ArgotString, "output", 'o', false);
    argotAddArgument(&parser, ArgotChar, "mode", 'm', false);
    argotAddArgument(&parser, ArgotLong, "seed", 's', false);
    argotAddArgument(&parser, ArgotSize, "max-clients", 'c', false);
    argotAddArgument(&parser, ArgotDouble, "factor", 'f', false);

    // On cherche l'argument "libs" pour activer le mode multiple
    argotAddArgument(&parser, ArgotString, "libs", 'l', true);

    // -------------------------------------------------------------------------
    // TEST 1 : Cas nominal parfait avec alias et longues options mélangés
    // -------------------------------------------------------------------------
    print_test_banner("Nominal Case (Mixed long/short options)");
    
    char *argv1[] = {
        "./my_program",
        "-p", "8080",
        "--timeout", "42.42",
        "-o", "log.txt",
        "--mode", "X",
        "-s", "1234567890",
        "--max-clients", "500",
        "-f", "0.00001"
    };
    int argc1 = sizeof(argv1) / sizeof(argv1[0]);

    if (argotParse(&parser, argc1, argv1)) {
        printf("[SUCCESS] Parsing succeeded!\n");
        printf("  port (expected 8080)        : %d\n", argotGetInt(&parser, "port", 3000));
        printf("  timeout (expected 42.42)    : %f\n", argotGetFloat(&parser, "timeout", 1.0f));
        printf("  output (expected log.txt)   : %s\n", argotGetStr(&parser, "output", "stdout"));
        printf("  mode (expected X)           : %c\n", argotGetChr(&parser, "mode", 'D'));
        printf("  seed (expected 1234567890)  : %ld\n", argotGetLong(&parser, "seed", 0));
        printf("  max-clients (expected 500)  : %zu\n", argotGetSize(&parser, "max-clients", 10));
        printf("  factor (expected 0.00001)   : %f\n", argotGetDouble(&parser, "factor", 1.0));
    } else {
        printf("[FAILURE] Parsing failed on valid input!\n");
    }

    // -------------------------------------------------------------------------
    // TEST 2 : Test des valeurs par défaut (On passe un argv vide)
    // -------------------------------------------------------------------------
    print_test_banner("Fallback to Default Values");

    char *argv2[] = {"./my_program"};
    argotParser parser_empty = {0, NULL}; // Nouveau parser propre
    argotAddArgument(&parser_empty, ArgotInt, "port", 'p', false);
    argotAddArgument(&parser_empty, ArgotString, "output", 'o', false);

    if (argotParse(&parser_empty, 1, argv2)) {
        printf("[SUCCESS] Empty parsing succeeded!\n");
        printf("  port (expected 80)          : %d\n", argotGetInt(&parser_empty, "port", 80));
        printf("  output (expected index.html): %s\n", argotGetStr(&parser_empty, "output", "index.html"));
    } else {
        printf("[FAILURE] Empty parsing failed!\n");
    }

    // -------------------------------------------------------------------------
    // TEST 3 : Le mode glouton (multiple_answer)
    // -------------------------------------------------------------------------
    print_test_banner("Multiple Answer Greedy Mode (-l aaa bbb ccc -p 42)");

    char *argv3[] = {
        "./my_program",
        "-l", "kronknet", "raytracer", "bcs_ecs",
        "-p", "42"
    };
    int argc3 = sizeof(argv3) / sizeof(argv3[0]);

    // On reset l'état du premier parser pour re-tester
    for (size_t i = 0; i < parser.nargs; i++) {
        parser.args[i].founded = false;
    }

    if (argotParse(&parser, argc3, argv3)) {
        printf("[SUCCESS] Multiple parsing succeeded!\n");
        printf("  port (expected 42) : %d\n", argotGetInt(&parser, "port", 3000));
        
        // Extraction manuelle du tableau v_array pour le test
        for (size_t i = 0; i < parser.nargs; i++) {
            if (strcmp(parser.args[i].name, "libs") == 0 && parser.args[i].founded) {
                printf("  libs found components :\n");
                char **arr = (char **)parser.args[i].value.v_array;
                if (arr) {
                    for (int j = 0; arr[j] != NULL; j++) {
                        printf("    -> [%d] : %s\n", j, arr[j]);
                    }
                } else {
                    printf("    -> Array is NULL!\n");
                }
            }
        }
    } else {
        printf("[FAILURE] Multiple parsing failed!\n");
    }

    // -------------------------------------------------------------------------
    // TEST 4 : Cas d'erreurs (Validation des types)
    // -------------------------------------------------------------------------
    print_test_banner("Error Handling (Type Mismatch)");

    char *argv4[] = {
        "./my_program",
        "-p", "8080a" // Pas un int valide à cause du 'a'
    };
    
    for (size_t i = 0; i < parser.nargs; i++) {
        parser.args[i].founded = false;
    }

    if (!argotParse(&parser, 3, argv4)) {
        printf("[SUCCESS] Library correctly detected type mismatch for '8080a'!\n");
    } else {
        printf("[FAILURE] Library accepted an invalid integer value!\n");
    }

    argotClear(&parser);
    argotClear(&parser_empty);

    printf("\n==================================================\n");
    printf(" END OF TESTS\n");
    printf("==================================================\n");

    return 0;
}
