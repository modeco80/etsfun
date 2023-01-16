;
; Helper for calling service calls (used by ets.hpp).
;
; (C) 2023 modeco80 <lily.modeco80@protonmail.ch>.
;
; SPDX-License-Identifier: MIT
;

bits 32

; macros for generating the (common) part of the service call functions

%macro svccall_prologue 0
	push ebp						; save fastcall arguments
	mov ebp, esp
	sub esp, 8
	push ebx

	mov dword [ebp - 4], ecx
	mov dword [ebp - 8], edx

	mov ax, 0x254a					; Setup system call
	mov bx, word [ebp - 4]			; call number
%endmacro

%macro svccall_epilogue 0
	mov eax, edx 					; service call returns @ EDX
	mov dword[ebp - 4], ecx			; restore fastcall arguments
	mov dword[ebp - 8], edx
	pop ebx
%endmacro

global @__ets_svccall0@4
global @__ets_svccall1@8

@__ets_svccall0@4:
	svccall_prologue
	int 0xfe						; do service call
	svccall_epilogue				; cleanup
	leave
	ret

@__ets_svccall1@8:
	svccall_prologue
	mov dword [ebp - 8], edx		; service call argument
	int 0xfe						; do service call
	svccall_epilogue				; cleanup
	leave
	ret

