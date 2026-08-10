/**........................................................
// C base utility functions and macros.                  */

#ifndef SEROS_BASE_UTILS
#define SEROS_BASE_UTILS

/**........................................................
// Length and count macros                               */

#if HAS_BUILTINS
#       define CountOf(x)                                                                        \
        ({     CompileAssert(!__builtin_types_compatible_p(TypeOf(x), TypeOf(&(x)[0])),          \
                             "CountOf: argument must be a real array and not a pointer.");       \
               (I32) (sizeof(x)/sizeof((x)[0]));                                                 \
        })
#else          /* !HAS_BUILTINS */
#       define CountOf(x) ((I32)(sizeof(x) / sizeof((x)[0])))
#endif         /* CountOf */

#define LengthOf(x) (CountOf(x)-1)

/**........................................................
// Struct member offset macros                           */

#if HAS_BUILTINS
#       define CastFromMember(T, m, ptr)                                                         \
        ({     CompileAssert(__builtin_types_compatible_p(TypeOf(ptr), TypeOf(&(((T*)0)->m))) || \
                             __builtin_types_compatible_p(TypeOf(ptr), U0*),                     \
                             "CastFromMember: ptr type does not match member type.");            \
               (T*) ((I8*) (ptr)-OffsetOf(T,m));                                                 \
        })
#else          /* !HAS_BUILTINS */
#       define CastFromMember(T, m, ptr) (T*) ((I8*) (ptr)-OffsetOf(T,m))
#endif         /* CastFromMember */

/**........................................................
//  Min, Max, Clamp and Swap Functions                   */

/* The Max, Min, Clamp and Swap functions are generated using X-macros. Assume stack    */
/* traffic when using these in debug builds. The compiler can optimize out and inline   */
/* this during release.                                                                 */
/* See SEI Cert C Coding Standard (Edition 2016): page 26 and 27.                       */

#define MakeMaxFn(T)   static inline T max##T(T x, T y) { return (x > y) ? x : y; }
#define MakeMinFn(T)   static inline T min##T(T x, T y) { return (x < y) ? x : y; }
#define MakeSwapFn(T)  static inline U0 swap##T(T *x, T*y) { T t = *x; *x = *y; *y = t; }
#define MakeClampFn(T) static inline T clamp##T(T v, T min, T max) { if (v < min) return min;    \
                                                                     if (v > max) return max;    \
                                                                     return v; }
XMacroNumTypes(MakeMaxFn)
XMacroNumTypes(MakeMinFn)
XMacroNumTypes(MakeSwapFn)
XMacroNumTypes(MakeClampFn)

#undef MakeMaxFn
#undef MakeMinFn
#undef MakeSwapFn
#undef MakeClampFn

#endif /* SEROS_BASE_UTILS */
