/** ============================================================================
    @addtogroup FrostCompiler
    @package    Frost_Lexer

    @brief      This module provides functionalities for lexical analysis
                within the Frost Compiler, including tokenization, identifier
                parsing, and whitespace handling.

    @file       lexer.h

    @author     Rafael V. Volkmer <rafael.v.volkmer@gmail.com>
    @date       11.12.2024
 
    @details    The Frost Lexer module is responsible for breaking down source
                code into meaningful tokens. It handles lexemes like identifiers,
                operators, and whitespace, serving as the first step in parsing
                source code for the Frost Compiler. The module provides utility
                functions for advancing through the source, skipping unnecessary
                characters, and parsing identifiers.

    @note       - Ensure the input source string is properly formatted before
                  initializing the lexer to prevent errors during tokenization.
                - The module relies on the Frost_Token module for creating and
                  managing token objects
 =========================================================================== **/

#ifndef LEXER_H_
#define LEXER_H_

/* ========================================================================== *\
 *                               INCLUDED FILES                               *
\* ========================================================================== */

/*< Dependencies >*/
#include <stdio.h>

/*< Implements >*/
#include "../token/token.h"

/* ========================================================================== *\
 *                              PUBLIC STRUCTURES                             *
\* ========================================================================== */

/** ============================================================================
  @struct   frostLexer
  @package  Frost_Lexer

  @typedef  lexer_t

  @brief    Represents the structure of a lexical analyzer.

  @details  The lexer structure contains the source code string being analyzed,
            the current character being processed, the total size of the source
            string, and the current index of the lexer within the source.
============================================================================ **/
typedef struct __attribute__((packed)) frostLexer
{
    char        *source;            /*< Pointer to the source string >*/
    char        current_char;       /*< Current character being processed >*/
    size_t      source_size;        /*< Total size of the source string >*/
    size_t      index;              /*< Current index in the source string >*/
} lexer_t;

/* ========================================================================== *\
 *                       PUBLIC FUNCTIONS PROTOTYPES                          *
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
lexer_t *Frost_initLexer(char *source);

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
int Frost_freeLexer(lexer_t *lexer);

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
int Frost_lexerAdvance(lexer_t *lexer);

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
token_t *Frost_lexerAdvanceWith(lexer_t *lexer, token_t *token);

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
int Frost_lexerSkipWhiteSpace(lexer_t *lexer);

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
token_t *Frost_lexerParseID(lexer_t *lexer);

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
char Frost_lexerPeek(lexer_t *lexer, int offset);

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
token_t *Frost_nextToken(lexer_t *lexer);

#endif /* LEXER_H_ */

/*< end of header file >*/
