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

	mov dword [ebp - 4], ecx
	mov dword [ebp - 8], edx

	mov ax, 0x254a					; Service call magic
	mov bx, word [ebp - 4]			; Load service call number
%endmacro

%macro svccall_epilogue 0
	int 0xfe						; Do service call
	mov eax, edx 					; returns @ EDX
	mov dword[ebp - 4], ecx			; Restore fastcall arguments
	mov dword[ebp - 8], edx
	pop ebx							; restore EBX
	leave							; return
	ret
%endmacro

global @ets_svccall0@4
global @ets_svccall1@8
global @ets_svccall2@12

@ets_svccall0@4:
	svccall_prologue
	svccall_epilogue				; do it and then cleanup

@ets_svccall1@8:
	svccall_prologue
	mov dword [ebp - 8], edx		; service call argument
	svccall_epilogue

; TODO: this might be wrong >_<
@ets_svccall2@12:
	svccall_prologue
	mov dword [ebp - 8], edx		; service call argument
	mov dword [ebp + 8], ecx		; service call argument
	svccall_epilogue
