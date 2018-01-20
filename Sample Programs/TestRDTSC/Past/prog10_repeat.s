	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.intel_syntax noprefix
	.globl	__Z7testTSCv
	.p2align	4, 0x90
__Z7testTSCv:                           ## @_Z7testTSCv
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
	## InlineAsm Start
	rdtscp
	## InlineAsm End
	mov	dword ptr [rbp - 4], eax
	mov	dword ptr [rbp - 8], edx
	## InlineAsm Start
	rdtscp
	## InlineAsm End
	mov	dword ptr [rbp - 12], eax
	mov	dword ptr [rbp - 16], edx
	mov	eax, dword ptr [rbp - 4]
	mov	eax, eax
	mov	ecx, eax
	mov	eax, dword ptr [rbp - 8]
	mov	eax, eax
	mov	esi, eax
	shl	rsi, 32
	or	rcx, rsi
	mov	qword ptr [rbp - 24], rcx
	mov	eax, dword ptr [rbp - 12]
	mov	eax, eax
	mov	ecx, eax
	mov	eax, dword ptr [rbp - 16]
	mov	eax, eax
	mov	esi, eax
	shl	rsi, 32
	or	rcx, rsi
	mov	qword ptr [rbp - 32], rcx
	mov	rcx, qword ptr [rbp - 32]
	mov	rsi, qword ptr [rbp - 24]
	sub	rcx, rsi
	mov	eax, ecx
	pop	rbp
	ret
	.cfi_endproc

	.globl	__Z6testL1v
	.p2align	4, 0x90
__Z6testL1v:                            ## @_Z6testL1v
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
	sub	rsp, 32848
	mov	rax, qword ptr [rip + ___stack_chk_guard@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	qword ptr [rbp - 8], rax
	mov	dword ptr [rbp - 32824], 0
LBB1_1:                                 ## =>This Inner Loop Header: Depth=1
	cmp	dword ptr [rbp - 32824], 8192
	jge	LBB1_4
## BB#2:                                ##   in Loop: Header=BB1_1 Depth=1
	movsxd	rax, dword ptr [rbp - 32824]
	mov	dword ptr [rbp + 4*rax - 32784], 0
## BB#3:                                ##   in Loop: Header=BB1_1 Depth=1
	mov	eax, dword ptr [rbp - 32824]
	add	eax, 1
	mov	dword ptr [rbp - 32824], eax
	jmp	LBB1_1
LBB1_4:
	mov	qword ptr [rbp - 32832], 0
	mov	dword ptr [rbp - 32836], 0
LBB1_5:                                 ## =>This Inner Loop Header: Depth=1
	cmp	dword ptr [rbp - 32836], 1000
	jge	LBB1_8
## BB#6:                                ##   in Loop: Header=BB1_5 Depth=1
	## InlineAsm Start
	rdtscp
	## InlineAsm End
	mov	dword ptr [rbp - 32788], eax
	mov	dword ptr [rbp - 32792], edx
	mov	eax, dword ptr [rbp - 32784]
	mov	dword ptr [rbp - 32820], eax
	mov	eax, dword ptr [rbp - 32780]
	mov	dword ptr [rbp - 32820], eax
	mov	eax, dword ptr [rbp - 32776]
	mov	dword ptr [rbp - 32820], eax
	mov	eax, dword ptr [rbp - 32772]
	mov	dword ptr [rbp - 32820], eax
	mov	eax, dword ptr [rbp - 32768]
	mov	dword ptr [rbp - 32820], eax
	mov	eax, dword ptr [rbp - 32764]
	mov	dword ptr [rbp - 32820], eax
	mov	eax, dword ptr [rbp - 32760]
	mov	dword ptr [rbp - 32820], eax
	mov	eax, dword ptr [rbp - 32756]
	mov	dword ptr [rbp - 32820], eax
	mov	eax, dword ptr [rbp - 32752]
	mov	dword ptr [rbp - 32820], eax
	mov	eax, dword ptr [rbp - 32748]
	mov	dword ptr [rbp - 32820], eax
	## InlineAsm Start
	rdtscp
	## InlineAsm End
	mov	ecx, 10
	mov	esi, ecx
	mov	dword ptr [rbp - 32796], eax
	mov	dword ptr [rbp - 32800], edx
	mov	eax, dword ptr [rbp - 32788]
	mov	eax, eax
	mov	edi, eax
	mov	eax, dword ptr [rbp - 32792]
	mov	eax, eax
	mov	r8d, eax
	shl	r8, 32
	or	rdi, r8
	mov	qword ptr [rbp - 32808], rdi
	mov	eax, dword ptr [rbp - 32796]
	mov	eax, eax
	mov	edi, eax
	mov	eax, dword ptr [rbp - 32800]
	mov	eax, eax
	mov	r8d, eax
	shl	r8, 32
	or	rdi, r8
	mov	qword ptr [rbp - 32816], rdi
	mov	rdi, qword ptr [rbp - 32816]
	mov	r8, qword ptr [rbp - 32808]
	sub	rdi, r8
	mov	rax, rdi
	xor	ecx, ecx
	mov	edx, ecx
	div	rsi
	add	rax, qword ptr [rbp - 32832]
	mov	qword ptr [rbp - 32832], rax
## BB#7:                                ##   in Loop: Header=BB1_5 Depth=1
	mov	eax, dword ptr [rbp - 32836]
	add	eax, 1
	mov	dword ptr [rbp - 32836], eax
	jmp	LBB1_5
LBB1_8:
	mov	eax, 1000
	mov	ecx, eax
	mov	rax, qword ptr [rbp - 32832]
	xor	edx, edx
                                        ## kill: %RDX<def> %EDX<kill>
	div	rcx
	mov	esi, eax
	mov	rax, qword ptr [rip + ___stack_chk_guard@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	rcx, qword ptr [rbp - 8]
	cmp	rax, rcx
	mov	dword ptr [rbp - 32840], esi ## 4-byte Spill
	jne	LBB1_10
## BB#9:
	mov	eax, dword ptr [rbp - 32840] ## 4-byte Reload
	add	rsp, 32848
	pop	rbp
	ret
LBB1_10:
	call	___stack_chk_fail
	.cfi_endproc

	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	push	rbp
Lcfi6:
	.cfi_def_cfa_offset 16
Lcfi7:
	.cfi_offset rbp, -16
	mov	rbp, rsp
Lcfi8:
	.cfi_def_cfa_register rbp
	sub	rsp, 16
	lea	rdi, [rip + L_.str]
	mov	dword ptr [rbp - 4], 0
	mov	al, 0
	call	_printf
	mov	dword ptr [rbp - 8], eax ## 4-byte Spill
	call	__Z6testL1v
	lea	rdi, [rip + L_.str.1]
	mov	esi, eax
	mov	al, 0
	call	_printf
	lea	rdi, [rip + L_.str.2]
	mov	dword ptr [rbp - 12], eax ## 4-byte Spill
	mov	al, 0
	call	_printf
	xor	esi, esi
	mov	dword ptr [rbp - 16], eax ## 4-byte Spill
	mov	eax, esi
	add	rsp, 16
	pop	rbp
	ret
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	" --- 10 Loads x 1000 --- "

L_.str.1:                               ## @.str.1
	.asciz	"\n\tL1 Avg Cycles: %d"

L_.str.2:                               ## @.str.2
	.asciz	"\n\n"


.subsections_via_symbols
