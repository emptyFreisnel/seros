#ifndef SEROS_BASE_SCALL_LYR
#define SEROS_BASE_SCALL_LYR

/**........................................................
// Unix-like direct syscall interface.                       */

// Theses are userspace stubs to syscalls.

/* [Chromium] https://chromium.googlesource.com/linux-syscall-support
 * [Linux]
 * [FreeBSD] https://github.com/freebsd/freebsd-src/blob/main/sys/sys/syscall.h
 */

#if OS_LINUX
#  if ARCH_X64 || ARCH_X86
#       include <asm/unistd.h>
#  elif ARCH_ARM64
#       include <asm-generic/unistd.h>
#  endif
#elif OS_FREEBSD
#       include <sys/syscalls.h>
#else
#       error "seros: No syscall interface for this operating system / kernel environment."
#endif

/* SyscallNum(): for syscalls that has no name changes between cross kernel/OS implementations.
 * Dispatches syscall numbers depending on the kernel/OS or architecture.
 * Use SyscallNumDispatch() if names are not the same; examples of which are __NR_exit vs
 * SYS__exit in Linux and FreeBSD respectively.
 */

#define SyscallNum(name) SyscallNumDispatch(name, name)

#if OS_LINUX
#       define SyscallNumDispatch(lnux, fbsd) __NR_##lnux
#elif OS_FREEBSD
#       define SyscallNumDispatch(lnux, fbsd) SYS_##fbsd
#endif

#define UNIMPLEMENTED (sizeof(struct Unimplemented))

extern Iptr __scall0(Iptr _nr);
extern Iptr __scall1(Iptr _a1, Iptr _nr);
extern Iptr __scall2(Iptr _a1 , Iptr _a2, Iptr _nr);
extern Iptr __scall3(Iptr _a1 , Iptr _a2, Iptr _a3, Iptr _nr);
extern Iptr __scall4(Iptr _a1 , Iptr _a2, Iptr _a3, Iptr _a4, Iptr _nr);
extern Iptr __scall5(Iptr _a1 , Iptr _a2, Iptr _a3, Iptr _a4, Iptr _a5, Iptr _nr);
extern Iptr __scall6(Iptr _a1 , Iptr _a2, Iptr _a3, Iptr _a4, Iptr _a5, Iptr _a6, Iptr _nr);

static inline I64
read_(I32 fd, U0 *buf, U64 cnt)
{
        return __scall3((Iptr)fd, (Iptr)buf, (Iptr)cnt, SyscallNum(read));
}

static inline I64
wrte_(I32 fd, const U0 *buf, U64 cnt)
{
        return __scall3((Iptr)fd, (Iptr)buf, (Iptr)cnt, SyscallNum(write));
}

static inline I64
open_(const U0 *path, I32 flags, U32 mode)
{
        return __scall3((Iptr)path, (Iptr)flags, (Iptr)mode, SyscallNum(open));
}

static inline I64
clse_(I32 fd)
{
        return __scall1((Iptr)fd, SyscallNum(close));
}

static inline I64
mmap_(U0 *addr, I32 len, I32 prot, I32 flags, I32 fd, I64 offset)
{
        return __scall6((Iptr)addr, (Iptr)len, (Iptr)prot, (Iptr)flags, (Iptr)fd, (Iptr)offset,
                        SyscallNum(mmap));
}

static inline I64
exit_(I32 status)
{
        return __scall1((Iptr)status, SyscallNumDispatch(/* lnux */ exit,
                                                         /* fbsd */ _exit));
}

#endif /* SEROS_BASE_SCALL_LYR */
