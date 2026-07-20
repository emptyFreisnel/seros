/**........................................................
// C core utilites and basic types.                      

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

#include <stdint.h>
#include <stddef.h>

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

/* Windows, Linux and Mac */
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
// Keyword and compiler attribute wrappers               */

#define asm __asm__
#define volatile __volatile__

#define private static

#if STD_C23
#       define NIL nullptr
#else          /* !STD_C23 */
#       define NIL ((U0*)0)
#endif 

#if GNU_COMPILER || CLANG_COMPILER
#       define always_inline inline __attribute__((__always_inline__))
#else          /* !(GNU_COMPILER || CLANG_COMPILER) */
#       define always_inline inline
#endif         /*   GNU_COMPILER || CLANG_COMPILER  */

#if GNU_COMPILER || CLANG_COMPILER
#       define TypeOf(t) __typeof__(t)
#elif STD_C23
#       define TypeOf(t) typeof(t)
#endif         /*   GNU_COMPILER || CLANG_COMPILER  */

#ifndef offsetof
#       define OffsetOf(T, m) ((U64) &((T*)0)->m)
#else          /* defined(offsetof) */
#       define OffsetOf(T, m) offsetof(T, m)
#endif         /* !offsetof */

/**........................................................
// Units                                                 */

#define KB(n) (((U64)(n))<<10)
#define MB(n) (((U64)(n))<<20)
#define GB(n) (((U64)(n))<<30)
#define TB(n) (((U64)(n))<<40)

/**........................................................
// Asserts and Typechecking                              

* When using HintAssert, compile with -fsanitize=undefined
* to enable UndefinedBehaviourSanitizer to detect UB at runtime.

* Alternatively, compile with just -fsanitize=unreachable
* and -fsanitize-trap=unreachable if one finds further sanitizer
* machinery unnecessary. On higher optimizations without -fsanitize,
* the compiler understands that __builtin_unreachable() is an invalid
* code path and will skip generating assembly for the while loop.
*
* [Clang]
* https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html#ubsan-checks
*
* [GCC]
* https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html */

#ifndef ASSERT_ALL
#       define ASSERT_ALL     1
#endif

#if ASSERT_ALL
#  ifndef COMPILE_ASSERT
#       define COMPILE_ASSERT 1
#  endif
#  ifndef RUNTIME_ASSERT
#       define RUNTIME_ASSERT 1
#  endif
#  ifndef HINT_ASSERT
#       define HINT_ASSERT    1
#  endif
#endif

#ifndef COMPILE_ASSERT
#       define COMPILE_ASSERT 0
#endif
#ifndef RUNTIME_ASSERT
#       define RUNTIME_ASSERT 0
#endif
#ifndef HINT_ASSERT
#       define HINT_ASSERT    0
#endif

#if COMPILE_ASSERT
#  if STD_C11 || GNU_COMPILER || CLANG_COMPILER
#       define CompileAssert(...) _Static_assert(__VA_ARGS__)
#  else        /* !(STD_C11 || GNU_COMPILER || CLANG_COMPILER) */
#       define CompileAssert(...) ((U0)(__VA_ARGS__))
#  endif       /* STD_C11 || GNU_COMPILER || CLANG_COMPILER    */
#else          /* !COMPILE_ASSERT */
#       define CompileAssert(...) ((U0)(__VA_ARGS__))
#endif         /*  COMPILE_ASSERT */

#if RUNTIME_ASSERT
#  if GNU_COMPILER || CLANG_COMPILER
#       define RuntimeAssert(c) do { if (!(c)) __builtin_trap(); } while(0)
#  elif MSVC_COMPILER
#       define RuntimeAssert(c) do { if (!(c)) __debugbreak();   } while(0)
#  else        /* !(GNU_COMPILER || CLANG_COMPILER) && MSVC_COMPLIER */
#       define RuntimeAssert(c) ((U0)(c))
#  endif       /*   GNU_COMPILER || CLANG_COMPILER && MSVC_COMPLIER  */
#else          /* !RUNTIME_ASSERT */
#       define RuntimeAssert(c) ((U0)(c))
#endif         /*  RUNTIME_ASSERT */

#if HINT_ASSERT
#  if GNU_COMPILER || CLANG_COMPILER
#       define HintAssert(c) while (!(c)) __builtin_unreachable()
#  elif MSVC_COMPILER
#       define HintAssert(c) while (!(c)) __assume(0)
#  else        /* !(GNU_COMPILER || CLANG_COMPILER) && MSVC_COMPLIER */
#       define HintAssert(c) ((U0)(c))
#  endif       /* GNU_COMPILER || CLANG_COMPILER */
#else          /* !HINT_ASSERT */
#       define HintAssert(c) ((U0)(c))
#endif         /*  HINT_ASSERT */

/**........................................................
// Debugging, poisoning and address sanitizer utilities  */

typedef enum PoisonPtrTrait PoisonPtrTrait;
enum PoisonPtrTrait {

};

#ifndef DEBUG
#       define DEBUG 0
#endif         /* !DEBUG */

#ifndef DIAGNOSIC
#       define DIAGNOSTIC 1
#endif         /* !DIAGNOSTIC */

#ifndef TRACE
#define TRACE 1
#endif
        
#if GNU_COMPILER || CLANG_COMPILER
#  if defined(__has_feature)
#    if __has_feature(address_sanitizer)
#       define ASAN_ENABLED 1
#    endif     /* __has_feature(address_sanitizer) */
#  endif       /* defined(__has_feature) */

#  elif defined(__SANITIZE_ADDRESS__)
#       define ASAN_ENABLED 1
#  endif       /* defined(__SANITIZE_ADDRESS__) */
#endif         /* GNU_COMPILER || CLANG_COMPILER */

#if GNU_COMPILER || CLANG_COMPILER
#       define PtrInvalidate(a, n) ({                                                            \
               CompileAssert(__builtin_classify_type(a) == __builtin_classify_type((U0*)0) &&    \
                             __builtin_classify_type(n) == __builtin_classify_type((S32)0)       \
                             "PtrInvalidate: a must be a ptr and n must be an integer.");        \
               do { (a) = ((U0*)-n); } while(0);                                                 \
        })
#       define PtrIsInvalidated(a, n) ((x) == (U0*)(Iptr)-n)
#elif
#       define PtrInvalidate(a, n) do { (a) = ((U0*)-n); } while(0)
#else          /* !(GNU_COMPILER || CLANG_COMPILER) */
#       define PtrInvalidate(a, n) (((U0)(a) = (a)), (U0)(n))
#endif         /*   GNU_COMPILER || CLANG_COMPILER  */

#if DEBUG && ASAN_ENABLED
#       define DBG_PoisonMemRegion(a, s)   __asan_poison_memory_region((a), (s))
#       define DBG_UnpoisonMemRegion(a, s) __asan_unpoison_memory_region((a), (s))
#else          /* !(DEBUG && ASAN_ENABLED) */
#       define DBG_PoisonMemRegion(a, s)   ((U0)(a), (U0)(s))
#       define DBG_UnpoisonMemRegion(a, s) ((U0)(a), (U0)(s))
#endif         /*  DEBUG && ASAN_ENABLED   */

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
// Struct member offset macros to emulate inheritance.   */

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
