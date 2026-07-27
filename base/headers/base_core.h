/**........................................................
// C core utilities.                                     */

#ifndef SEROS_BASE_CORE
#define SEROS_BASE_CORE

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
#else 
#       warning "seros: Unrecognised compiler."
#endif  /* CLANG_COMPILER, GNU_COMPILER, MSVC_COMPILER */

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
#  endif       /* __STDC_VERSION__ */
#endif  /* __STDC__ */

/**........................................................
// CPU architecture delegation.                          */

#if defined(__amd64__)
#       define ARCH_X64   1
#elif defined(__amd64)
#       define ARCH_X64   1
#elif defined(__x86_64__)
#       define ARCH_X64   1
#elif defined(__x86_64)
#       define ARCH_X64   1
#elif defined(_M_X64)
#       define ARCH_X64   1
#elif defined(_M_AMD64)
#       define ARCH_X64   1
#endif         /* ARCH_X64 */

#if defined(i386)
#       define ARCH_X86   1
#elif defined(__i386__)
#       define ARCH_X86   1
#elif defined(__i386)
#       define ARCH_X86   1
#elif defined(_M_IX86)
#       define ARCH_X86   1
#endif         /* ARCH_X86 */

#if defined(__aarch64__)
#       define ARCH_ARM64 1
#elif defined(_M_ARM64)
#       define ARCH_ARM64 1
#endif         /* ARCH_ARM64 */

#if defined(__arm__)
#       define ARCH_ARM32 1
#elif defined(_M_ARM)
#       define ARCH_ARM32 1
#endif         /* ARCH_ARM32 */

#if defined(__riscv)
#       define ARCH_RISCV 1
#endif         /* ARCH_RISCV */

#if defined(__mips__)
#       define ARCH_MIPS  1
#elif defined(__mips)
#       define ARCH_MIPS  1
#endif         /* ARCH_MIPS */

#if !defined(ARCH_X64)
#       define ARCH_X64   0
#endif
#if !defined(ARCH_X86)
#       define ARCH_X86   0
#endif
#if !defined(ARCH_ARM64)
#       define ARCH_ARM64 0
#endif
#if !defined(ARCH_ARM32)
#       define ARCH_ARM32 0
#endif
#if !defined(ARCH_RISCV)
#       define ARCH_RISCV 0
#endif
#if !defined(ARCH_MIPS)
#       define ARCH_MIPS  0
#endif

#if !(ARCH_X64 || ARCH_X86 || ARCH_ARM64 || ARCH_ARM32 || ARCH_RISCV || ARCH_MIPS)
#       error "seros: Unrecognised processor."
#endif

/**........................................................
// Pointer width.                                        */

#if ARCH_X64
#       define ARCH_64BIT 1
#elif ARCH_ARM64
#       define ARCH_64BIT 1
#elif ARCH_RISCV && (__riscv_xlen == 64)
#       define ARCH_64BIT 1
#elif ARCH_MIPS && defined(__mips64)
#       define ARCH_64BIT 1
#elif ARCH_X86
#       define ARCH_32BIT 1
#elif ARCH_ARM32
#       define ARCH_32BIT 1
#elif ARCH_RISCV && (__riscv_xlen == 32)
#       define ARCH_32BIT 1
#elif ARCH_MIPS
#       define ARCH_32BIT 1
#else
#       error "seros: Unrecognised architecture"
#endif
#if !defined(ARCH_64BIT)
#       define ARCH_64BIT 0
#endif
#if !defined(ARCH_32BIT)
#       define ARCH_32BIT 0
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

#define XMacroNumTypes(X) X(U16) X(U32) X(U64) X(I16) X(I32) X(I64) X(F32) X(F64)

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
#       define CompilerExt(...) __attribute__((__VA_ARGS__))
#elif MSVC_COMPILER
#       define CompilerExt(...) __declspec((__VA_ARGS__))
#else          /* !(GNU_COMPILER || CLANG_COMPILER) && !MSVC_COMPILER */
#       define CompilerExt(...) ((U0)(__VA_ARGS__))
#endif         /*   CompilerExt  */

#if GNU_COMPILER || CLANG_COMPILER
#       define TypeOf(t) __typeof__(t)
#       define AlignOf(t) __alignof__(t)
#elif STD_C23
#       define TypeOf(t) typeof(t)
#       define AlignOf(t) alignof(t)
#elif STD_C11
#       define AlignOf(t) _Alignof(t)
#endif         /* TypeOf, AlignOf  */

#if GNU_COMPILER || CLANG_COMPILER
#       define AlignType(x) CompilerExt(aligned(x))
#elif MSVC_COMPILER
#       define AlignType(x) CompilerExt(align(x))
#endif        /*  AlignType */

/* Note that the #else branch implementation of offsetof fails UBSAN;
 * instead use __builtin_offsetof() available since GCC 4 and Clang 4.
 * [Source] https://lkml.iu.edu/hypermail/linux/kernel/2604.0/01424.html */

#undef offsetof
#if GNU_COMPILER || CLANG_COMPILER
#       define OffsetOf(T, m) __builtin_offsetof(T, m)
#else          /* !(GNU_COMPILER || CLANG_COMPILER) */
#       define OffsetOf(T, m) ((U64) &((T*)0)->m)
#endif         /* OffsetOf */

#undef NULL
#if STD_C23
#       define NULL nullptr
        typedef TypeOf(NULL) /* nullptr_t */ Nptr;
#else          /* !STD_C23 */
#       define NULL ((U0*)0)
#endif         /* NULL */

#define asm __asm__
#define volatile __volatile__

/**........................................................
// Branch prediction macros                              */

#if GNU_COMPILER || CLANG_COMPILER
#       define Expect(e, v) __builtin_expect((e), (v))
#else          /* !(GNU_COMPILER || CLANG_COMPILER) */
#       define Expect(e, v) (e)
#endif         /* Expect  */

#define Likely(e)   Expect((e), 1)
#define Unlikely(e) Expect((e), 0)

/**........................................................
// Length and count macros                               */

#if GNU_COMPILER || CLANG_COMPILER
#       define CountOf(x) ({                                                                     \
               CompileAssert(!__builtin_types_compatible_p(TypeOf(x), TypeOf(&(x)[0])),          \
                             "CountOf: argument must be a real array and not a pointer.");       \
               (I32) (sizeof(x)/sizeof((x)[0]));                                                 \
        })
#else          /* !(GNU_COMPILER || CLANG_COMPILER) */
#       define CountOf(x) ((I32)(sizeof(x) / sizeof((x)[0])))
#endif         /* CountOf */

#define LengthOf(x) (CountOf(x)-1)

/**........................................................
// Struct member offset macros                           */

#if GNU_COMPILER || CLANG_COMPILER
#       define CastFromMember(T, m, ptr) ({                                                      \
               CompileAssert(__builtin_types_compatible_p(TypeOf(ptr), TypeOf(&(((T*)0)->m))) || \
                             __builtin_types_compatible_p(TypeOf(ptr), U0*),                     \
                             "CastFromMember: ptr type does not match member type.");            \
               (T*) ((I8*) (ptr)-OffsetOf(T,m));                                                 \
        })
#else          /* !(GNU_COMPILER || CLANG_COMPILER) */
#       define CastFromMember(T, m, ptr) (T*) ((I8*) (ptr)-OffsetOf(T,m))
#endif         /* CastFromMember */

#endif /* SEROS_BASE_CORE */
