/**........................................................
// String types.                                         */

#ifndef SEROS_BASE_STRING
#define SEROS_BASE_STRING

typedef struct String8 S8;
struct String8 {
        I8 *str;
        I64 strlen;
};

/* String literal */
#define S8Lit(s) (S8) { (s), LengthOf(s); }

#endif /* SEROS_BASE_STRING */
