/*..........................................................................*/
//* Includes

#include "base_core.h"

/*..........................................................................*/
//* Min, Max, Clamp and Swap Functions

// C compliers will not substitute and inline function calls in debug builds.
// There is still additional stack traffic unless it is compiled with optflags.
// This is just to prevent side effects from using unsafe macros, like the
// ubiquitous min and max macros we all know (and love?).

// See SEI Cert C Coding Standard (Edition 2016): page 26 and 27.

static inline S16 maxS16(S16 x, S16 y) { return (x > y) ? x : y; };
static inline S32 maxS32(S32 x, S32 y) { return (x > y) ? x : y; };
static inline S64 maxS64(S64 x, S64 y) { return (x > y) ? x : y; };
static inline U16 maxU16(U16 x, U16 y) { return (x > y) ? x : y; };
static inline U32 maxU32(U32 x, U32 y) { return (x > y) ? x : y; };
static inline U64 maxU64(U64 x, U64 y) { return (x > y) ? x : y; };
static inline F32 maxF32(F32 x, F32 y) { return (x > y) ? x : y; };
static inline F64 maxF64(F64 x, F64 y) { return (x > y) ? x : y; };
                                                              
static inline S16 minS16(S16 x, S16 y) { return (x < y) ? x : y; };
static inline S32 minS32(S32 x, S32 y) { return (x < y) ? x : y; };
static inline S64 minS64(S64 x, S64 y) { return (x < y) ? x : y; };
static inline U16 minU16(U16 x, U16 y) { return (x < y) ? x : y; };
static inline U32 minU32(U32 x, U32 y) { return (x < y) ? x : y; };
static inline U64 minU64(U64 x, U64 y) { return (x < y) ? x : y; };
static inline F64 minF32(F64 x, F64 y) { return (x < y) ? x : y; };
static inline F32 minF64(F32 x, F32 y) { return (x < y) ? x : y; };

static inline S32
clampS32(S32 val, S32 min, S32 max) {
        if (val < min) return min;
        if (val > max) return max;
        return val;
}

static inline U0
swapS32(S32 *x, S32 *y) {
        S32 t = *x;
        *x = *y;
        *y = t;
}

/*..........................................................................*/


