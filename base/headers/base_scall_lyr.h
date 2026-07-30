#ifndef SEROS_BASE_SCALL_LYR
#define SEROS_BASE_SCALL_LYR

/**........................................................
// Unix-like direct syscall interface.                       */

/* [Chromium] https://chromium.googlesource.com/linux-syscall-support
 * [Linux]  
 */

// Test
#if OS_LINUX
#       define NR(lnx, fbsd) (lnx)
#elif OS_FREEBSD
#       define NR(lnx, fbsd) (fbsd)
#endif

//extern Iptr read_scall_(Iptr fd, Iptr buf, Iptr count);
extern Iptr __scall3(Iptr _a1 , Iptr _a2, Iptr a3, Iptr _nr);

static inline I64
os_wrte(I32 fd, const U0 *buf, U64 cnt)
{
        return __scall3((Iptr)fd, (Iptr) buf, (Iptr) cnt, NR(1, 4));
}


#endif /* SEROS_BASE_SCALL_LYR */
