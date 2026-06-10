/*
** FREE PROJECT, 2026
** ARGOT
** File description:
** Implementation of argotAddArgument
*/
#include "../include/argot.h"
#include <stdalign.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static void __safe_strncpy(char *dest, const char *src, size_t max_len)
{
    if (!dest || !src || max_len == 0)
        return;
    
    size_t i = 0;
    for (; i < max_len - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

void argotAddArgument(
    argotParser *parser,
    argotType type,
    const char *name,
    const char alias,
    bool multiple_answer
)
{
    size_t nsize = 0;
    argotArg *nargs;
    argotArg *narg;

    if (!parser || !name)
        return;
    nsize = parser->nargs + 1;
    nargs = realloc(parser->args, nsize * sizeof(argotArg));
    if (!nargs)
        return; 
    parser->args = nargs;
    narg = &parser->args[parser->nargs];
    memset(narg, 0, sizeof(argotArg));
    __safe_strncpy(narg->name, name, ARGOT_MAX_ARG_NAME);
    narg->alias = alias;
    narg->type = type;
    narg->founded = false;
    narg->multiple_answer = multiple_answer;
    parser->nargs = nsize;
}
