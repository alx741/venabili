#pragma once

#define NMACROS 10
#define MACRO_LENGTH 20

extern Key MACROS[NMACROS][MACRO_LENGTH];

/* Add a macro
 *
 * Macros end with an empty key 'k_empty'
 */
void add_macro(const Key macro[MACRO_LENGTH]);

/* Add a string macro
 *
 * String macros end with a null character '\0'
 */
void add_string_macro(const char macro[MACRO_LENGTH]);

/* Report a macro to the host
 */
void report_macro(int id);
