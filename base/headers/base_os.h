#ifndef SEROS_BASE_OS
#define SEROS_BASE_OS

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
#endif        /* !defined(OS_NETBSD)   */

#if !(OS_WINDOWS || OS_MAC || OS_LINUX || OS_FREEBSD || OS_OPENBSD || OS_NETBSD)
#       error "seros: Unrecognised operating system / kernel environment."
#endif

/**........................................................
// Linux direct syscall interface.                       */

/* [Chromium] https://chromium.googlesource.com/linux-syscall-support
 * [Linux]  
 // TODO syscall entry point layers */

//extern Iptr read_scall_(Iptr fd, Iptr buf, Iptr count);
extern Iptr wrte_scall_(Iptr fd, Iptr buf, Iptr count);

#endif /* SEROS_BASE_OS */
