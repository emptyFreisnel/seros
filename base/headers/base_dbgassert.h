/**........................................................
// Asserts.                                              */

#if !defined(ASSERT_ALL)
#       define ASSERT_ALL     1
#endif         /* !ASSERT_ALL */

#if ASSERT_ALL
#  if !defined(COMPILE_ASSERT)
#       define COMPILE_ASSERT 1
#  endif       /* !COMPILE_ASSERT */
#  if !defined(RUNTIME_ASSERT)
#       define RUNTIME_ASSERT 1
#  endif       /* !RUNTIME_ASSERT */
#  if !defined(HINT_ASSERT)
#       define HINT_ASSERT    1
#  endif       /* !HINT_ASSERT    */
#endif         /*  ASSERT_ALL  */

#if !defined(COMPILE_ASSERT)
#       define COMPILE_ASSERT 0
#endif         /* !COMPILE_ASSERT */
#if !defined(RUNTIME_ASSERT)
#       define RUNTIME_ASSERT 0
#endif         /* !RUNTIME_ASSERT */
#if !defined(HINT_ASSERT)
#       define HINT_ASSERT    0
#endif         /* !HINT_ASSERT */

#if !defined(ASSERT_USE_HINT)
#       define ASSERT_USE_HINT 1
#endif         /* !ASSERT_USE_HINT */

#if !defined(ASSERT_USE_DIAGNOSTIC)
#       define ASSERT_USE_DIAGNOSTIC 0
#endif         /* !ASSERT_USE_DIAGNOSTIC */

#if ASSERT_USE_DIAGNOSTIC
#       define Diagnostic(s, ...) ((u0)(s), ##__VA_ARGS__)
#else          /* !ASSERT_USE_DIAGNOSTIC */
#       define Diagnostic(s, w) ((u0)(s), (u0)(w))
#endif         /* Diagnostic */

#if COMPILE_ASSERT
#  if STD_C11 || GNU_COMPILER || CLANG_COMPILER
#       define CompileAssert(...) _Static_assert(__VA_ARGS__)
#  else        /* !(STD_C11 || GNU_COMPILER || CLANG_COMPILER) */
#       define CompileAssert(...) ((u0)0)
#  endif       /* STD_C11 || GNU_COMPILER || CLANG_COMPILER    */
#else          /* !COMPILE_ASSERT */
#       define CompileAssert(...) ((u0)0)
#endif         /* CompileAssert   */

/* RuntimeAssert: Diagnostic prints are printed out */

#if RUNTIME_ASSERT
#  if COMPILER_HAS_BUILTINS
#       define RuntimeAssert(c) do { if (Unlikely(!(c))) __builtin_trap(); } while(0)
#  elif HAS_MSVC_INTRINSICS
#       define RuntimeAssert(c) do { if (Unlikely(!(c))) __debugbreak();   } while(0)
#  else        /* !(COMPILER_HAS_BUILTINS) vs HAS_MSVC_INTRINSICS */
#       define RuntimeAssert(c) ((u0)(c))
#  endif       /*  COMPILER_HAS_BUILTINS   vs HAS_MSVC_INTRINSICS */
#else          /* !RUNTIME_ASSERT */
#       define RuntimeAssert(c) ((u0)(c))
#endif         /* RuntimeAssert   */

/* HintAssert: Enable UndefinedBehaviourSanitizer by passing -fsanitize=undefined.    
   If compiled on higher optimization flags without -fsanitize, __builtin_unreachable()  
   (GCC/Clang) or __assume(0) (MSVC) optimizes out the invalidated path; the compiler    
   skips generating assembly for the while loop altogether regardless if the conditional 
   is true or false.                                                                     
   
   Thus, prefer HintAssert as it also allows trapping of illegal instructions by passing 
   -fsanitize-trap=undefined (if needed) for debug builds. For release builds, simply    
   build without passing -fsanitize.                                                     
   
   [ Clang ] https: //clang.llvm.org/docs/UndefinedBehaviorSanitizer.html#ubsan-checks   
   [ GCC   ] https: //gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html            
   [ MSVC  ] https: //learn.microsoft.com/en-us/cpp/intrinsics/assume?view=msvc-170    */

#if HINT_ASSERT
#  if COMPILER_HAS_BUILTINS
#       define HintAssert(c) while (Unlikely(!(c))) __builtin_unreachable()
#  elif HAS_MSVC_INTRINSICS
#       define HintAssert(c) while (Unlikely(!(c))) __assume(0)
#  else        /* !(COMPILER_HAS_BUILTINS || HAS_MSVC_INTRINSICS) */
#       define HintAssert(c) ((u0)(c))
#  endif       /*  COMPILER_HAS_BUILTINS */
#else          /* !HINT_ASSERT */
#       define HintAssert(c) ((u0)(c))
#endif         /* HintAssert */

#if RUNTIME_ASSERT && HINT_ASSERT
#  if ASSERT_USE_HINT
#       define Assert(c) HintAssert(c)
#  else        /* !ASSERT_USE_HINT */
#       define Assert(c) RuntimeAssert(c)
#  endif       /*  ASSERT_USE_HINT */
#else          /* !(RUNTIME_ASSERT && HINT_ASSERT) */
#       define Assert(c) ((u0)(c))
#endif         /* Assert */

/**........................................................
// Debug toggle.                                         */

#if !defined(DEBUG)
#       define DEBUG 0
#endif         /* !DEBUG */

#if DEBUG
#  if ARCH_X64
#       define DebugBreak() asm("int3")
#  elif ARCH_ARM64
#       define DebugBreak() asm("brk\t#0x666")
#  elif COMPILER_HAS_BUILTINS
#       define DebugBreak() __builtin_trap()
#  endif       /* ARCH_X64 || ARCH_ARM64 vs COMPILER_HAS_BUILTINS */
#else          /* !DEBUG */
#       define DebugBreak() ((u0)0)
#endif         /* DebugBreak() */

/**........................................................
// Address Sanitizer wrappers                            */

#if CLANG_COMPILER
#  if defined(__has_feature)
#    if __has_feature(address_sanitizer)
#       define ASAN_ENABLED 1
#    endif     /* __has_feature(address_sanitizer) */
#  elif defined(__SANITIZE_ADDRESS__)
#       define ASAN_ENABLED 1
#  endif       /* defined(__has_feature) */
#endif         /* ASAN_ENABLED */

#if DEBUG && ASAN_ENABLED
C_LINKAGE void __asan_poison_memory_region(void const volatile *addr, size_t size);
C_LINKAGE void __asan_unpoison_memory_region(void const volatile *addr, size_t size);
#       define AsanPoisonMemRegion(a, s)   __asan_poison_memory_region((a), (s))
#       define AsanUnpoisonMemRegion(a, s) __asan_unpoison_memory_region((a), (s))
#else          /* !(DEBUG && ASAN_ENABLED) */
#       define AsanPoisonMemRegion(a, s)   ((u0)(a), (u0)(s))
#       define AsanUnpoisonMemRegion(a, s) ((u0)(a), (u0)(s))
#endif         /* DBG_PoisonMemRegion && DBG_UnpoisonMemRegion */

/**........................................................
// Thread Sanitizer wrappers                             */

#if CLANG_COMPILER
#  if defined(__has_feature)
#    if __has_feature(thread_sanitizer)
#       define TSAN_ENABLED 1
#    endif     /* __has_feature(thread_sanitizer) */
#  elif defined(__SANITIZE_THREAD__)
#       define TSAN_ENABLED 1
#  endif       /* defined(__has_feature) */
#endif         /* TSAN_ENABLED */

/**........................................................
// Poisoned pointers and unmmappable memory markers      */

/* TODO: HandleInvalidate */
#if COMPILER_HAS_BUILTINS
#       define PtrInvalidate(ptr, n)                                                             \
        ({     CompileAssert(__builtin_classify_type(ptr) == __builtin_classify_type((u0*)0) &&  \
                             __builtin_classify_type(n)   == __builtin_classify_type((i32)0),    \
                             "PtrInvalidate: a must be a ptr and n must be an int/hex value.");  \
               do { (ptr) = ((u0*)n); } while(0);                                                \
        })
#else          /* !(COMPILER_HAS_BUILTINS) */
#       define PtrInvalidate(ptr, n) do { (ptr) = ((u0*)n); } while(0)
#endif         /* PtrInvalidate */

#define PtrIsInvalidated(ptr, n) ((ptr) == (u0*)(iptr)n)

/* base_list.h && base_list.c */
#define LISTNODE_POISON_PREVPTR 0xDEAD0001
#define LISTNODE_POISON_NEXTPTR 0xDEAD0002
