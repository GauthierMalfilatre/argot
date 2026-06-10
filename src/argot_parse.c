/*
** FREE PROJECT, 2026
** ARGOT
** File description:
** Implementation of argotParse
*/
#include "../include/argot.h"
#include <stdlib.h>
#include <string.h>

static argotArg *find_arg_by_token(argotParser *parser, const char *token)
{
    for (size_t i = 0; i < parser->nargs; i++) {
        if (token[0] == '-' && token[1] != '-' && token[1] == parser->args[i].alias && token[2] == '\0')
            return &parser->args[i];
        if (token[0] == '-' && token[1] == '-' && strcmp(&token[2], parser->args[i].name) == 0)
            return &parser->args[i];
    }
    return NULL;
}

static bool convert_value(argotArg *arg, const char *raw_value)
{
    char *endptr;

    switch (arg->type) {
        case ArgotInt:
            arg->value.v_int = (int)strtol(raw_value, &endptr, 10);
            return *endptr == '\0';
        case ArgotFloat:
            arg->value.v_float = strtof(raw_value, &endptr);
            return *endptr == '\0';
        case ArgotString:
            arg->value.v_str = (char *)raw_value;
            return true;
        case ArgotChar:
            if (raw_value[0] != '\0' && raw_value[1] == '\0') {
                arg->value.v_chr = raw_value[0];
                return true;
            }
            return false;
        case ArgotLong:
            arg->value.v_long = strtol(raw_value, &endptr, 10);
            return *endptr == '\0';
        case ArgotSize:
            arg->value.v_size = (size_t)strtoull(raw_value, &endptr, 10);
            return *endptr == '\0';
        case ArgotDouble:
            arg->value.v_double = strtod(raw_value, &endptr);
            return *endptr == '\0';
        default:
            return false;
    }
}

static bool add_to_multiple(argotArg *arg, const char *raw_value)
{
    size_t count = 0;
    void ** new_array = NULL;

    if (arg->value.v_array)
        while (arg->value.v_array[count] != NULL) count++;
    new_array = realloc(arg->value.v_array, (count + 2) * sizeof(void *));
    if (!new_array)
        return false;
    arg->value.v_array = new_array;
    arg->value.v_array[count] = strdup(raw_value);
    arg->value.v_array[count + 1] = NULL;
    return arg->value.v_array[count] != NULL;
}

bool argotParse(argotParser *parser, int argc, char *const *argv)
{
    argotArg *arg = NULL;

    if (!parser || argc < 1 || !argv)
        return false;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-')
            continue;
        arg = find_arg_by_token(parser, argv[i]);
        if (!arg)
            return false;
        if (arg->multiple_answer) {
            while (i + 1 < argc && argv[i + 1][0] != '-') {
                if (!add_to_multiple(arg, argv[i + 1]))
                    return false;
                i++;
            }
        } else {
            if (i + 1 >= argc)
                return false;
            if (!convert_value(arg, argv[i + 1]))
                return false;
            i++;
        }
        arg->founded = true;
    }
    return true;
}
