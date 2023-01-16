// extern "C" u32 ets_syscall_helper(u16 no, u32 arg)
// Call a ETS service (NOTE: there are at least 2 other ways to do syscalls.... awful!)
//
// no  - service number
// arg - argument to pass to the service (there are possibly multiple but lazy)

.globl _ets_syscall_helper
_ets_syscall_helper:
	push %ebx
	push %edx

	mov $0x254a, %ax	// Setup system call
	mov  (%esp), %bx	// call number
	movzx 4(%esp), %edx	// call arg

	int $0xfe			// do it!
	mov %edx, %eax		// syscall returns in edx

	pop %edx
	pop %ebx
	ret
