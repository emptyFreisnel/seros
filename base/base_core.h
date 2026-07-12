/**........................................................
// C core utilites and basic types.                       */

#ifndef SEROS_BASE_CORE
#define SEROS_BASE_CORE

#ifdef __cplusplus
extern "C" {
#endif

/**........................................................
// Freestanding header includes                           */

#include <stdint.h>
#include <stddef.h>

/**........................................................
// Compiler versioning delegation macros                  */

#if defined(__clang__)
#       define CLANG_COMPILER 1
#elif defined(__GNUC__)
#       define GNU_COMPILER   1
#elif defined(_MSC_VER)
#       define MSVC_COMPILER  1
#endif

#if defined(__STDC__)
#  if !defined(__STDC_VERSION__)
#       define STD_C89 1
#  endif
#  if __STDC_VERSION__ >= 199409L
#       define STD_C89 1
#  endif
#  if __STDC_VERSION__ >= 199901L
#       define STD_C99 1
#  endif
#  if __STDC_VERSION__ >= 201112L
#       define STD_C11 1
#  endif
#  if __STDC_VERSION__ >= 201710L
#       define STD_C17 1
#  endif
#  if __STDC_VERSION__ >= 202311L
#       define STD_C23 1
#  endif
#  if __STDC_VERSION__ >  202311L
#       define STD_C2Y 1
#  endif
#endif

/**........................................................
// Base Types and keyword abstractions for compatibility  */

#ifndef offsetof
#       define OffsetOf(T, m) ((U64) &((T*)0)->m)
#else
#       define OffsetOf(T, m) offsetof(T, m)
#endif

#if GNU_COMPILER || CLANG_COMPILER
#       define TypeOf(t) __typeof__(t)
#elif STD_C23
#       define TypeOf(t) typeof(t)
#endif

typedef void     U0;
typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef int8_t   S8;
typedef int16_t  S16;
typedef int32_t  S32;
typedef int64_t  S64;
typedef U8       B8;
typedef U16      B16;
typedef U32      B32;
typedef U64      B64;
typedef float    F32;
typedef double   F64;

typedef U0 Proc(U0);

typedef union U128 U128;
union U128 {
	U8  u8[16];
	U16 u16[8];
	U32 u32[4];
	U64 u64[2];
};

/**........................................................
// Units                                                   */

#define KB(n) (((U64)(n))<<10)
#define MB(n) (((U64)(n))<<20)
#define GB(n) (((U64)(n))<<30)
#define TB(n) (((U64)(n))<<40)

/*........................................................*/
// Debugging utilities

#ifndef DEBUG
#       define DEBUG 1
#endif

/*........................................................*/
// Asserts and Typechecking
// Note on HintAssert: 

#define CompileAssert(...) _Static_assert(__VA_ARGS__)

#if GNU_COMPILER || CLANG_COMPILER
#       define RuntimeAssert(c) do { if (!(c)) __builtin_trap(); } while(0)
#       define HintAssert(c) while (!(c)) __builtin_unreachable();
#elif MSVC_COMPILER
#       define RuntimeAssert(c) do { if (!(c)) __debugbreak(); } while(0)
#       define HintAssert(c) while (!(c)) __assume(0)
#else 
#       define RuntimeAssert(c) ((U0)(c))
#       define HintAssert(c) ((U0)(c))
#endif

/*........................................................*/
// Length and count macros

#if GNU_COMPILER || CLANG_COMPILER
#       define CountOf(x) ({                                                                     \
               CompileAssert(!__builtin_types_compatible_p(TypeOf(x), TypeOf(&(x)[0])),          \
                             "CountOf: argument must be a real array and not a pointer.");       \
               (S32) (sizeof(x)/sizeof((x)[0]));                                                 \
        })
#else
#       define CountOf(x) ((S32) (sizeof(x)/sizeof((x)[0])))
#endif

/*........................................................*/
// Struct member offset macros

#if GNU_COMPILER || CLANG_COMPILER
#       define CastFromMember(T, m, ptr) ({                                                      \
               CompileAssert(__builtin_types_compatible_p(TypeOf(ptr), TypeOf(&(((T*)0)->m))) || \
                             __builtin_types_compatible_p(TypeOf(ptr), U0*),                     \
                             "CastFromMember: ptr type does not match member type.");            \
               (T*) ((S8*) (ptr)-OffsetOf(T,m));                                                 \
        })
#else
#       define CastFromMember(T, m, ptr) (T*) ((S8*) (ptr)-OffsetOf(T,m))
#endif

#ifdef __cplusplus
}
#endif

#endif /* SEROS_BASE_CORE */
