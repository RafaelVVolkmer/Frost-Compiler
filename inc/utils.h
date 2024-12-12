/** ============================================================================
    @addtogroup FrostCompiler
    @package    Frost_Utils

    @brief      Utility macros and definitions for the Frost compiler.

    @file       utils.h

    @author     Rafael V. Volkmer <rafael.v.volkmer@gmail.com>
    @date       11.12.2024

    @details    This header file provides a collection of utility macros and 
                definitions that are commonly used across various modules of the 
                Frost compiler. It includes macros for no-operation instructions, 
                architecture-specific alignment, logging, bit manipulation, and 
                other general-purpose utilities. These utilities facilitate 
                consistent coding practices and enhance code readability and 
                maintainability.

    @note       - Ensure that architecture-specific macros align with the target 
                  compilation environment.
                - Use logging macros (`LOG_INFO`, `LOG_WARNING`, `LOG_ERROR`) 
                  appropriately to aid in debugging and monitoring.
============================================================================ **/

#ifndef UTILS_H_
#define UTILS_H_

/* ========================================================================== *\
 *                              MACRO DEFINITIONS                             *
\* ========================================================================== */

/** ============================================================================
    @def       NOP__
    @brief     Executes a no-operation (NOP) instruction.

    @details   This macro inserts a no-operation instruction, which is useful for 
               timing adjustments, debugging, or preventing certain optimizations.
               The implementation varies based on the compiler being used.
               
    @note      - For GCC and Clang, it uses inline assembly.
               - For MSVC, it uses the built-in `__nop()` function.
               - For other compilers, it defaults to an empty do-while loop.
============================================================================ **/
#if defined(__GNUC__) || defined(__clang__)
    #define NOP__ __asm__ __volatile__("nop")
#elif defined(_MSC_VER)
    #define NOP__ __nop()
#else
    #define NOP__ do { } while (0)
#endif

/** ============================================================================
    @def       ARCH_ALIGNMENT
    @brief     Defines the default memory alignment based on the target 
               architecture.

    @details   This macro sets the `ARCH_ALIGNMENT` value to ensure that data 
               structuresare aligned according to the optimal alignment 
               requirements of the  underlying architecture. Proper alignment 
               can lead to performance improvements and prevent potential 
               hardware exceptions.

    @note      - x86_64 and ARM64 architectures typically benefit from 16-byte 
                 alignment.
               - 32-bit x86 and ARM architectures use 8-byte alignment.
               - For other architectures, `ALIGNMENT` should be defined 
                 appropriately.
============================================================================ **/
#if defined(__x86_64__) || defined(_M_X64)
    #define ARCH_ALIGNMENT 16U                      /**< x86_64 typically benefits from 16-byte alignment */
#elif defined(__aarch64__) || defined(_M_ARM64)
    #define ARCH_ALIGNMENT 16U                      /**< ARM64 also benefits from 16-byte alignment */
#elif defined(__i386__) || defined(_M_IX86)
    #define ARCH_ALIGNMENT 8U                       /**< 32-bit x86 uses 8-byte alignment */
#elif defined(__arm__) || defined(_M_ARM)
    #define ARCH_ALIGNMENT 8U                       /**< 32-bit ARM uses 8-byte alignment */
#else
    #define ARCH_ALIGNMENT ALIGNMENT                /**< Default alignment for other architectures */
#endif

/** ============================================================================
    @def       FUNCTION_SUCCESS
    @brief     Indicates successful execution of a function.

    @details   This macro represents a successful function return value, typically 
               used in functions that return an integer status code.
============================================================================ **/
#define FUNCTION_SUCESS 0U

/** ============================================================================
    @def       UNUSED(variable)
    @brief     Marks a variable as unused to suppress compiler warnings.

    @details   This macro casts the provided variable to `(void)`, informing the 
               compiler that the variable is intentionally unused. This is useful 
               in scenarios such as function parameters that are not utilized.

    @param     variable  The variable to mark as unused.
============================================================================ **/
#define UNUSED(variable)                                    \
    (void)(variable)

/** ============================================================================
    @def       MAX(param_a, param_b)
    @brief     Returns the maximum of two parameters.

    @details   This macro evaluates and returns the greater of two given 
               parameters. It uses the ternary operator to compare `param_a` 
               and `param_b`.

    @param     param_a  The first parameter for comparison.
    @param     param_b  The second parameter for comparison.

    @return    The greater of `param_a` and `param_b`.
============================================================================ **/
#define MAX(param_a, param_b)                               \
    ((param_a) > (param_b) ? (param_a) : (param_b))

/** ============================================================================
    @def       MIN(param_a, param_b)
    @brief     Returns the minimum of two parameters.

    @details   This macro evaluates and returns the lesser of two given 
               parameters. It uses the ternary operator to compare `param_a` 
               and `param_b`.

    @param     param_a  The first parameter for comparison.
    @param     param_b  The second parameter for comparison.

    @return    The lesser of `param_a` and `param_b`.
============================================================================ **/
#define MIN(param_a, param_b)                               \
    ((param_a) < (param_b) ? (param_a) : (param_b))

/** ============================================================================
    @def       LOG_INFO(message)
    @brief     Logs an informational message.

    @details   This macro prints an informational message to `stdout`, including 
               the function name, file name, and line number where the log is 
               invoked. It is useful for general-purpose logging and tracking 
               program flow.

    @param     message  The message string to log.
============================================================================ **/
#define LOG_INFO(message)                                   \
        fprintf(stdout, "INFO: %s at: %s() (%s:%d)\n",      \
            message, __func__, __FILE__, __LINE__)

/** ============================================================================
    @def       LOG_WARNING(message)
    @brief     Logs a warning message.

    @details   This macro prints a warning message to `stderr`, including the 
               function name, file name, and line number where the log is 
               invoked. It is useful for indicating potential issues that do not 
               prevent the program from running.

    @param     message  The warning message string to log.
============================================================================ **/
#define LOG_WARNING(message)                                \
        fprintf(stderr, "WARNING: %s at: %s() (%s:%d)\n",   \
            message, __func__, __FILE__, __LINE__)

/** ============================================================================
    @def       LOG_ERROR(message)
    @brief     Logs an error message.

    @details   This macro prints an error message to `stdout`, including the 
               function name, file name, and line number where the log is 
               invoked. It is useful for reporting critical issues that may 
               affect program execution.

    @param     message  The error message string to log.
============================================================================ **/
#define LOG_ERROR(message)                                  \
        fprintf(stdout, "DEBUG: %s at: %s() (%s:%d)\n",     \
            message, __func__, __FILE__, __LINE__)

/** ============================================================================
    @def       ALIGN_UP(x, align)
    @brief     Aligns a value `x` upwards to the nearest multiple of `align`.

    @details   This macro calculates the smallest multiple of `align` that is 
               greater than or equal to `x`. It is commonly used to ensure that 
               memory addresses or sizes adhere to specific alignment 
               requirements.

    @param     x        The value to be aligned.
    @param     align    The alignment boundary.

    @return    The aligned value.
============================================================================ **/
#define ALIGN_UP(x, align)                                  \
    (((x) + ((align) - 1U)) & ~((align) - 1U))

/** ============================================================================
    @def       ALIGN_DOWN(x, align)
    @brief     Aligns a value `x` downwards to the nearest multiple of `align`.

    @details   This macro calculates the largest multiple of `align` that is 
               less than or equal to `x`. It is useful for adjusting memory 
               addresses or sizes to fit alignment constraints.

    @param     x        The value to be aligned.
    @param     align    The alignment boundary.

    @return    The aligned value.
============================================================================ **/
#define ALIGN_DOWN(x, align)                                \
    ((x) & ~((align) - 1U))

/** ============================================================================
    @def       ALIGN_UP_ARCH(x)
    @brief     Aligns a value `x` upwards based on the architecture-specific
               alignment.

    @details   This macro uses the previously defined `ARCH_ALIGNMENT` to align 
               the value `x` upwards to the nearest multiple of the 
               architecture's default alignment.

    @param     x        The value to be aligned.

    @return    The aligned value.
============================================================================ **/
#define ALIGN_UP_ARCH(x)                                    \
    ALIGN_UP((x), ARCH_ALIGNMENT)

/** ============================================================================
    @def       ALIGN_DOWN_ARCH(x)
    @brief     Aligns a value `x` downwards based on the architecture-specific 
               alignment.

    @details   This macro uses the previously defined `ARCH_ALIGNMENT` to align 
               the value `x` downwards to the nearest multiple of the 
               architecture's default alignment.

    @param     x        The value to be aligned.

    @return    The aligned value.
============================================================================ **/
#define ALIGN_DOWN_ARCH(x)                                  \
    ALIGN_DOWN((x), ARCH_ALIGNMENT)

/** ============================================================================
    @def       SET_BIT(var, pos)
    @brief     Sets a specific bit in a variable.

    @details   This macro sets the bit at position `pos` in the variable 
               `var` to 1.

    @param     var      The variable whose bit is to be set.
    @param     pos      The position of the bit to set (0-based indexing).
============================================================================ **/
#define SET_BIT(var, pos)                                   \
    ((var) |= (1U << (pos)))

/** ============================================================================
    @def       CLEAR_BIT(var, pos)
    @brief     Clears a specific bit in a variable.

    @details   This macro clears the bit at position `pos` in the variable `var`, 
               setting it to 0.

    @param     var      The variable whose bit is to be cleared.
    @param     pos      The position of the bit to clear (0-based indexing).
============================================================================ **/
#define CLEAR_BIT(var, pos)                                 \
    ((var) &= ~(1U << (pos)))

/** ============================================================================
    @def       TOGGLE_BIT(var, pos)
    @brief     Toggles a specific bit in a variable.

    @details   This macro toggles the bit at position `pos` in the variable `var`. 
               If the bit is 1, it becomes 0, and vice versa.

    @param     var      The variable whose bit is to be toggled.
    @param     pos      The position of the bit to toggle (0-based indexing).
============================================================================ **/
#define TOGGLE_BIT(var, pos)                                \
    ((var) ^= (1U << (pos)))

/** ============================================================================
    @def       CHECK_BIT(var, pos)
    @brief     Checks the status of a specific bit in a variable.

    @details   This macro returns the value of the bit at position `pos` in the 
               variable `var`. It returns `1` if the bit is set, and `0` 
               otherwise.

    @param     var      The variable to check.
    @param     pos      The position of the bit to check (0-based indexing).

    @return    `1` if the bit at position `pos` is set, `0` otherwise.
============================================================================ **/
#define CHECK_BIT(var, pos)                                 \
    (((var) >> (pos)) & 1U)

#endif /* UTILS_H_ */

/*< end of header file >*/
