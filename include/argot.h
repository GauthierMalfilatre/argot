/*
** FREE PROJECT, 2026
** ARGOT
** File description:
** Header file for argot lib
*/
#ifndef ARGOT_H
    #define ARGOT_H
    #include <stddef.h>
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

    ArgotInt,     // Int
    ArgotFloat,   // Float
    ArgotString,  // String (char *)
    ArgotChar,    // Char
    ArgotLong,    // Long
    ArgotSize,    // Size
    ArgotDouble,  // Double

    ArgotTypeCount,  // The count of args (always last!!!)

} argotType;
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/**
 * @struct argot_arg_s
 *
 * @brief  "Hidden" struct to store arguments options
 *
 * @note   If `multiple_answer` is true, the `founded` value would be
 *         a allocated array terminating by NULL   
 */
///////////////////////////////////////////////////////////////////////////////
typedef struct argot_arg_s  {

    char      name[ARGOT_MAX_ARG_NAME];  //!< The name (like --verbose)
    char      alias[ARGOT_MAX_ALIAS];    //!< The alias (like -v)
    void     *founded;                   //!< The value founded (NULL if not found)
    bool      multiple_answer;           //!< Allow multiple answer ?
    argotType type;                      //!< The type of the argument

} ArgotArg;
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
    ArgotArg *args;   //!< The arguments structs in a raw array

} argotParser;
///////////////////////////////////////////////////////////////////////////////

#endif /* ARGOT_H */
