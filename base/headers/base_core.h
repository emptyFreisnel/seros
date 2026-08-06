
/**........................................................
// C core utilities.                                     */

/* [raddbgger] https://github.com/EpicGames/raddebugger  */

#ifndef SEROS_BASE_CORE
#define SEROS_BASE_CORE

/**........................................................
// Freestanding/standalone header includes.              */

#include <stdarg.h>  /* For va_args/va_list              */
#include <stdint.h>  /* For fixed width types eg int32_t */
#include <stddef.h>  /* For size_t and ptrdiff_t         */

/**........................................................
// Compiler versioning delegation.                       */

#if defined(__clang__)
#       define CLANG_COMPILER 1
#elif defined(__GNUC__)
#       define GNU_COMPILER   1
#elif defined(_MSC_VER)
#       define MSVC_COMPILER  1
#endif  /* CLANG_COMPILER, GNU_COMPILER, MSVC_COMPILER */

#if !defined(CLANG_COMPILER)
#       define CLANG_COMPILER 0
#elif !defined(GNU_COMPILER)
#       define GNU_COMPILER 0
#elif !defined(MSVC_COMPILER)
#       define GNU_COMPILER 0
#else
#       warning "seros: Unrecognised compiler."
#endif

#if GNU_COMPILER || CLANG_COMPLIER
#       define HAS_COMPILER_BUILTINS 1
#elif MSVC_COMPILER
#       define HAS_MSVC_INTRINSICS 1
#endif

#if !defined(HAS_COMPILER_BUILTINS)
#       define HAS_COMPILER_BUILTINS 0
#elif !defined(MSVC_COMPILER)
#       define HAS_MSVC_INTRINSICS 1
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
#endif         /* !defined(ARCH_X64) */
#if !defined(ARCH_X86)
#       define ARCH_X86   0
#endif         /* !defined(ARCH_X86) */
#if !defined(ARCH_ARM64)
#       define ARCH_ARM64 0
#endif         /* !defined(ARCH_ARM64) */
#if !defined(ARCH_ARM32)
#       define ARCH_ARM32 0
#endif         /* !defined(ARCH_ARM32) */
#if !defined(ARCH_RISCV)
#       define ARCH_RISCV 0
#endif         /* !defined(ARCH_RISCV) */
#if !defined(ARCH_MIPS)
#       define ARCH_MIPS  0
#endif         /* !defined(ARCH_MIPS) */

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
#else          /* !(ARCH_X64 || ARCH_X86 || ARCH_ARM64 || ARCH_ARM32 || ARCH_RISCV || ARCH_MIPS) */
#       error "seros: Unrecognised architecture"
#endif
#if !defined(ARCH_64BIT)
#       define ARCH_64BIT 0
#endif         /* !defined(ARCH_64BIT) */
#if !defined(ARCH_32BIT)
#       define ARCH_32BIT 0
#endif         /* !defined(ARCH_32BIT) */

/**........................................................
// OS architecture delegation.                           */

#if defined(_WIN32)
#       define OS_WINDOWS 1
#elif defined(_WIN64)
#       define OS_WINDOWS 1
#elif defined(__WIN32__)
#       define OS_WINDOWS 1
#elif defined(__NT__)
#       define OS_WINDOWS 1
#endif         /* OS_WINDOWS */
#if defined(__APPLE__) && defined(__MACH__)
#       define OS_MAC     1
#endif         /* OS_MAC     */
#if defined(__linux__)
#       define OS_LINUX   1
#elif defined(__linux)
#       define OS_LINUX   1
#elif defined(__gnu_linux__)
#       define OS_LINUX   1
#endif         /* OS_LINUX   */
#if defined(__FreeBSD__)
#       define OS_FREEBSD 1
#elif defined(__FreeBSD_kernel__)
#       define OS_FREEBSD 1
#endif         /* OS_FREEBSD */
#if defined(__OpenBSD__)
#       define OS_OPENBSD 1
#endif         /* OS_OPENBSD */
#if defined(__NetBSD__)
#       define OS_NETBSD  1
#elif defined(__NetBSD_Version__)
#       define OS_NETBSD  1
#endif         /* OS_NETBSD  */

#if !defined(OS_WINDOWS)
#       define OS_WINDOWS 0
#endif         /* !defined(OS_WINDOWS) */
#if !defined(OS_MAC)
#       define OS_MAC     0
#endif         /* !defined(OS_MAC)     */
#if !defined(OS_LINUX)
#       define OS_LINUX   0
#endif         /* !defined(OS_LINUX)   */
#if !defined(OS_FREEBSD)
#       define OS_FREEBSD 0
#endif         /* !defined(OS_FREEBSD) */
#if !defined(OS_OPENBSD)
#       define OS_OPENBSD 0
#endif         /* !defined(OS_OPENBSD) */
#if !defined(OS_NETBSD)
#       define OS_NETBSD  0
#endif         /* !defined(OS_NETBSD)  */

#if !(OS_WINDOWS || OS_MAC || OS_LINUX || OS_FREEBSD || OS_OPENBSD || OS_NETBSD)
#       error "seros: Unrecognised operating system / kernel environment."
#endif        /* !(OS_WINDOWS || OS_MAC || OS_LINUX || OS_FREEBSD || OS_OPENBSD || OS_NETBSD)  */

/**........................................................
// Base types                                            */

typedef void      U0;
typedef uint8_t   U8;
typedef uint16_t  U16;
typedef uint32_t  U32;
typedef uint64_t  U64;
typedef uintptr_t Uptr;
typedef size_t    Usize;
typedef int8_t    I8;
typedef int16_t   I16;
typedef int32_t   I32;
typedef int64_t   I64;
typedef intptr_t  Iptr;
typedef ptrdiff_t Isize;
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
#       define CompilerExt(...) ((U0)0)
#endif         /*   CompilerExt  */

#if GNU_COMPILER || CLANG_COMPILER
#       define TypeOf(t) __typeof__(t)
#       define AlignOf(t) __alignof__(t)
#elif MSVC_COMPILER
#       define AlignOf(t) __alignof
#elif STD_C23
#       define TypeOf(t) typeof(t)
#       define AlignOf(t) alignof(t)
#elif STD_C11
#       define AlignOf(t) _Alignof(t)
#endif         /* TypeOf, AlignOf  */

/* Note that the #else branch implementation of offsetof fails UBSAN;    */
/* instead use __builtin_offsetof() available since GCC 4 and Clang 4.   */
/* [Source] https://lkml.iu.edu/hypermail/linux/kernel/2604.0/01424.html */

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
#define restrict __restrict__

/**........................................................
// Common compiler attribute defines                     */

#if GNU_COMPILER || CLANG_COMPLIER
#       define WeakReference(p, a) p CompilerExt(weak, alias(#a))
#else
#       define WeakReference(p, a) ((U0)(p), (U0)(a))
#endif         /* WeakReference */

#if GNU_COMPILER || CLANG_COMPILER
#       define AlignType(x) CompilerExt(aligned(x))
#elif MSVC_COMPILER
#       define AlignType(x) CompilerExt(align(x))
#endif        /*  AlignType */

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

/**........................................................
// Memfunctions                                          */

/* memfunctions live in core and not base_string.h which differs from the C Standard    */
/* bundling them in <string.h>. Cstrings and raw byte buffers are both just contiguous  */
/* memory, and the memfunctions operate on them both. Whether the grouping made sense   */
/* is left as an exercise for the reader (the author has no metric but subjectively     */
/* believes it to be so) but the thought behind is that the compilers (GNU/Clang)       */
/* expects these definitions regardless as it recognises patterns that replaces loops   */
/* to generated memfunc calls for speed. The flags -fno-builtin and -ffreestanding does */
/* not matter here as seros calls the __builtin functions directly, meaning that the    */
/* complier will consistently insert memfunc calls and expect a reference to them,      */
/* either from linking with libc or your own supplied definitions.                      */
/* [Cosmopolitan]                                                                       */
/* [Musl] https://git.musl-libc.org/cgit/musl/tree/src/string/memcpy.c                  */

/* dst and src may overlap */

U0 *
memmove(U0 *restrict dst, const U0 *restrict src, Usize n)
{
        U8 *d = (U8*) dst;
        const U8 *s = (U8*) src;

        if (n == 0)
                return (U0*) d;
        if (n == 1) {
                *d = *s;
                return (U0*) d;
        }

        #if ARCH_X64 && HAS_COMPILER_BUILTINS

                U16 frntw, backw;
                U32 frntl, backl;
                U64 frntq, backq;

                if (n <= 16 && !(n <= 1)) {
                        if (n >= 8) {
                                __builtin_memcpy(&frntq, s, 8);
                                __builtin_memcpy(&backq, s+n-8, 8);
                                __builtin_memcpy(d, &frntq, 8);
                                __builtin_memcpy(d+n-8, &backq, 8);
                        } else if (n >= 4) {                        /* eg: s is pointing to [0 1 2 3 4 5], n=6  */
                                __builtin_memcpy(&frntl, s, 4);     /* [0 1 2 3], cpy 4bs to frntl              */
                                __builtin_memcpy(&backl, s+n-4, 4); /* [    2 3 4 5], s+n-4=2, cpy 4bs to backl */
                                __builtin_memcpy(d, &frntl, 4);     /* [0 1 2 3], cpy 4bs frm frntl to d        */
                                __builtin_memcpy(d+n-4, &backl, 4); /* [0 1 2 3 4 5], d+n-4=2, cpy 4bs frm backl to d pointing at 2 */
                        } else if (n >= 2) {
                                __builtin_memcpy(&frntw, s, 2);
                                __builtin_memcpy(&frntw, s, 2);
                                __builtin_memcpy(&frntw, s, 2);
                                __builtin_memcpy(&frntw, s, 2);
                        } else {
                                for (; n; n--) *d++ = *s++;
                        }
                }

        #else /* TODO: ARCH_ARM64 */
                for (; n; n--) *d++ = *s++;
        #endif
                return dst;
}

U0 *
memset(U0 *restrict s, I32 c, Usize n)
{
        U8 *d = (U8*)s;

        if (len >= 4 && len <= 7) {

        } else {
                for (; n; n--) *d++ = (I8)c;
        }
        return s;
}

I32
memcmp(U0 s1, const U0 s2, Usize n)
{
}

// thin dispatcher
static inline U0 *
mset(U0 *restrict s, I32 c, Usize n)
{
        return memset(s, c, n);
}

static inline U0 *
mmove(U0 dst, const U0 src, Usize n)
{
        return memmove(dst, src, n);
}
#endif /* SEROS_BASE_CORE */
