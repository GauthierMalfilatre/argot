/*
** FREE PROJECT, 2026
** ARGOT
** File description:
** Argot init impl
*/
#include "../include/argot.h"

void argot_init(argotParser *parser)
{
    if (!parser) {
        return;
    }
    parser->nargs = 0;
    parser->args = NULL;
}
