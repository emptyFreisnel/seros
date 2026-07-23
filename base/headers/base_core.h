/**........................................................
// C core utilities.

*  The code in this file is seperated into the following

*  1. Freestanding header includes.
*  2. Compiler versioning delegation.
*  3. OS and CPU architecture delegation.                */

#ifndef SEROS_BASE_CORE
#define SEROS_BASE_CORE

#ifdef __cplusplus
extern "C" {
#endif

/**........................................................
// Freestanding/standalone header includes.              */

#include <stdarg.h>  /* For va_args/va_list */
#include <stdint.h>  /* For fixed width types eg int32_t */

/**........................................................
// Compiler versioning delegation.                       */

#if defined(__clang__)
#       define CLANG_COMPILER 1
#elif defined(__GNUC__)
#       define GNU_COMPILER   1
#elif defined(_MSC_VER)
#       define MSVC_COMPILER  1
#endif

#ifdef __STDC__
#  ifndef __STDC_VERSION__
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
#endif /* __STDC__ */

/**........................................................
// OS and CPU architecture delegation.                   */

#if defined(_WIN32)
#       define OS_WINDOWS 1
#elif defined(__gnu_linux__) || defined(__linux__)
#       define OS_LINUX   1
#elif defined(__APPLE__) && defined(__MACH__)
#       define OS_MAC     1
#endif

/* x86 and x86-64 */
#if defined(__amd64__) || defined(__amd64)
#       define ARCH_X64   1
#elif defined(__x86_64__) || defined(__x86_64)
#       define ARCH_X64   1
#elif defined(i386)   || defined(__i386__)
#       define ARCH_X86   1
#elif defined(__i386) || defined(_M_IX86)
#       define ARCH_X86   1
#endif

/* AARCH64 and ARM32 */
#if defined(__aarch64__)
#       define ARCH_ARM64 1
#elif defined(__arm__)
#       define ARCH_ARM32 1
#endif
        
#if defined(__riscv__)
#       define ARCH_RISCV 1
#elif defined(__mips__)
#       define ARCH_MIPS  1
#endif

#if ARCH_X64 || ARCH_ARM64
#       define ARCH_64BIT 1
#elif ARCH_X86 || ARCH_ARM64
#       define ARCH_32BIT 1
#endif

/**........................................................
// Base types                                            */

typedef void      U0;
typedef uint8_t   U8;
typedef uint16_t  U16;
typedef uint32_t  U32;
typedef uint64_t  U64;
typedef uintptr_t Uptr;
typedef int8_t    I8;
typedef int16_t   I16;
typedef int32_t   I32;
typedef int64_t   I64;
typedef intptr_t  Iptr;
typedef U8        B8;
typedef U16       B16;
typedef U32       B32;
typedef U64       B64;
typedef float     F32;
typedef double    F64;

typedef U0 Proc(U0);

typedef union U128 U128;
union U128 {
	U8  u8[16];
	U16 u16[8];
	U32 u32[4];
	U64 u64[2];
        F32 f32[4];
        F64 f64[2];
};

typedef union U256 U256;
union U256 {
	U8    u8[32];
	U16   u16[16];
	U32   u32[8];
	U64   u64[4];
        U128 u128[2];
        F32   f32[8];
        F64   f64[4];
};

/**........................................................
// Units                                                 */

#define KB(n) (((U64)(n))<<10)
#define MB(n) (((U64)(n))<<20)
#define GB(n) (((U64)(n))<<30)
#define TB(n) (((U64)(n))<<40)

/**........................................................
// Keyword and compiler attribute wrappers               */

#if GNU_COMPILER || CLANG_COMPILER
#       define ComplierExt(...) __attribute__((__VA_ARGS__))
#elif MSVC_COMPILER
#       define ComplierExt(...) __declspec((__VA_ARGS__))
#else          /* !(GNU_COMPILER || CLANG_COMPILER) && !MSVC_COMPILER */
#       define ComplierExt(...) ((U0)(__VA_ARGS__))
#endif         /*   GNU_COMPILER || CLANG_COMPILER  */

#if GNU_COMPILER || CLANG_COMPILER
#       define TypeOf(t) __typeof__(t)
#       define AlignOf(t) __alignof__(t)
#elif STD_C23
#       define TypeOf(t) typeof(t)
#       define AlignOf(t) alignof(t)
#elif STD_C11
#       define AlignOf(t) _Alignof(t)
#endif         /*   GNU_COMPILER || CLANG_COMPILER  */

/* Note that the #else branch implementation of offsetof fails UBSAN;
 * instead use __builtin_offsetof() available since GCC 4 and Clang 4.
 * [Source] https://lkml.iu.edu/hypermail/linux/kernel/2604.0/01424.html */

#undef offsetof
#if GNU_COMPILER || CLANG_COMPILER
#       define OffsetOf(T, m) __builtin_offsetof(T, m)
#else          /* !(GNU_COMPILER || CLANG_COMPILER) */
#       define OffsetOf(T, m) ((U64) &((T*)0)->m)
#endif         /*   GNU_COMPILER || CLANG_COMPILER  */

#undef NULL
#if STD_C23
#       define NULL nullptr
        typedef TypeOf(NULL) Nptr;
#else          /* !STD_C23 */
#       define NULL ((U0*)0)
#endif         /*  STD_C23 */

#define asm __asm__
#define volatile __volatile__

#define private static

/**........................................................
// Type alignment                                        */

#if GNU_COMPILER || CLANG_COMPILER
#       define AlignType(x) CompilerExt(aligned(x))
#elif MSVC_COMPILER
#       define AlignType(x) CompilerExt(align(x))
#endif
        

/**........................................................
// Branch prediction macros                              */

#if GNU_COMPILER || CLANG_COMPILER
#       define Expect(e, v) __builtin_expect((e), (v))
#else          /* !(GNU_COMPILER || CLANG_COMPILER) */
#       define Expect(e, v) (e)
#endif         /*   GNU_COMPILER || CLANG_COMPILER  */

#define Likely(e)   Expect((e), 1)
#define Unlikely(e) Expect((e), 0)

/**........................................................
// Length and count macros                               */

#if GNU_COMPILER || CLANG_COMPILER
#       define CountOf(x) ({                                                                     \
               CompileAssert(!__builtin_types_compatible_p(TypeOf(x), TypeOf(&(x)[0])),          \
                             "CountOf: argument must be a real array and not a pointer.");       \
               (S32) (sizeof(x)/sizeof((x)[0]));                                                 \
        })
#else          /* !(GNU_COMPILER || CLANG_COMPILER) */
#       define CountOf(x) ((S32)(sizeof(x) / sizeof((x)[0])))
#endif         /*   GNU_COMPILER || CLANG_COMPILER  */

#define LengthOf(x) (CountOf(x)-1)

/**........................................................
// Struct member offset macros                           */

#if GNU_COMPILER || CLANG_COMPILER
#       define CastFromMember(T, m, ptr) ({                                                      \
               CompileAssert(__builtin_types_compatible_p(TypeOf(ptr), TypeOf(&(((T*)0)->m))) || \
                             __builtin_types_compatible_p(TypeOf(ptr), U0*),                     \
                             "CastFromMember: ptr type does not match member type.");            \
               (T*) ((S8*) (ptr)-OffsetOf(T,m));                                                 \
        })
#else          /* !(GNU_COMPILER || CLANG_COMPILER) */
#       define CastFromMember(T, m, ptr) (T*) ((S8*) (ptr)-OffsetOf(T,m))
#endif         /*   GNU_COMPILER || CLANG_COMPILER  */

#ifdef __cplusplus
}
#endif

#endif /* SEROS_BASE_CORE */
