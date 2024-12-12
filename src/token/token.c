/** ===========================================================================
    @ingroup    FrostCompiler
    @addtogroup FrostCompiler_Module Frost_Token

    @package    Frost_Token
    @brief      This module provides functionalities for creating, managing, 
                and deallocating token objects used by the Frost compiler's 
                lexical analyzer.

    @file       token.c
    @headerfile token.h

    @author     Rafael V. Volkmer <rafael.v.volkmer@gmail.com>
    @date       11.12.2024

    @details    The Frost_Token module is responsible for abstracting the logic 
                of constructing and cleaning up token objects, which are 
                fundamental data structures within the lexical analysis stage. 
                Each token contains a lexeme (a sequence of characters extracted 
                from the source code) along with a token type indicating its 
                syntactic category (e.g., identifiers, keywords, punctuation 
                marks). Proper memory management is crucial to avoid leaks and 
                ensure stable compiler operation.

    @note       - Ensure that lexeme memory is properly allocated and freed to 
                  prevent memory leaks.
                - This module depends on `utils.h` for logging and other 
                  utilities, as well as `token.h` for data structure definitions.
 =========================================================================== **/

/* ========================================================================== *\
 *                              INCLUDED FILES                                *
\* ========================================================================== */

/*< Dependencies >*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*< Implements >*/
#include "../../inc/utils.h"
#include "token.h"

/* ========================================================================== *\
 *                      PUBLIC FUNCTIONS IMPLEMENTATION                       *
\* ========================================================================== */

/** ===========================================================================
  @fn       Frost_initToken
  @package  Frost_Token

  @brief    Allocates and initializes a new token object from a given lexeme and
            token type.

  @details  This function attempts to create a new token by allocating memory 
            for a `token_t` structure, copying the provided lexeme, and setting 
            the token type. If the provided lexeme is NULL or if memory 
            allocation fails, it returns NULL. On success, it returns a pointer 
            to a fully initialized token.

  @param    lexeme    [in]: A pointer to the character string representing the 
                           token's lexeme.
  @param    type      [in]: The token type to be assigned, represented by a 
                           `token_type_t` enumeration. This determines the 
                           syntactic category of the token (e.g., identifier, 
                           keyword).

  @return   Pointer to a fully initialized `token_t` object on success.
            NULL if the lexeme is NULL or if a memory allocation error occurs.
 =========================================================================== **/
token_t *Frost_initToken(const char *lexeme, token_type_t type)
{
    /*< Variable Declarations >*/
    token_t *token_out = NULL;
    
    /*< Security Checks >*/
    if (lexeme == NULL)
    {
        LOG_ERROR("Lexeme entry point is NULL.");
        goto end_of_function;
    }
    
    /* Memory Allocation for the Token */
    token_out = (token_t *)calloc(1u, sizeof(token_t));
    if (token_out == NULL)
    {
        LOG_ERROR("Memory allocation failed for token.");
        goto end_of_function;
    }

    /*< Token Initialization >*/
    token_out->type = type;

    token_out->lexeme = strdup(lexeme);
    if (token_out->lexeme == NULL)
    {
        LOG_ERROR("Memory allocation failed for lexeme.");
        free(token_out);
        token_out = NULL;
        goto end_of_function;
    }

    /*< Function Output >*/
end_of_function:
    return token_out;
}

/** ===========================================================================
  @fn       Frost_freeToken
  @package  Frost_Token

  @brief    Frees the memory associated with a token object.

  @details  This function releases memory allocated for the token's lexeme and 
            then frees the token object itself. If the given token pointer is 
            NULL, it logs an error and returns an error code. On success, it 
            returns `FUNCTION_SUCCESS`.

  @param    token     [in]: Pointer to the token to be freed.

  @return   FUNCTION_SUCCESS on successful deallocation.
            -ENOMEM if the token pointer is NULL.
 =========================================================================== **/
int Frost_freeToken(token_t *token)
{
    /*< Variable Declarations >*/
    int ret = FUNCTION_SUCESS;
    
    /*< Start Function Algorithm >*/
    if (token != NULL)
    {
        free(token->lexeme); 
        free(token);

        token->lexeme   = NULL;
        token           = NULL;
    }
    else
    {
        LOG_ERROR("Token entry point is NULL.");
        ret = -ENOMEM;
        goto end_of_function;
    }
    
    /*< Function Output >*/
end_of_function:
    return ret;
}

/*< end of file >*/
