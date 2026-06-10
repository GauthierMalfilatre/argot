/*
** FREE PROJECT, 2026
** ARGOT
** File description:
** Header file for argot lib
*/

#ifndef ARGOT_H
    #define ARGOT_H

    #include <stddef.h>
    #include <stdbool.h>

    #define ARGOT_MAX_ARG_NAME 16
    #define ARGOT_MAX_ALIAS     4

///////////////////////////////////////////////////////////////////////////////
/**
 * @enum  argot_type_e
 *
 * @brief Types of arguments
 */
///////////////////////////////////////////////////////////////////////////////
typedef enum argot_type_e {

    ArgotInt,        //!< Matches a standard integer (int)
    ArgotFloat,      //!< Matches a floating-point number (float)
    ArgotString,     //!< Matches a raw string literal (char *)
    ArgotChar,       //!< Matches a single character (char)
    ArgotLong,       //!< Matches a long integer (long)
    ArgotSize,       //!< Matches a size variable (size_t)
    ArgotDouble,     //!< Matches a high-precision float (double)

    ArgotTypeCount,  //!< The count of args (always last!!!)

} argotType;
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/**
 * @struct argot_arg_s
 *
 * @brief  "Hidden" struct to store arguments options
 *
 * @note   If `multiple_answer` is true, the `value.v_array` field will contain
 * a dynamically allocated, NULL-terminated array of pointers to parsed values.   
 */
///////////////////////////////////////////////////////////////////////////////
typedef struct argot_arg_s  {

    char      name[ARGOT_MAX_ARG_NAME];  //!< The name (like --verbose)
    char      alias[ARGOT_MAX_ALIAS];    //!< The alias (like -v)
    bool      founded;                   //!< Is founded ?
    argotType type;                      //!< The type of the argument
    union {
        int      v_int;                  //!< Parsed int value
        float    v_float;                //!< Parsed float value
        char    *v_str;                  //!< Duplicated string value
        char     v_chr;                  //!< Parsed single character value
        long     v_long;                 //!< Parsed long integer value
        size_t   v_size;                 //!< Parsed size_t value
        double   v_double;               //!< Parsed double value
        void   **v_array;                //!< NULL-terminated array of parsed values (if multiple_answer)
    } value;                             //!< The actual value
    bool      multiple_answer;           //!< Allow multiple answer ?

} argotArg;
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/**
 * @struct argot_opt_s
 *
 * @brief  Big struct to store parameters
 */
///////////////////////////////////////////////////////////////////////////////
typedef struct argot_opt_s {

    size_t    nargs;  //!< The number of arguments
    argotArg *args;   //!< The arguments structs in a raw array

} argotParser;
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Registers a new argument configuration into the parser context.
 */
void argotAddArgument(argotParser *parser, argotType type, const char *name,
    const char c, bool multiple_answer);

/**
 * @brief Processes command-line inputs against registered arguments.
 */
bool argotParse(argotParser *parser, int argc, char *const *argv);

/**
 * @name Argument Getters
 * @brief Safely retrieve values from parsed arguments. Return default_v if not found.
 * @{
 */
int    argotGetInt(argotParser *parser, const char *name, int default_v);
float  argotGetFloat(argotParser *parser, const char *name, float default_v);
char  *argotGetStr(argotParser *parser, const char *name, char *default_v);
char   argotGetChr(argotParser *parser, const char *name, char default_v);
long   argotGetLong(argotParser *parser, const char *name, long default_v);
size_t argotGetSize(argotParser *parser, const char *name, size_t default_v);
double argotGetDouble(argotParser *parser, const char *name, double default_v);
/** @} */

#endif /* ARGOT_H */
