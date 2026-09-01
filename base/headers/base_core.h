/**........................................................
// C core types and constants                            */

/* Key defines and core function stubs for programs to
   compile in an environment without any need or hard
   dependency for the C standard library.                */

/* [Mr4thProgramming's base layer series.]
   https://www.youtube.com/watch?v=8fJ4vWrkS4o&list=PLT6InxK-XQvNKTyLXk6H6KKy12UYS_KDL
   [Pre-defined Compiler Macros]
   https://sourceforge.net/projects/predef/
   [raddebugger]
   https://github.com/EpicGames/raddebugger              */

#ifndef SEROS_BASE_CORE
#define SEROS_BASE_CORE

/**........................................................
// Freestanding/standalone header includes.              */

#include <stdarg.h>  /* For va_args/va_list              */
#include <stdint.h>  /* For fixed width types eg int32_t */
#include <stddef.h>  /* For size_t and ptrdiff_t         */

#if !defined(SEROS_FREESTANDING)
#       define SEROS_FREESTANDING 0
#       define SEROS_HAS_CRT      1
#endif         /* SEROS_FREESTANDING 0, SEROS_HAS_CRT 1  */

#if !defined(SEROS_FREESTANDING)
#       define SEROS_FREESTANDING 0
#endif         /* !defined(SEROS_FREESTANDING) */
#if !defined(SEROS_HAS_CRT)
#       define SEROS_HAS_CRT (!SEROS_FREESTANDING)
#endif         /* !defined(SEROS_HAS_CRT) */

/**........................................................
// Codebase keywords and API function specifiers.        */

#define UTAPI static                  /* base_utils.h    */
#define STAPI static                  /* base_stringio.h */
#define INAPI static                  /* base_intrin.h   */

#undef internal
#define internal        static
#define internal_helper static

#define asm __asm__
#define volatile __volatile__
#define restrict __restrict__

#undef NULL
#if STD_C23
#       define NULL nullptr
        typedef TypeOf(NULL) /* nullptr_t */ nptr;
#else          /* !STD_C23 */
#       define NULL ((u0*)0)
#endif         /* NULL */

/**........................................................
// Linkage Keyword macros                                */

#if defined(__cplusplus)
#       define LANG_CPP 1
#else          /* !__cplusplus */
#       define LANG_C   1
#endif         /*  __cplusplus */

#if !defined(__cplusplus)
#       define LANG_CPP 0
#endif

#if LANG_CPP
#       define C_LINKAGE_BEGIN extern "C" {
#       define C_LINKAGE_END }
#       define C_LINKAGE extern "C"
#else
#       define C_LINKAGE_BEGIN
#       define C_LINKAGE_END
#       define C_LINKAGE
#endif

/**........................................................
// C standard delegation.                                */

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
// Compiler vendor delegation.                           */

#if defined(__clang__)
#       define CLANG_COMPILER 1
#elif defined(__GNUC__)
#       define GNU_COMPILER   1
#elif defined(_MSC_VER)
#       define MSVC_COMPILER  1
#endif         /* CLANG_COMPILER, GNU_COMPILER, MSVC_COMPILER */

#if !defined(CLANG_COMPILER)
#       define CLANG_COMPILER 0
#endif         /* !defined(CLANG_COMPILER) */
#if !defined(GNU_COMPILER)
#       define GNU_COMPILER   0
#endif         /* !defined(GNU_COMPILER)   */
#if !defined(MSVC_COMPILER)
#       define MSVC_COMPILER  0
#endif         /* !defined(MSVC_COMPILER)  */

#if GNU_COMPILER || CLANG_COMPILER
#       define COMPILER_HAS_BUILTINS   1
#       define COMPILER_HAS_ATTRIBUTES 1
#elif MSVC_COMPILER
#       define HAS_MSVC_INTRINSICS     1
#endif         /* COMPILER_HAS_BUILTINS, COMPILER_HAS_ATTRIBUTES, HAS_MSVC_INTRINSICS */

#if !defined(COMPILER_HAS_BUILTINS)
#       define COMPILER_HAS_BUILTINS   0
#endif         /* !defined(COMPILER_HAS_BUILTINS)   */
#if !defined(COMPILER_HAS_ATTRIBUTES)
#       define COMPILER_HAS_ATTRIBUTES 0
#endif         /* !defined(COMPILER_HAS_ATTRIBUTES) */
#if !defined(HAS_MSVC_INTRINSICS)
#       define HAS_MSVC_INTRINSICS     0
#endif         /* !defined(HAS_MSVC_INTRINSICS) */

#if !(CLANG_COMPILER || GNU_COMPILER || MSVC_COMPILER)
#       warning "seros: Unrecognised compiler. Proceed with caution."
#endif

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
#endif         /* ARCH_X64   */

#if defined(i386)
#       define ARCH_X86 1
#elif defined(__i386__)
#       define ARCH_X86 1
#elif defined(__i386)
#       define ARCH_X86 1
#elif defined(_M_IX86)
#       define ARCH_X86 1
#endif         /* ARCH_X86   */

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
#       define ARCH_MIPS 1
#elif defined(__mips)
#       define ARCH_MIPS 1
#endif         /* ARCH_MIPS  */

#if !defined(ARCH_X64)
#       define ARCH_X64   0
#endif         /* !defined(ARCH_X64)   */
#if !defined(ARCH_X86)
#       define ARCH_X86   0
#endif         /* !defined(ARCH_X86)   */
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
#endif         /* !defined(ARCH_MIPS)  */

#if !(ARCH_X64 || ARCH_X86 || ARCH_ARM64 || ARCH_ARM32 || ARCH_RISCV || ARCH_MIPS)
#       error "seros: Unrecognised processor."
#endif

/**........................................................
// Pointer width and SIMD availability.                  */

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
#endif         /* ARCH_64BIT, ARCH_32BIT */

#if ARCH_X64
#  if defined(__SSE__)
#       define SIMD_SSE  1
#  endif       /* __SSE__ */
#  if defined(__AVX2__)
#       define SIMD_AVX2 1
#  endif       /* __AVX2__ */
#endif         /* SIMD_SSE, SIMD_AVX2 */

#if ARCH_ARM64 && defined(__SVE__)
#       define SIMD_SVE  1
#endif         /*  SIMD_SVE */

#if !defined(ARCH_64BIT)
#       define ARCH_64BIT 0
#endif         /* !defined(ARCH_64BIT) */
#if !defined(ARCH_32BIT)
#       define ARCH_32BIT 0
#endif         /* !defined(ARCH_32BIT) */

#if !defined(SIMD_SSE)
#       define SIMD_SSE  0
#endif         /* !defined(SIMD_SSE)  */
#if !defined(SIMD_AVX2)
#       define SIMD_AVX2 0
#endif         /* !defined(SIMD_AVX2) */
#if !defined(SIMD_SVE)
#       define SIMD_SVE  0
#endif         /* !defined(SIMD_SVE)  */

#if !(ARCH_64BIT || ARCH_32BIT)
#       error "seros: Unrecognised architecture"
#endif

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

/* All the types here are named to bit-widths lengths.   */

typedef void      u0;
typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;
typedef uintptr_t uptr;
typedef size_t    usize;
typedef int8_t    i8;
typedef int16_t   i16;
typedef int32_t   i32;
typedef int64_t   i64;
typedef intptr_t  iptr;
typedef ptrdiff_t isize;
typedef u8        b8;
typedef u16       b16;
typedef u32       b32;
typedef u64       b64;
typedef float     f32;
typedef double    f64;

#define XMacroNumTypes(X) X(u16) X(u32) X(u64) X(i16) X(i32) X(i64) X(f32) X(f64)

typedef u0 Proc(u0);

typedef union u128 u128;
union u128 {
	u8  _u8[16];
	u16 _u16[8];
	u32 _u32[4];
	u64 _u64[2];
        f32 _f32[4];
        f64 _f64[2];
};

typedef union u256 u256;
union u256 {
	u8    _u8[32];
	u16   _u16[16];
	u32   _u32[8];
	u64   _u64[4];
        u128 _u128[2];
        f32   _f32[8];
        f64   _f64[4];
};

/**........................................................
// Compiler attribute wrappers                           */

#if COMPILER_HAS_ATTRIBUTES
#       define CompilerExt(...) __attribute__((__VA_ARGS__))
#elif MSVC_COMPILER
#       define CompilerExt(...) __declspec((__VA_ARGS__))
#else          /* !COMPILER_HAS_ATTRIBUTES vs MSVC_COMPILER */
#       define CompilerExt(...) ((u0)0)
#endif         /* CompilerExt  */

#if GNU_COMPILER || CLANG_COMPILER
#       define TypeOf(t)  __typeof__(t)
#       define AlignOf(t) __alignof__(t)
#elif MSVC_COMPILER
#       define TypeOf(t)  __typeof__(t)
#       define AlignOf(t) __alignof(t)
#elif STD_C23
#       define TypeOf(t)  typeof(t)
#       define AlignOf(t) alignof(t)
#elif STD_C11
#       define AlignOf(t) _Alignof(t)
#endif         /* TypeOf, AlignOf  */

#if STD_C11
#       define Generic(...) _Generic(__VA_ARGS__)
#elif COMPILER_HAS_BUILTINS // from freebsd cdefs.h - todo
#       define Generic(...) __builtin_choose_expr(__builtin_types_compatible_p(TypeOf(((u0)0, (__VA_ARGS__))), t), yes, no)
#else          /* !STD_C11 vs !COMPILER_HAS_BUILTINS */
#       define Generic(...) ((u0)0)
#endif         /* Generic */

/**........................................................
// Common compiler attribute defines                     */

#if COMPILER_HAS_ATTRIBUTES
#       define WeakReference(sym, a)   TypeOf(sym) (a) CompilerExt(weak, alias(#sym))
#       define StrongReference(sym, a) TypeOf(sym) (a) CompilerExt(alias(#sym))
#elif MSVC_COMPILER
#  if ARCH_X64 || ARCH_ARM64
#       define WeakReference(sym, a) __pragma(comment(linker, "/alternatename:" #a "=" #sym))
#  elif ARCH_X86
#       define WeakReference(sym, a) __pragma(comment(linker, "/alternatename:_" #a "=_" #sym))
#  endif       /* ARCH_X64 || ARCH_ARM64 vs ARCH_X86 */
#else          /* !COMPILER_HAS_ATTRIBUTES vs MSVC_COMPILER */
#       define WeakReference(sym, a)   ((u0)(sym), (u0)(a))
#       define StrongReference(sym, a) ((u0)(sym), (u0)(a))
#endif         /* WeakReference, StrongReference */

#if COMPILER_HAS_ATTRIBUTES
#       define AlignType(x) CompilerExt(__aligned__(x))
#elif MSVC_COMPILER
#       define AlignType(x) CompilerExt(align(x))
#else          /* !COMPILER_HAS_ATTRIBUTES vs MSVC_COMPILER   */
#       define AlignType(x) ((u0)(x))
#endif         /*  AlignType */

#if COMPILER_HAS_ATTRIBUTES
#       define always_inline inline CompilerExt(__always_inline__)
#       define noinline CompilerExt(__noinline__)
#elif MSVC_COMPILER
#else 
#       define always_inline inline
#       define noinline
#endif         /* always_inline, noinline */

/**........................................................
// Builtin function wrappers                             */

/* Branch predictors, stack allocators etc */

/* Note that the branch implementation of offsetof fails UBSAN;
   instead use __builtin_offsetof() available since GCC 4 and Clang 4.
   [Source] https://lkml.iu.edu/hypermail/linux/kernel/2604.0/01424.html */

#undef offsetof
#if COMPILER_HAS_BUILTINS
#       define OffsetOf(T, m) __builtin_offsetof(T, m)
#else          /* !COMPILER_HAS_BUILTINS */
#       define OffsetOf(T, m) ((u64) &((T*)0)->m)
#endif         /* OffsetOf */

#if COMPILER_HAS_BUILTINS
#       define Alloca(s) __builtin_alloca(s)
#else          /* !COMPILER_HAS_BUILTINS */
#       define Alloca(s) ((u0)(s))
#endif         /* Alloca */

#if COMPILER_HAS_BUILTINS
#       define Expect(e, v) __builtin_expect((e), (v))
#       define Likely(e) Expect((e), 1)
#       define Unlikely(e) Expect((e), 0)
#else          /* !COMPILER_HAS_BUILTINS */
#       define Expect(e, v) ((u0)(e), (u0)(v))
#       define Likely(e) ((u0)(e))
#       define Unlikely(e) ((u0)(e))
#endif         /* Expect  */

/**........................................................
// Basic constants                                       */

#define I8FLOOR  (i8) 0x80
#define I16FLOOR (i16) 0x8000
#define I32FLOOR (i32) 0x80000000
#define I64FLOOR (i64) 0x8000000000000000ull

#define I8CEIL  (i8) 0x7f
#define I16CEIL (i16) 0x7fff
#define I32CEIL (i32) 0x7fffffff
#define I64CEIL (i64) 0x7fffffffffffffffull

#define U8CEIL  0xffu
#define U16CEIL 0xffffu
#define U32CEIL 0xffffffffu
#define U64CEIL 0xffffffffffffffffull

#define F32MACHEPS 1.1920929e-7f
#define F64MACHEPS 2.2204460492503131e-16

/* Commas are not included in the length */
#define I32MAXLEN 11 /* "-2,147,483,648" */ 
#define U32MAXLEN 10 /* " 4,294,967,295" */
#define I64MAXLEN 20 /* "-9,223,372,036,854,775,808"  */
#define U64MAXLEN 20 /* " 18,446,744,073,709,551,615" */

#define F32INFINITY_BITS     0x7f800000
#define F64INFINITY_BITS     0x7ff0000000000000ull
#define NEG_F32INFINITY_BITS 0xff800000
#define NEG_F64INFINITY_BITS 0xfff0000000000000ull

#if COMPILER_HAS_BUILTINS
#       define F32INFINITY     __builtin_inff(u0)
#       define F64INFINITY     __builtin_inf(u0)
#       define NEG_F32INFINITY (-F32INFINITY)
#       define NEG_F64INFINITY (-F64INFINITY)
#else
#       define F32INFINITY ((f32) (1e300*1e300))
#       define F64INFINITY ((f64) (1e300*1e300))
#       define NEG_F32INFINITY (-F32INFINITY)
#       define NEG_F64INFINITY (-F64INFINITY)
#endif

/**........................................................
// Units                                                 */

#define KB(n) (((u64)(n))<<10)
#define MB(n) (((u64)(n))<<20)
#define GB(n) (((u64)(n))<<30)
#define TB(n) (((u64)(n))<<40)

#endif /* SEROS_BASE_CORE */
