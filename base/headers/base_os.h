#ifndef SEROS_BASE_OS
#define SEROS_BASE_OS

/**........................................................
// OS architecture delegation.                          */

// TODO: FreeBSD and OpenBSD
#if defined(_WIN32)
#       define OS_WINDOWS 1
#endif         /* OS_WINDOWS */

#if defined(__gnu_linux__)
#       define OS_LINUX 1
#elif defined(__linux__)
#       define OS_LINUX 1
#endif        /* OS_LINUX */

#if defined(__APPLE__)
#       define OS_MAC   1
#elif defined(__MACH__)
#       define OS_MAC   1
#endif         /* OS_MAC */

/**........................................................
// Linux direct syscall interface.                       */

/* [Chromium] https://chromium.googlesource.com/linux-syscall-support
 * [Linux]  
// TODO syscall entry point layers */

#if GNU_COMPILER || CLANG_COMPILER
#  if OS_LINUX && ARCH_X64

        static inline I64
        scall_iface0_(I64 num)
        {
                I64 _ret;
                register I64 _rax asm("rax") = num;
                
                asm volatile("syscall"
                /* Outputs */: "=a"(_ret)
                /* Inputs  */: "0"(_rax)
                /* Clobbers*/: "rcx", "r11", "cc", "memory"              
                );

                return _ret;
        }

        static inline I64
        scall_iface1_(I64 num, I64 _1)
        {
                I64 _ret;
                register I64 _rax asm("rax") = num;
                register I64 _rdi asm("rdi") = _1;
                
                asm volatile("syscall"
                /* Outputs */: "=a"(_ret)
                /* Inputs  */: "r"(rdi), "0"(_rax)
                /* Clobbers*/: "rcx", "r11", "cc", "memory"              
                );

                return _ret;
        }

        static inline I64
        scall_iface2_(I64 num, I64 _1, I64 _2)
        {
                I64 _ret;
                register I64 _rax asm("rax") = num;
                register I64 _rdi asm("rdi") = _1;
                register I64 _rsi asm("rsi") = _2;
                
                asm volatile("syscall"
                /* Outputs */: "=a"(_ret)
                /* Inputs  */: "r"(rdi), "r"(rsi), "0"(_rax)
                /* Clobbers*/: "rcx", "r11", "cc", "memory"              
                );

                return _ret;
        }

        static inline I64
        scall_iface3_(I64 num, I64 _1, I64 _2, I64 _3)
        {
                I64 _ret;
                register I64 _rax asm("rax") = num;
                register I64 _rdi asm("rdi") = _1;
                register I64 _rsi asm("rsi") = _2;
                register I64 _rdx asm("rdx") = _3;
                
                asm volatile("syscall"
                /* Outputs */: "=a"(_ret)
                /* Inputs  */: "r"(rdi), "r"(rsi), "r"(rdx), "0"(_rax)
                /* Clobbers*/: "rcx", "r11", "cc", "memory"              
                );

                return _ret;
        }

        static inline I64
        scall_iface4_(I64 num, I64 _1, I64 _2, I64 _3, I64 _4)
        {
                I64 _ret;
                register I64 _rax asm("rax") = num;
                register I64 _rdi asm("rdi") = _1;
                register I64 _rsi asm("rsi") = _2;
                register I64 _rdx asm("rdx") = _3;
                register I64 _r10 asm("r10") = _4;
                
                asm volatile("syscall"
                /* Outputs */: "=a"(_ret)
                /* Inputs  */: "r"(rdi), "r"(rsi), "r"(rdx),
                               "r"(r10), "0"(_rax)
                /* Clobbers*/: "rcx", "r11", "cc", "memory"              
                );

                return _ret;
        }

        static inline I64
        scall_iface5_(I64 num, I64 _1, I64 _2, I64 _3, I64 _4, I64 _5)
        {
                I64 _ret;
                register I64 _rax asm("rax") = num;
                register I64 _rdi asm("rdi") = _1;
                register I64 _rsi asm("rsi") = _2;
                register I64 _rdx asm("rdx") = _3;
                register I64 _r10 asm("r10") = _4;
                register I64 _r8  asm("r8")  = _5;

                asm volatile("syscall"
                /* Outputs */: "=a"(_ret)
                /* Inputs  */: "r"(_rdi), "r"(_rsi), "r"(_rdx),
                               "r"(_r10), "r"(_r8), "0"(_rax)
                /* Clobbers*/: "rcx", "r11", "cc", "memory"              
                );

                return _ret;
        }

        static inline I64
        scall_iface6_(I64 num, I64 _1, I64 _2, I64 _3, I64 _4, I64 _5, I64 _6)
        {
                I64 _ret;
                register I64 _rax asm("rax") = num;
                register I64 _rdi asm("rdi") = _1;
                register I64 _rsi asm("rsi") = _2;
                register I64 _rdx asm("rdx") = _3;
                register I64 _r10 asm("r10") = _4;
                register I64 _r8  asm("r8")  = _5;
                register I64 _r9  asm("r9")  = _6;

                asm volatile("syscall"
                /* Outputs */: "=a"(_ret)
                /* Inputs  */: "r"(_rdi), "r"(_rsi), "r"(_rdx),
                               "r"(_r10), "r"(_r8), "r"(_r9), "0"(_rax)
                /* Clobbers*/: "rcx", "r11", "cc", "memory"              
                );

                return _ret;
        }

        static inline I64
        read_scall0_(I64 fd, I64 buf, I64 cnt)
        {
                return scall_iface3_(0, fd, buf, cnt);
        }
        
        static inline I64
        wrte_scall1_(I64 fd, I64 buf, I64 cnt)
        {
                return scall_iface3_(1, fd, buf, cnt);
        }

        static inline I64
        open_scall2_(I64 filename, I64 flags, I64 mode)
        {
                return scall_iface3_(2, filename, flags, mode);
        }

        static inline I64
        clse_scall3_(I64 fd)
        {
                return scall_iface1_(3, fd);
        }

#  elif OS_LINUX && ARCH_ARM64
#  endif
        
#endif /* GNU_COMPILER || CLANG_COMPILER */
#endif
