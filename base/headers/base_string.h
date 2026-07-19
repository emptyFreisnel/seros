/**........................................................
// String types.                                         */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct String8 S8;
struct String8 {
        I8 *str;
        I64 strlen;
};

/* String literal */
#define S8Lit(s) (S8) { (s), LengthOf(s); }


#ifdef __cplusplus
}
#endif
