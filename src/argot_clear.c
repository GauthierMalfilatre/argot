/*
** FREE PROJECT, 2026
** ARGOT
** File description:
** Implementation of argotFree
*/

#include "../include/argot.h"
#include <stdlib.h>

void argotClear(argotParser *parser)
{
    if (!parser || !parser->args)
        return;
    for (size_t i = 0; i < parser->nargs; i++) {
        if (parser->args[i].multiple_answer && parser->args[i].value.v_array) {
            char **arr = (char **)parser->args[i].value.v_array;
            for (int j = 0; arr[j] != NULL; j++) {
                free(arr[j]);
            }
            free(arr);
            parser->args[i].value.v_array = NULL;
        }
    }
    free(parser->args);
    parser->args = NULL;
    parser->nargs = 0;
}