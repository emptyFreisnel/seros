/**..........................................................................
//  Min, Max, Clamp and Swap Functions

*  Assume additional stack traffic when using these in debug builds.
*  Your average optimizing compiler can inline this during release.
*  See SEI Cert C Coding Standard (Edition 2016): page 26 and 27.           */

static inline I16 maxI16(I16 x, I16 y) { return (x > y) ? x : y; };
static inline I32 maxI32(I32 x, I32 y) { return (x > y) ? x : y; };
static inline I64 maxI64(I64 x, I64 y) { return (x > y) ? x : y; };
static inline U16 maxU16(U16 x, U16 y) { return (x > y) ? x : y; };
static inline U32 maxU32(U32 x, U32 y) { return (x > y) ? x : y; };
static inline U64 maxU64(U64 x, U64 y) { return (x > y) ? x : y; };
static inline F32 maxF32(F32 x, F32 y) { return (x > y) ? x : y; };
static inline F64 maxF64(F64 x, F64 y) { return (x > y) ? x : y; };
                                                              
static inline I16 minI16(I16 x, I16 y) { return (x < y) ? x : y; };
static inline I32 minI32(I32 x, I32 y) { return (x < y) ? x : y; };
static inline I64 minI64(I64 x, I64 y) { return (x < y) ? x : y; };
static inline U16 minU16(U16 x, U16 y) { return (x < y) ? x : y; };
static inline U32 minU32(U32 x, U32 y) { return (x < y) ? x : y; };
static inline U64 minU64(U64 x, U64 y) { return (x < y) ? x : y; };
static inline F64 minF32(F64 x, F64 y) { return (x < y) ? x : y; };
static inline F32 minF64(F32 x, F32 y) { return (x < y) ? x : y; };

static inline I32
clampI32(I32 val, I32 min, I32 max) {
        if (val < min) return min;
        if (val > max) return max;
        return val;
}

static inline U0
swapI32(I32 *x, I32 *y) {
        I32 t = *x;
        *x = *y;
        *y = t;
}
