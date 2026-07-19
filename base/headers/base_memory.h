#ifdef __cplusplus
extern "C" {
#endif

typedef struct Arena Arena;
struct Arena {
        U0 *base;
        I64 len;
        I64 used;
};

#ifdef __cplusplus
}
#endif
