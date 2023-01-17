;
; Helper routines for service calls (used by ets.hpp).
;
; (C) 2023 modeco80 <lily.modeco80@protonmail.ch>.
;
; SPDX-License-Identifier: MIT
;

bits 32

; macros for doing the (common) part of the service call helpers
; these could be fancier, but this is good enough for now

%macro svccall_prologue 0
	push ebp
	mov ebp, esp
	sub esp, 8
	push ebx						; save EBX (it gets clobbered)

	mov dword [ebp - 4], ecx		; call number
	mov dword [ebp - 8], edx

	mov ax, 0x254a					; Setup system call
	mov bx, word [ebp - 4]			; call number
%endmacro

%macro svccall_epilogue 0
	int 0xfe						; do service call
	mov eax, edx 					; service call returns @ EDX
	mov dword[ebp - 4], ecx			; restore fastcall arguments
	mov dword[ebp - 8], edx
	pop ebx							; restore EBX
	leave
	ret
%endmacro

global @__ets_svccall0@4
global @__ets_svccall1@8
; TODO: Two arguments?

@__ets_svccall0@4:
	svccall_prologue
	svccall_epilogue				; do it and then cleanup

@__ets_svccall1@8:
	svccall_prologue
	mov dword [ebp - 8], edx		; service call argument
	svccall_epilogue

