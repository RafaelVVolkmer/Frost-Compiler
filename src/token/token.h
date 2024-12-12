/** ===========================================================================
    @addtogroup FrostCompiler
    @package    Frost_Token

    @brief      This module provides functionalities for creating, managing, 
                and deallocating token objects used by the Frost compiler's 
                lexical analyzer.

    @file       token.h

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

#ifndef TOKEN_H_
#define TOKEN_H_

/* ========================================================================== *\
 *                                PUBLIC ENUMS                                *
\* ========================================================================== */

/** ============================================================================
    @enum       frostTokens
    @package    Frost_Token
    
    @typedef    token_type_t
    
    @brief      Enumerates all possible token types recognized by the Frost 
                compiler's lexical analyzer.
    
    @details    This enumeration defines the various types of tokens that the
                lexer can identify within the source code. It includes categories 
                such as identifiers, keywords, literals, arithmetic operators, 
                relational operators, logical operators, assignment operators, 
                bitwise operators, pointer operators, delimiters, comments, error 
                tokens, and the end-of-file marker. Each token type is assigned 
                a unique unsigned integer value to facilitate efficient token 
                classification and handling during the compilation process.
============================================================================ **/
typedef enum frostTokens
{
    /* <ID> */
    TOKEN_ID                = 0u,

    /* <Keywords> */
    TOKEN_IF                = 1u,   /**< Represents the 'if' keyword */
    TOKEN_ELSE              = 2u,   /**< Represents the 'else' keyword */
    TOKEN_WHILE             = 3u,   /**< Represents the 'while' keyword */
    TOKEN_FOR               = 4u,   /**< Represents the 'for' keyword */
    TOKEN_RETURN            = 5u,   /**< Represents the 'return' keyword */
    TOKEN_INT               = 6u,   /**< Represents the 'int' keyword */
    TOKEN_FLOAT             = 7u,   /**< Represents the 'float' keyword */
    TOKEN_CHAR              = 8u,   /**< Represents the 'char' keyword */
    TOKEN_VOID              = 9u,   /**< Represents the 'void' keyword */
    TOKEN_STRUCT            = 10u,  /**< Represents the 'struct' keyword */
    TOKEN_CONST             = 11u,  /**< Represents the 'const' keyword */

    /* <Identifiers> */
    TOKEN_IDENTIFIER        = 12u,  /**< Represents a general identifier */

    /* <Literals> */
    TOKEN_LITERAL_INT       = 13u,  /**< Represents an integer literal */
    TOKEN_LITERAL_FLOAT     = 14u,  /**< Represents a floating-point literal */
    TOKEN_LITERAL_CHAR      = 15u,  /**< Represents a character literal */
    TOKEN_LITERAL_STRING    = 16u,  /**< Represents a string literal */

    /* <Arithmetic Operators> */
    TOKEN_PLUS              = 17u,  /**< Represents the '+' operator */
    TOKEN_MINUS             = 18u,  /**< Represents the '-' operator */
    TOKEN_MULTIPLY          = 19u,  /**< Represents the '*' operator */
    TOKEN_DIVIDE            = 20u,  /**< Represents the '/' operator */
    TOKEN_MODULO            = 21u,  /**< Represents the '%' operator */

    /* <Relational Operators> */
    TOKEN_EQUAL             = 22u,  /**< Represents the '==' operator */
    TOKEN_NOT_EQUAL         = 23u,  /**< Represents the '!=' operator */
    TOKEN_LESS              = 24u,  /**< Represents the '<' operator */
    TOKEN_GREATER           = 25u,  /**< Represents the '>' operator */
    TOKEN_LESS_EQUAL        = 26u,  /**< Represents the '<=' operator */
    TOKEN_GREATER_EQUAL     = 27u,  /**< Represents the '>=' operator */

    /* <Logical Operators> */
    TOKEN_AND               = 28u,  /**< Represents the '&&' operator */
    TOKEN_OR                = 29u,  /**< Represents the '||' operator */
    TOKEN_NOT               = 30u,  /**< Represents the '!' operator */

    /* <Assignment Operators> */
    TOKEN_ASSIGN            = 31u,  /**< Represents the '=' operator */
    TOKEN_PLUS_ASSIGN       = 32u,  /**< Represents the '+=' operator */
    TOKEN_MINUS_ASSIGN      = 33u,  /**< Represents the '-=' operator */
    TOKEN_MULTIPLY_ASSIGN   = 34u,  /**< Represents the '*=' operator */
    TOKEN_DIVIDE_ASSIGN     = 35u,  /**< Represents the '/=' operator */

    /* <Bitwise Operators> */
    TOKEN_BITWISE_AND       = 36u,  /**< Represents the '&' operator */
    TOKEN_BITWISE_OR        = 37u,  /**< Represents the '|' operator */
    TOKEN_BITWISE_XOR       = 38u,  /**< Represents the '^' operator */
    TOKEN_BITWISE_NOT       = 39u,  /**< Represents the '~' operator */
    TOKEN_LEFT_SHIFT        = 40u,  /**< Represents the '<<' operator */
    TOKEN_RIGHT_SHIFT       = 41u,  /**< Represents the '>>' operator */

    /* <Pointer Operators> */
    TOKEN_POINTER           = 42u,  /**< Represents the '*' operator for pointers */
    TOKEN_ADDRESS           = 43u,  /**< Represents the '&' operator for addresses */

    /* <Delimiters and Punctuation> */
    TOKEN_SEMICOLON         = 44u,  /**< Represents the ';' delimiter */
    TOKEN_COMMA             = 45u,  /**< Represents the ',' delimiter */
    TOKEN_PERIOD            = 46u,  /**< Represents the '.' delimiter */
    TOKEN_COLON             = 47u,  /**< Represents the ':' delimiter */
    TOKEN_DOUBLE_COLON      = 48u,  /**< Represents the '::' delimiter */
    TOKEN_LEFT_PAREN        = 49u,  /**< Represents the '(' delimiter */
    TOKEN_RIGHT_PAREN       = 50u,  /**< Represents the ')' delimiter */
    TOKEN_LEFT_BRACE        = 51u,  /**< Represents the '{' delimiter */
    TOKEN_RIGHT_BRACE       = 52u,  /**< Represents the '}' delimiter */
    TOKEN_LEFT_BRACKET      = 53u,  /**< Represents the '[' delimiter */
    TOKEN_RIGHT_BRACKET     = 54u,  /**< Represents the ']' delimiter */

    /* <Comments> */
    TOKEN_COMMENT           = 55u,  /**< Represents a comment in the source code */

    /* <Error> */
    TOKEN_ERROR             = 56u,  /**< Represents an erroneous or unrecognized token */

    /* <End of File> */
    TOKEN_EOF               = 57u,  /**< Represents the end of the source file */
} token_type_t;

/* ========================================================================== *\
 *                              PUBLIC STRUCTURES                             *
\* ========================================================================== */

/** ============================================================================
  @struct   tokenInstance
  @package  Frost_Token

  @typedef  token_t

  @brief    Represents a token instance within the Frost compiler's lexical 
            analysis.

  @details  The token structure holds a lexeme (a sequence of characters taken 
            from the source code) and a token type that categorizes the lexeme 
            (e.g., identifier, keyword, punctuation). This data is fundamental 
            for the parser and subsequent compiler stages that rely on the 
            lexical analysis results.

============================================================================ **/
typedef struct __attribute__((packed)) tokenInstance
{
    char            *lexeme;        /*< Pointer to the token’s lexeme string >*/
    token_type_t    type;           /*< The token type, as defined by token_type_t >*/
} token_t;

/* ========================================================================== *\
 *                       PUBLIC FUNCTIONS PROTOTYPES                          *
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
token_t *Frost_initToken(const char *lexeme, token_type_t type);

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
int FrostCompiler_freeToken(token_t *token);

#endif /* TOKEN_H_ */

/*< end of header file >*/
