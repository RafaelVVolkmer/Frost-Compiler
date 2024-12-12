/** ===========================================================================
    @ingroup    FrostCompiler
    @addtogroup FrostCompiler_Module Frost_Lexer

    @package    Frost_Lexer
    @brief      This module provides functionalities for lexical analysis in
                the Frost Compiler, including tokenization, identifier parsing,
                and whitespace handling.

    @file       lexer.c
    @headerfile lexer.h

    @author     Rafael V. Volkmer <rafael.v.volkmer@gmail.com>
    @date       11.12.2024

    @details    The Frost Lexer module is responsible for breaking down the 
                source code into meaningful tokens, which are used in subsequent 
                stages of the Frost Compiler, such as parsing and semantic 
                analysis. It supports functionality for handling various token 
                types, whitespace skipping, and identifier parsing.

    @note       - Ensure that the source code input to the lexer is properly
                  formatted to avoid errors during tokenization.
                - This module is tightly coupled with the `Frost_Token` module
                  for creating and managing token objects.
 =========================================================================== **/

/* ========================================================================== *\
 *                              INCLUDED FILES                                *
\* ========================================================================== */

/*< Dependencies >*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

/*< Implements >*/
#include "lexer.h"
#include "../../inc/utils.h"

/* ========================================================================== *\
 *                      PRIVATE FUNCTIONS IMPLEMENTATION                      *
\* ========================================================================== */

/** ============================================================================
  @fn       Frost_initLexer
  @package  Frost_Lexer

  @brief    Initializes a lexer structure from the given source string.

  @details  Allocates memory for a lexer object and initializes its internal
            fields based on the provided source string. If the source is NULL,
            or memory allocation fails, it returns NULL.

  @param    source    [in]:   String containing the source code to be tokenized.

  @return   Pointer to a newly created lexer object on success.
            NULL if the source is NULL or memory allocation fails.
 =========================================================================== **/
lexer_t *Frost_initLexer(char *source)
{
    /*< Variable Declarations >*/
    lexer_t *lexer_out = NULL;

    /*< Security Checks >*/
    if (source == NULL)
    {
        LOG_ERROR("Source entry point is NULL.");
        goto end_of_function;
    }

    /*< Allocate Memory >*/
    lexer_out = (lexer_t *)calloc(1u, sizeof(lexer_t));
    if (lexer_out == NULL)
    {
        LOG_ERROR("Memory allocation failed for lexer.");
        goto end_of_function;
    }

    /*< Start Function Algorithm >*/
    lexer_out->source       = source;
    lexer_out->source_size  = strlen(source);
    lexer_out->index        = 0u;
    lexer_out->current_char = (char)(source[lexer_out->index]);

   /*< Function Output >*/
end_of_function:
    return lexer_out;
}

/** ============================================================================
  @fn       Frost_freeLexer
  @package  Frost_Lexer

  @brief    Frees the memory associated with a lexer object.

  @details  Releases all memory allocated for the lexer, including its source
            and the lexer itself. If the lexer is NULL, returns an error code.

  @param    lexer     [in]:   Pointer to the lexer to be freed.

  @return   FUNCTION_SUCCESS on success.
            -ENOMEM if the lexer is NULL.
 =========================================================================== **/
int Frost_freeLexer(lexer_t *lexer)
{
    /*< Variable Declarations >*/
    int ret = FUNCTION_SUCESS;
    
    /*< Start Function Algorithm >*/
    if (lexer != NULL)
    {
        free(lexer->source); 
        free(lexer);

        lexer->source   = NULL;
        lexer           = NULL;
    }
    else
    {
        LOG_ERRROR("Lexer entry point is NULL.");
        ret = -ENOMEM;
        goto end_of_function;
    }
    
    /*< Function Output >*/
end_of_function:
    return ret;
}

/** ============================================================================
  @fn       Frost_lexerAdvance
  @package  Frost_Lexer

  @brief    Advances the lexer to the next character in the source string.

  @details  Moves the lexer's index forward and updates its current character.
            If the lexer is NULL, returns an error code.

  @param    lexer     [in]:   Pointer to the lexer to advance.

  @return   FUNCTION_SUCCESS on success.
            -ENOMEM if the lexer is NULL.
 =========================================================================== **/
int Frost_lexerAdvance(lexer_t *lexer)
{
    /*< Variable Declarations >*/
    int ret = FUNCTION_SUCESS;

    /*< Security Checks >*/
    if (lexer == NULL)
    {
        LOG_ERROR("Lexer entry point is NULL.");
        ret = -ENOMEM;
        goto end_of_function;
    }

    /*< Start Function Algorithm >*/
    if ( (lexer->index < lexer->source_size) && (lexer->current_char != '\0') )
    {
        lexer->index++;
        lexer->current_char = lexer->source[lexer->index];
    }

    /*< Function Output >*/
end_of_function:
    return ret;
}

/** ============================================================================
  @fn       Frost_lexerAdvanceWith
  @package  Frost_Lexer

  @brief    Advances the lexer and returns the provided token.

  @details  Advances the lexer to the next character and returns the given token.
            If the lexer or token is NULL, returns NULL.

  @param    lexer     [in]:   Pointer to the lexer to advance.
  @param    token     [in]:   Pointer to the token to return.

  @return   Pointer to the given token on success.
            NULL if the lexer or token is NULL.
 =========================================================================== **/
token_t *Frost_lexerAdvanceWith(lexer_t *lexer, token_t *token)
{
    /*< Variable Declarations >*/
    token_t *token_out = NULL;

    /*< Security Checks >*/
    if (lexer == NULL)
    {
        LOG_ERROR("Lexer entry point is NULL.");
        goto end_of_function;
    }

    if (token == NULL)
    {
        LOG_ERROR("Token entry point is NULL.");
        goto end_of_function;
    }

    /*< Start Function Algorithm >*/
    Frost_lexerAdvance(lexer);
    token_out = token;

    /*< Function Output >*/
end_of_function:
    return token_out;
}

/** ============================================================================
  @fn       Frost_lexerSkipWhiteSpace
  @package  Frost_Lexer

  @brief    Skips whitespace characters in the source string.

  @details  Advances the lexer past all whitespace characters, including spaces,
            tabs, and line breaks. If the lexer is NULL, returns an error code.

  @param    lexer     [in]:   Pointer to the lexer to modify.

  @return   FUNCTION_SUCCESS on success.
            -ENOMEM if the lexer is NULL.
 =========================================================================== **/
int Frost_lexerSkipWhiteSpace(lexer_t *lexer)
{
    /*< Variable Declarations >*/
    int ret = FUNCTION_SUCESS;
    
    /*< Security Checks >*/
    if (lexer == NULL)
    {
        LOG_ERROR("Lexer entry point is NULL.");
        goto end_of_function;
    }

    /*< Start Function Algorithm >*/
    while ( 
            (lexer->current_char == 13)     || 
            (lexer->current_char == 10)     || 
            (lexer->current_char == ' ')    ||
            (lexer->current_char == '\t')
          )
    {
        Frost_lexerAdvance(lexer);
    }
    
    /*< Function Output >*/
end_of_function:
    return ret;
}

/** ============================================================================
  @fn       Frost_lexerParseID
  @package  Frost_Lexer

  @brief    Parses an identifier token from the source string.

  @details  Reads alphanumeric characters from the current position in the
            source string to form an identifier. Creates and returns a token
            for the identifier. If memory allocation fails, returns NULL.

  @param    lexer     [in]:   Pointer to the lexer.

  @return   Pointer to a new identifier token on success.
            NULL if the lexer is NULL or memory allocation fails.
 =========================================================================== **/
token_t *Frost_lexerParseID(lexer_t *lexer)
{
    /*< Variable Declarations >*/
    token_t *token_out  = NULL;
    char *value         = NULL;
    
    /*< Security Checks >*/
    if (lexer == NULL)
    {
        LOG_ERROR("Lexer entry point is NULL.");
        goto end_of_function;
    }

    /*< Allocate Memory >*/
    value = (char *)calloc(1, sizeof(char));
    if (value == NULL)
    {
        LOG_ERROR("Fail at alloc for value.");
        goto end_of_function;
    }

    /*< Start Function Algorithm >*/
    while (isalnum(lexer->current_char))
    {
        value = (char *)realloc(value, ((strlen(value) + 2u) * sizeof(char)));
        if (value == NULL)
        {
            LOG_ERROR("Fail at realloc for value.");
            goto end_of_function;
        }

        strcat(value, (char[]){lexer->current_char, 0u});
        Frost_lexerAdvance(lexer);
    }

    token_out = Frost_initToken(value, TOKEN_ID);

    /*< Function Output >*/
end_of_function:
    return token_out;
}

/** ============================================================================
  @fn       Frost_lexerPeek
  @package  Frost_Lexer

  @brief    Retrieves a character from the source string at a specified offset.

  @details  Looks ahead or behind in the source string by a given offset relative
            to the current index in the lexer. Ensures that the returned character
            does not exceed the bounds of the source string. Returns a default
            space character if the lexer is NULL or if the calculated offset is
            invalid.

  @param    lexer     [in]:   Pointer to the lexer.
  @param    offset    [in]:   Offset from the current index to peek the character.

  @return   The character at the specified offset on success.
            A default space character (' ') if the lexer is NULL or the offset
            exceeds the bounds of the source string.
 =========================================================================== **/
char Frost_lexerPeek(lexer_t *lexer, int offset)
{
    /*< Variable Declarations >*/
    char ret = ' ';

    /*< Security Checks >*/
    if (lexer == NULL)
    {
        LOG_ERROR("Lexer entry point is NULL.");
        goto end_of_function;
    }

    /*< Start Function Algorithm >*/
    ret = (char)lexer->source[MIN((lexer->index + offset), lexer->source_size)];

    /*< Function Output >*/
end_of_function:
    return ret;
}

/** ============================================================================
  @fn       Frost_nextToken
  @package  Frost_Lexer

  @brief    Retrieves the next token from the source string.

  @details  Identifies and returns the next token in the source string. If the
            token is an identifier, it calls Frost_lexerParseID. If no valid
            token is found, it returns an EOF token.

  @param    lexer     [in]:   Pointer to the lexer.

  @return   Pointer to the next token on success.
            EOF token if no valid token is found.
 =========================================================================== **/
token_t *Frost_nextToken(lexer_t *lexer)
{
    /*< Variable Declarations >*/
    token_t *token_out = NULL;
    
    /*< Security Checks >*/
    if (lexer == NULL)
    {
        LOG_ERROR("Lexer entry point is NULL.");
        goto end_of_function;
    }

    /*< Start Function Algorithm >*/
    while (lexer->current_char != '\0')
    {
        if (isaalpha(lexer->current_char))
        {
            token_out = Frost_lexerAdvanceWith(lexer, Frost_lexerParseID(lexer));
            goto end_of_function;
        }

        switch (lexer->current_char)
        {
            case ':':

                break;
        }
    }

    token_out = Frost_initToken(0u, TOKEN_EOF);

    /*< Function Output >*/
end_of_function:
    return token_out;
}

/*< end of file >*/
