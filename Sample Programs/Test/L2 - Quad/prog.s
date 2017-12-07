	.file	"prog.cpp"
	.intel_syntax noprefix
	.globl	mask
	.bss
	.align 32
	.type	mask, @object
	.size	mask, 128
mask:
	.zero	128
	.globl	data_arr
	.align 32
	.type	data_arr, @object
	.size	data_arr, 16384
data_arr:
	.zero	16384
	.text
	.globl	_Z4initv
	.type	_Z4initv, @function
_Z4initv:
.LFB14:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	DWORD PTR -4[rbp], 0
.L3:
	cmp	DWORD PTR -4[rbp], 4095
	jg	.L4
	mov	eax, DWORD PTR -4[rbp]
	cdqe
	lea	rdx, 0[0+rax*4]
	lea	rax, data_arr[rip]
	mov	DWORD PTR [rdx+rax], 1
	add	DWORD PTR -4[rbp], 1
	jmp	.L3
.L4:
	nop
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	_Z4initv, .-_Z4initv
	.section	.text._Z12assignToCorei,"axG",@progbits,_Z12assignToCorei,comdat
	.weak	_Z12assignToCorei
	.type	_Z12assignToCorei, @function
_Z12assignToCorei:
.LFB15:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	DWORD PTR -20[rbp], edi
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	lea	rdx, mask[rip]
	mov	eax, 0
	mov	ecx, 16
	mov	rdi, rdx
	rep stosq
	mov	eax, DWORD PTR -20[rbp]
	cdqe
	mov	QWORD PTR -16[rbp], rax
	mov	rax, QWORD PTR -16[rbp]
	cmp	rax, 1023
	ja	.L7
	mov	rax, QWORD PTR -16[rbp]
	shr	rax, 6
	lea	rcx, 0[0+rax*8]
	lea	rdx, mask[rip]
	add	rdx, rcx
	mov	rdx, QWORD PTR [rdx]
	mov	rcx, QWORD PTR -16[rbp]
	and	ecx, 63
	mov	esi, 1
	sal	rsi, cl
	mov	rcx, rsi
	lea	rsi, 0[0+rax*8]
	lea	rax, mask[rip]
	add	rax, rsi
	or	rdx, rcx
	mov	QWORD PTR [rax], rdx
.L7:
	lea	rdx, mask[rip]
	mov	esi, 128
	mov	edi, 0
	call	sched_setaffinity@PLT
	nop
	mov	rax, QWORD PTR -8[rbp]
	xor	rax, QWORD PTR fs:40
	je	.L8
	call	__stack_chk_fail@PLT
.L8:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	_Z12assignToCorei, .-_Z12assignToCorei
	.text
	.globl	_Z6rdtscpv
	.type	_Z6rdtscpv, @function
_Z6rdtscpv:
.LFB16:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
#APP
# 26 "prog.cpp" 1
	rdtscp
# 0 "" 2
#NO_APP
	mov	QWORD PTR -16[rbp], rax
#APP
# 27 "prog.cpp" 1
	rdtscp
# 0 "" 2
#NO_APP
	mov	QWORD PTR -8[rbp], rax
	mov	rax, QWORD PTR -8[rbp]
	sub	rax, QWORD PTR -16[rbp]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	_Z6rdtscpv, .-_Z6rdtscpv
	.globl	_Z6testL1v
	.type	_Z6testL1v, @function
_Z6testL1v:
.LFB17:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	DWORD PTR -32[rbp], 0
	mov	DWORD PTR -28[rbp], 0
.L13:
	cmp	DWORD PTR -28[rbp], 15
	jg	.L12
	mov	eax, DWORD PTR -28[rbp]
	cdqe
	lea	rdx, 0[0+rax*4]
	lea	rax, data_arr[rip]
	mov	eax, DWORD PTR [rdx+rax]
	mov	DWORD PTR -32[rbp], eax
	add	DWORD PTR -28[rbp], 1
	jmp	.L13
.L12:
#APP
# 39 "prog.cpp" 1
	rdtscp
# 0 "" 2
#NO_APP
	mov	QWORD PTR -24[rbp], rax
	mov	eax, DWORD PTR data_arr[rip]
	mov	DWORD PTR -32[rbp], eax
#APP
# 41 "prog.cpp" 1
	rdtscp
# 0 "" 2
#NO_APP
	mov	QWORD PTR -16[rbp], rax
	mov	rax, QWORD PTR -16[rbp]
	sub	rax, QWORD PTR -24[rbp]
	mov	QWORD PTR -8[rbp], rax
	mov	rax, QWORD PTR -8[rbp]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	_Z6testL1v, .-_Z6testL1v
	.section	.rodata
.LC0:
	.string	" --- CYCLES ---"
.LC1:
	.string	"RDTSCP Overhead:\t%d\n"
.LC2:
	.string	"L1 Cache Hit:\t\t%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB18:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR -16[rbp], 0
	mov	QWORD PTR -8[rbp], 0
	call	_Z4initv
	mov	edi, 0
	call	_Z12assignToCorei
	mov	DWORD PTR -24[rbp], 1000000
	mov	DWORD PTR -32[rbp], 0
.L17:
	mov	eax, DWORD PTR -32[rbp]
	cmp	eax, DWORD PTR -24[rbp]
	jge	.L16
	call	_Z6rdtscpv
	add	QWORD PTR -16[rbp], rax
	add	DWORD PTR -32[rbp], 1
	jmp	.L17
.L16:
	mov	eax, DWORD PTR -24[rbp]
	movsx	rcx, eax
	mov	rax, QWORD PTR -16[rbp]
	mov	edx, 0
	div	rcx
	mov	QWORD PTR -16[rbp], rax
	mov	DWORD PTR -20[rbp], 1000000
	mov	DWORD PTR -28[rbp], 0
.L19:
	mov	eax, DWORD PTR -28[rbp]
	cmp	eax, DWORD PTR -20[rbp]
	jge	.L18
	call	_Z6testL1v
	cdqe
	add	QWORD PTR -8[rbp], rax
	add	DWORD PTR -28[rbp], 1
	jmp	.L19
.L18:
	mov	eax, DWORD PTR -20[rbp]
	movsx	rcx, eax
	mov	rax, QWORD PTR -8[rbp]
	mov	edx, 0
	div	rcx
	mov	QWORD PTR -8[rbp], rax
	lea	rdi, .LC0[rip]
	call	puts@PLT
	mov	rax, QWORD PTR -16[rbp]
	mov	rsi, rax
	lea	rdi, .LC1[rip]
	mov	eax, 0
	call	printf@PLT
	mov	rax, QWORD PTR -8[rbp]
	mov	rsi, rax
	lea	rdi, .LC2[rip]
	mov	eax, 0
	call	printf@PLT
	mov	eax, 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	main, .-main
	.ident	"GCC: (GNU) 7.2.0"
	.section	.note.GNU-stack,"",@progbits
