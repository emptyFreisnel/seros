/* System call dispatch layer. 
 * The code is based on the syscall dispatch assembly helper layers in Cosmopolitan libc.
 * The error-convention normalization (clc/jnc/neg) follows the approach in __syscall4.S
 * Referenced file is Copyright 2023 Justine Alexandra Roberts Tunney, ISC. 

 * Here a decision is made to have an extra mov instruction to make the syscall interface
 * generic across Linux and the BSDs for simplicity. Given that syscalls are orders of magnitude
 * more expensive than normal function calls anyway due to security mitigations it is negligible
 * to have any performance impact especially if you are going to amortize the cost of syscalls
 * in userspace functions.

 * In principle Xnu 'can' be supported ala Cosmopolitan but seros will link to libSystem
 * instead (if needed).	The assembly layer powers the typed wrappers exported over to the
 * C side in base_scall_lyr.h, and this file does not require any codebase layers nor includes.

 * [Cosmopolitan Libc]
 * https://github.com/jart/cosmopolitan/blob/3293fad0a9eac7865c019be98fb993eeb933405e/libc/sysv/syscall4.S
 * [Nolibc shipped in the Linux Kernel]
 * https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/tools/include/nolibc/arch-x86.h
 */

#if !defined(__x86_64__) && !defined(__arch64__)
#	error "seros: Unrecognised architecture in assembly layer."
#endif
	
.macro scall_arity arg_, reg_

	.section .text.__scall\arg_,"ax",@progbits
	.globl  __scall\arg_
	.hidden __scall\arg_
	.type   __scall\arg_,@function

__scall\arg_:	

	.cfi_startproc

#if defined(__x86_64__)

	endbr64
	mov	%rcx,  %r10
	mov     \reg_, %eax
	clc
	syscall
	jnc     1f
	neg     %rax 

1:	ret

#elif defined(__aarch64__)
	//TODO
#endif

	.cfi_endproc

	.size	__scall6,.-__scall6
	.section .note.GNU-stack,"", @progbits 
.endm	

#ifdef __x86_64__

	scall_arity 0, %edi
	scall_arity 1, %esi
	scall_arity 2, %edx
	scall_arity 3, %ecx
	scall_arity 4, %r8d
	scall_arity 5, %r9d

/* For arity 6: seven C parameters exceed the six argument registers.
 * so the syscall number will spill past the return address at 8(%rsp).
 */
	.section .text.__scall6,"ax",@progbits
	.globl	__scall6
	.hidden __scall6
	.type   __scall6,@function
	
__scall6:
	.cfi_startproc
	
	endbr64
	mov	%rcx, %r10
	mov	8(%rsp), %eax
	clc
	syscall
	jnc	1f
	neg	%rax

1:	ret

	.cfi_endproc
	.size	__scall6, .-__scall6
	.previous

#elif __aarch64__
	//TODO
#endif

	.section .note.GNU-stack,"",@progbits
