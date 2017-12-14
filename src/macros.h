#ifndef MACROS_H
#define MACROS_H

#define NMACROS 10
#define MACRO_LENGTH 20

/* Add a macro
 *
 * Macros end with an empty key 'k_empty'
 */
void add_macro(Key macro[MACRO_LENGTH]);
void add_string_macro(char macro[MACRO_LENGTH]);
void report_macro(int id);

#endif // MACROS_H
