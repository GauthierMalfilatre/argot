/*
** FREE PROJECT, 2026
** ARGOT
** File description:
** Getters implementation for argot lib
*/

#include "../include/argot.h"
#include <string.h>

static argotArg *find_arg(argotParser *parser, const char *name)
{
    if (!parser || !name)
        return NULL;
    for (size_t i = 0; i < parser->nargs; i++) {
        if (strcmp(parser->args[i].name, name) == 0)
            return &parser->args[i];
    }
    return NULL;
}

int argotGetInt(argotParser *parser, const char *name, int default_v)
{
    argotArg *arg = find_arg(parser, name);
    if (!arg || !arg->founded)
        return default_v;
    return arg->value.v_int;
}

float argotGetFloat(argotParser *parser, const char *name, float default_v)
{
    argotArg *arg = find_arg(parser, name);
    if (!arg || !arg->founded)
        return default_v;
    return arg->value.v_float;
}

char *argotGetStr(argotParser *parser, const char *name, char *default_v)
{
    argotArg *arg = find_arg(parser, name);
    if (!arg || !arg->founded)
        return default_v;
    return arg->value.v_str;
}

char argotGetChr(argotParser *parser, const char *name, char default_v)
{
    argotArg *arg = find_arg(parser, name);
    if (!arg || !arg->founded)
        return default_v;
    return arg->value.v_chr;
}

long argotGetLong(argotParser *parser, const char *name, long default_v)
{
    argotArg *arg = find_arg(parser, name);
    if (!arg || !arg->founded)
        return default_v;
    return arg->value.v_long;
}

size_t argotGetSize(argotParser *parser, const char *name, size_t default_v)
{
    argotArg *arg = find_arg(parser, name);
    if (!arg || !arg->founded)
        return default_v;
    return arg->value.v_size;
}

double argotGetDouble(argotParser *parser, const char *name, double default_v)
{
    argotArg *arg = find_arg(parser, name);
    if (!arg || !arg->founded)
        return default_v;
    return arg->value.v_double;
}
