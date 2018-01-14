	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.intel_syntax noprefix
	.globl	__Z4testv
	.p2align	4, 0x90
__Z4testv:                              ## @_Z4testv
	.cfi_startproc
## BB#0:
	push	rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset rbp, -16
	mov	rbp, rsp
Lcfi2:
	.cfi_def_cfa_register rbp
	sub	rsp, 32
	mov	dword ptr [rbp - 8], 0
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmp	dword ptr [rbp - 8], 1000
	jge	LBB0_4
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	call	__ZNSt3__16chrono12steady_clock3nowEv
	lea	rcx, [rip + _arr]
	mov	qword ptr [rbp - 16], rax
	movsxd	rax, dword ptr [rbp - 8]
	mov	edx, dword ptr [rcx + 4*rax]
	mov	dword ptr [rbp - 4], edx
	call	__ZNSt3__16chrono12steady_clock3nowEv
	lea	rdi, [rip + L_.str]
	mov	qword ptr [rbp - 24], rax
	mov	esi, dword ptr [rbp - 4]
	mov	al, 0
	call	_printf
	mov	dword ptr [rbp - 28], eax ## 4-byte Spill
## BB#3:                                ##   in Loop: Header=BB0_1 Depth=1
	mov	eax, dword ptr [rbp - 8]
	add	eax, 1
	mov	dword ptr [rbp - 8], eax
	jmp	LBB0_1
LBB0_4:
	add	rsp, 32
	pop	rbp
	ret
	.cfi_endproc

	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	push	rbp
Lcfi3:
	.cfi_def_cfa_offset 16
Lcfi4:
	.cfi_offset rbp, -16
	mov	rbp, rsp
Lcfi5:
	.cfi_def_cfa_register rbp
	sub	rsp, 16
	mov	dword ptr [rbp - 4], 0
	mov	dword ptr [rbp - 8], 0
LBB1_1:                                 ## =>This Inner Loop Header: Depth=1
	cmp	dword ptr [rbp - 8], 1000
	jge	LBB1_4
## BB#2:                                ##   in Loop: Header=BB1_1 Depth=1
	lea	rax, [rip + _arr]
	movsxd	rcx, dword ptr [rbp - 8]
	mov	dword ptr [rax + 4*rcx], 1
## BB#3:                                ##   in Loop: Header=BB1_1 Depth=1
	mov	eax, dword ptr [rbp - 8]
	add	eax, 1
	mov	dword ptr [rbp - 8], eax
	jmp	LBB1_1
LBB1_4:
	call	__Z4testv
	mov	eax, dword ptr [rbp - 4]
	add	rsp, 16
	pop	rbp
	ret
	.cfi_endproc

	.globl	_arr                    ## @arr
.zerofill __DATA,__common,_arr,4000,4
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%d\n"


.subsections_via_symbols
