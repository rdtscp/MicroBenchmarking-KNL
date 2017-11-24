	.file	"prog.cpp"
	.intel_syntax noprefix
	.globl	mask
	.bss
	.align 32
	.type	mask, @object
	.size	mask, 128
mask:
	.zero	128
	.text
	.type	_ZL10test_rdtscv, @function
_ZL10test_rdtscv:
.LFB2:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
#APP
# 13 "prog.cpp" 1
	rdtscp
# 0 "" 2
#NO_APP
	mov	QWORD PTR [rbp-24], rax
#APP
# 14 "prog.cpp" 1
	rdtscp
# 0 "" 2
#NO_APP
	mov	QWORD PTR [rbp-16], rax
	mov	rax, QWORD PTR [rbp-16]
	sub	rax, QWORD PTR [rbp-24]
	mov	QWORD PTR [rbp-8], rax
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	_ZL10test_rdtscv, .-_ZL10test_rdtscv
	.section	.text._Z12assignToCorei,"axG",@progbits,_Z12assignToCorei,comdat
	.weak	_Z12assignToCorei
	.type	_Z12assignToCorei, @function
_Z12assignToCorei:
.LFB3:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	DWORD PTR [rbp-20], edi
	mov	esi, OFFSET FLAT:mask
	mov	eax, 0
	mov	edx, 16
	mov	rdi, rsi
	mov	rcx, rdx
	rep stosq
	mov	eax, DWORD PTR [rbp-20]
	cdqe
	mov	QWORD PTR [rbp-8], rax
	mov	rax, QWORD PTR [rbp-8]
	shr	rax, 3
	cmp	rax, 128
	jnb	.L5
	mov	esi, 64
	mov	rax, QWORD PTR [rbp-8]
	mov	edx, 0
	div	rsi
	lea	rdx, [0+rax*8]
	lea	rsi, mask[rdx]
	sal	rax, 3
	add	rax, OFFSET FLAT:mask
	mov	rdi, QWORD PTR [rax]
	mov	ecx, 64
	mov	rax, QWORD PTR [rbp-8]
	mov	edx, 0
	div	rcx
	mov	rax, rdx
	mov	edx, 1
	mov	ecx, eax
	sal	rdx, cl
	mov	rax, rdx
	or	rax, rdi
	mov	QWORD PTR [rsi], rax
.L5:
	mov	edx, OFFSET FLAT:mask
	mov	esi, 128
	mov	edi, 0
	call	sched_setaffinity
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	_Z12assignToCorei, .-_Z12assignToCorei
	.section	.rodata
.LC0:
	.string	"%lu\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB4:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	edi, 0
	call	_Z12assignToCorei
	mov	DWORD PTR [rbp-4], 0
.L8:
	cmp	DWORD PTR [rbp-4], 99
	jg	.L7
	call	_ZL10test_rdtscv
	mov	rsi, rax
	mov	edi, OFFSET FLAT:.LC0
	mov	eax, 0
	call	printf
	add	DWORD PTR [rbp-4], 1
	jmp	.L8
.L7:
	mov	eax, 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.5) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
