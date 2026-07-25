/**..........................................................................
//  Min, Max, Clamp and Swap Functions

*  The Max, Min, Clamp and Swap functions are generated using X-macros.
*  Assume additional stack traffic when using these in debug builds.
*  Your average optimizing compiler can inline this during release.
*  See SEI Cert C Coding Standard (Edition 2016): page 26 and 27.          */

#define MakeMaxFn(T) static inline T max##T(T x, T y) { return (x > y) ? x : y; }
#define MakeMinFn(T) static inline T min##T(T x, T y) { return (x < y) ? x : y; }
#define MakeSwapFn(T) static inline U0 swap##T(T *x, T*y) { T t = *x; *x = *y; *y = t; }

#define MakeClampFn(T)                          \
        static inline T                         \
        clamp##T(T val, T min, T max) {         \
                if (val < min) return min;      \
                if (val > max) return max;      \
                return val;                     \
        }

XMacroNumTypes(MakeMaxFn)
XMacroNumTypes(MakeMinFn)
XMacroNumTypes(MakeSwapFn)
XMacroNumTypes(MakeClampFn)

#undef MakeMaxFn
#undef MakeMinFn
#undef MakeSwapFn
#undef MakeClampFn
