	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.intel_syntax noprefix
	.globl	__Z4initv
	.p2align	4, 0x90
__Z4initv:                              ## @_Z4initv
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
	sub	rsp, 64
	lea	rdi, [rip + L_.str]
	mov	al, 0
	call	_printf
	lea	rdi, [rip + L_.str.1]
	lea	rcx, [rip + _head]
	mov	qword ptr [rbp - 8], rcx
	mov	rsi, qword ptr [rbp - 8]
	mov	dword ptr [rbp - 28], eax ## 4-byte Spill
	mov	al, 0
	call	_printf
	mov	dword ptr [rbp - 12], 0
	mov	dword ptr [rbp - 32], eax ## 4-byte Spill
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	mov	eax, dword ptr [rbp - 12]
	cmp	eax, dword ptr [rip + _mem_fill_blocks]
	jge	LBB0_10
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	mov	eax, 16
	mov	edi, eax
	call	__Znwm
	xor	esi, esi
	mov	ecx, 16
	mov	edx, ecx
	mov	rdi, rax
	mov	qword ptr [rbp - 40], rax ## 8-byte Spill
	call	_memset
	mov	rax, qword ptr [rbp - 40] ## 8-byte Reload
	mov	qword ptr [rbp - 24], rax
	mov	rdx, qword ptr [rbp - 24]
	mov	rdi, qword ptr [rbp - 8]
	mov	qword ptr [rdi], rdx
	mov	ecx, dword ptr [rbp - 12]
	mov	esi, dword ptr [rip + _mem_fill_blocks]
	sub	esi, 1
	cmp	ecx, esi
	jne	LBB0_4
## BB#3:                                ##   in Loop: Header=BB0_1 Depth=1
	mov	rax, qword ptr [rbp - 8]
	mov	dword ptr [rax + 8], 99
LBB0_4:                                 ##   in Loop: Header=BB0_1 Depth=1
	mov	eax, dword ptr [rbp - 12]
	mov	ecx, dword ptr [rip + _l1_cache_blocks]
	sub	ecx, 1
	cmp	eax, ecx
	jne	LBB0_6
## BB#5:                                ##   in Loop: Header=BB0_1 Depth=1
	mov	rax, qword ptr [rbp - 8]
	mov	dword ptr [rax + 8], 1
LBB0_6:                                 ##   in Loop: Header=BB0_1 Depth=1
	mov	eax, dword ptr [rbp - 12]
	mov	ecx, dword ptr [rip + _l2_cache_blocks]
	sub	ecx, 1
	cmp	eax, ecx
	jne	LBB0_8
## BB#7:                                ##   in Loop: Header=BB0_1 Depth=1
	mov	rax, qword ptr [rbp - 8]
	mov	dword ptr [rax + 8], 2
LBB0_8:                                 ##   in Loop: Header=BB0_1 Depth=1
	mov	rax, qword ptr [rbp - 8]
	mov	rax, qword ptr [rax]
	mov	qword ptr [rbp - 8], rax
## BB#9:                                ##   in Loop: Header=BB0_1 Depth=1
	mov	eax, dword ptr [rbp - 12]
	add	eax, 1
	mov	dword ptr [rbp - 12], eax
	jmp	LBB0_1
LBB0_10:
	lea	rdi, [rip + L_.str.2]
	mov	al, 0
	call	_printf
	lea	rdi, [rip + L_.str.3]
	mov	esi, 4096
	mov	dword ptr [rbp - 44], eax ## 4-byte Spill
	mov	al, 0
	call	_printf
	lea	rdi, [rip + L_.str.4]
	mov	esi, 135168
	mov	dword ptr [rbp - 48], eax ## 4-byte Spill
	mov	al, 0
	call	_printf
	lea	rdi, [rip + L_.str.5]
	mov	dword ptr [rbp - 52], eax ## 4-byte Spill
	mov	al, 0
	call	_printf
	mov	dword ptr [rbp - 56], eax ## 4-byte Spill
	add	rsp, 64
	pop	rbp
	ret
	.cfi_endproc

	.section	__TEXT,__literal8,8byte_literals
	.p2align	3
LCPI1_0:
	.quad	4741671816366391296     ## double 1.0E+9
	.section	__TEXT,__text,regular,pure_instructions
	.globl	__Z8runTestsv
	.p2align	4, 0x90
__Z8runTestsv:                          ## @_Z8runTestsv
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
	push	r15
	push	r14
	push	r13
	push	r12
	push	rbx
	sub	rsp, 488
Lcfi6:
	.cfi_offset rbx, -56
Lcfi7:
	.cfi_offset r12, -48
Lcfi8:
	.cfi_offset r13, -40
Lcfi9:
	.cfi_offset r14, -32
Lcfi10:
	.cfi_offset r15, -24
	lea	rdi, [rip + L_.str.6]
	mov	al, 0
	call	_printf
	lea	rdi, [rip + _head]
	mov	qword ptr [rbp - 424], rdi
	mov	dword ptr [rbp - 476], eax ## 4-byte Spill
	call	__ZNSt3__16chrono12steady_clock3nowEv
	mov	qword ptr [rbp - 432], rax
LBB1_1:                                 ## =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rbp - 424]
	cmp	qword ptr [rax], 0
	je	LBB1_7
## BB#2:                                ##   in Loop: Header=BB1_1 Depth=1
	mov	rax, qword ptr [rbp - 424]
	mov	rax, qword ptr [rax]
	mov	qword ptr [rbp - 424], rax
	mov	rax, qword ptr [rbp - 424]
	cmp	dword ptr [rax + 8], 0
	je	LBB1_6
## BB#3:                                ##   in Loop: Header=BB1_1 Depth=1
	mov	rax, qword ptr [rbp - 424]
	mov	ecx, dword ptr [rax + 8]
	mov	dword ptr [rbp - 436], ecx
	call	__ZNSt3__16chrono12steady_clock3nowEv
	mov	qword ptr [rbp - 448], rax
	mov	rax, qword ptr [rbp - 424]
	mov	rax, qword ptr [rax]
	mov	qword ptr [rbp - 424], rax
	call	__ZNSt3__16chrono12steady_clock3nowEv
	mov	rdi, qword ptr [rip + __ZNSt3__14coutE@GOTPCREL]
	lea	rsi, [rip + L_.str.7]
	lea	rdx, [rbp - 200]
	lea	r8, [rbp - 144]
	lea	r9, [rbp - 120]
	movsd	xmm0, qword ptr [rip + LCPI1_0] ## xmm0 = mem[0],zero
	lea	r10, [rbp - 168]
	lea	r11, [rbp - 472]
	lea	rbx, [rbp - 464]
	lea	r14, [rbp - 336]
	lea	r15, [rbp - 312]
	lea	r12, [rbp - 352]
	lea	r13, [rbp - 344]
	lea	rcx, [rbp - 408]
	mov	qword ptr [rbp - 488], rax ## 8-byte Spill
	lea	rax, [rbp - 400]
	mov	qword ptr [rbp - 496], rax ## 8-byte Spill
	lea	rax, [rbp - 448]
	mov	qword ptr [rbp - 504], rax ## 8-byte Spill
	lea	rax, [rbp - 456]
	mov	qword ptr [rbp - 512], rax ## 8-byte Spill
	mov	rax, qword ptr [rbp - 488] ## 8-byte Reload
	mov	qword ptr [rbp - 456], rax
	mov	rax, qword ptr [rbp - 512] ## 8-byte Reload
	mov	qword ptr [rbp - 384], rax
	mov	rax, qword ptr [rbp - 504] ## 8-byte Reload
	mov	qword ptr [rbp - 392], rax
	mov	rax, qword ptr [rbp - 384]
	mov	qword ptr [rbp - 368], rax
	mov	rax, qword ptr [rbp - 368]
	mov	rax, qword ptr [rax]
	mov	qword ptr [rbp - 360], rax
	mov	rax, qword ptr [rbp - 360]
	mov	qword ptr [rbp - 400], rax
	mov	rax, qword ptr [rbp - 392]
	mov	qword ptr [rbp - 240], rax
	mov	rax, qword ptr [rbp - 240]
	mov	rax, qword ptr [rax]
	mov	qword ptr [rbp - 232], rax
	mov	rax, qword ptr [rbp - 232]
	mov	qword ptr [rbp - 408], rax
	mov	rax, qword ptr [rbp - 496] ## 8-byte Reload
	mov	qword ptr [rbp - 320], rax
	mov	qword ptr [rbp - 328], rcx
	mov	rcx, qword ptr [rbp - 320]
	mov	rcx, qword ptr [rcx]
	mov	qword ptr [rbp - 344], rcx
	mov	qword ptr [rbp - 304], r13
	mov	rcx, qword ptr [rbp - 304]
	mov	rcx, qword ptr [rcx]
	mov	r13, qword ptr [rbp - 328]
	mov	r13, qword ptr [r13]
	mov	qword ptr [rbp - 352], r13
	mov	qword ptr [rbp - 248], r12
	mov	r12, qword ptr [rbp - 248]
	sub	rcx, qword ptr [r12]
	mov	qword ptr [rbp - 336], rcx
	mov	qword ptr [rbp - 280], r15
	mov	qword ptr [rbp - 288], r14
	mov	qword ptr [rbp - 296], 0
	mov	rcx, qword ptr [rbp - 280]
	mov	r14, qword ptr [rbp - 288]
	mov	r15, qword ptr [rbp - 296]
	mov	qword ptr [rbp - 256], rcx
	mov	qword ptr [rbp - 264], r14
	mov	qword ptr [rbp - 272], r15
	mov	rcx, qword ptr [rbp - 256]
	mov	r14, qword ptr [rbp - 264]
	mov	r14, qword ptr [r14]
	mov	qword ptr [rcx], r14
	mov	rcx, qword ptr [rbp - 312]
	mov	qword ptr [rbp - 376], rcx
	mov	rcx, qword ptr [rbp - 376]
	mov	qword ptr [rbp - 472], rcx
	mov	qword ptr [rbp - 208], rbx
	mov	qword ptr [rbp - 216], r11
	mov	qword ptr [rbp - 224], 0
	mov	rcx, qword ptr [rbp - 208]
	mov	r11, qword ptr [rbp - 216]
	mov	rbx, qword ptr [rbp - 224]
	mov	qword ptr [rbp - 176], rcx
	mov	qword ptr [rbp - 184], r11
	mov	qword ptr [rbp - 192], rbx
	mov	rcx, qword ptr [rbp - 176]
	mov	r11, qword ptr [rbp - 184]
	mov	qword ptr [rbp - 160], r11
	mov	r11, qword ptr [rbp - 160]
	mov	qword ptr [rbp - 128], r10
	mov	qword ptr [rbp - 136], r11
	mov	r10, qword ptr [rbp - 136]
	mov	qword ptr [rbp - 112], r10
	mov	r10, qword ptr [rbp - 112]
	cvtsi2sd	xmm1, qword ptr [r10]
	divsd	xmm1, xmm0
	movsd	qword ptr [rbp - 144], xmm1
	mov	qword ptr [rbp - 88], r9
	mov	qword ptr [rbp - 96], r8
	mov	qword ptr [rbp - 104], 0
	mov	r8, qword ptr [rbp - 88]
	mov	r9, qword ptr [rbp - 96]
	mov	r10, qword ptr [rbp - 104]
	mov	qword ptr [rbp - 64], r8
	mov	qword ptr [rbp - 72], r9
	mov	qword ptr [rbp - 80], r10
	mov	r8, qword ptr [rbp - 64]
	mov	r9, qword ptr [rbp - 72]
	movsd	xmm0, qword ptr [r9]    ## xmm0 = mem[0],zero
	movsd	qword ptr [r8], xmm0
	movsd	xmm0, qword ptr [rbp - 120] ## xmm0 = mem[0],zero
	movsd	qword ptr [rbp - 152], xmm0
	movsd	xmm0, qword ptr [rbp - 152] ## xmm0 = mem[0],zero
	movsd	qword ptr [rbp - 200], xmm0
	mov	qword ptr [rbp - 56], rdx
	mov	rdx, qword ptr [rbp - 56]
	movsd	xmm0, qword ptr [rdx]   ## xmm0 = mem[0],zero
	movsd	qword ptr [rcx], xmm0
	call	__ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc
	mov	esi, dword ptr [rbp - 436]
	mov	edi, esi
	add	edi, 1
	mov	dword ptr [rbp - 436], edi
	mov	rdi, rax
	call	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi
	lea	rsi, [rip + L_.str.8]
	mov	rdi, rax
	call	__ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc
	lea	rcx, [rbp - 464]
	mov	qword ptr [rbp - 48], rcx
	mov	rcx, qword ptr [rbp - 48]
	movsd	xmm0, qword ptr [rcx]   ## xmm0 = mem[0],zero
	mov	rdi, rax
	call	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEd
	mov	esi, 10
	mov	rdi, rax
	call	__ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_c
	cmp	dword ptr [rbp - 436], 99
	mov	qword ptr [rbp - 520], rax ## 8-byte Spill
	jne	LBB1_5
## BB#4:
	mov	dword ptr [rbp - 412], 0
	jmp	LBB1_8
LBB1_5:                                 ##   in Loop: Header=BB1_1 Depth=1
	jmp	LBB1_6
LBB1_6:                                 ##   in Loop: Header=BB1_1 Depth=1
	jmp	LBB1_1
LBB1_7:
	lea	rdi, [rip + L_.str.9]
	mov	al, 0
	call	_printf
	mov	dword ptr [rbp - 412], 1
	mov	dword ptr [rbp - 524], eax ## 4-byte Spill
LBB1_8:
	mov	eax, dword ptr [rbp - 412]
	add	rsp, 488
	pop	rbx
	pop	r12
	pop	r13
	pop	r14
	pop	r15
	pop	rbp
	ret
	.cfi_endproc

	.globl	__ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_c
	.weak_definition	__ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_c
	.p2align	4, 0x90
__ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_c: ## @_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_c
	.cfi_startproc
## BB#0:
	push	rbp
Lcfi11:
	.cfi_def_cfa_offset 16
Lcfi12:
	.cfi_offset rbp, -16
	mov	rbp, rsp
Lcfi13:
	.cfi_def_cfa_register rbp
	sub	rsp, 16
	mov	al, sil
	lea	rsi, [rbp - 9]
	mov	ecx, 1
	mov	edx, ecx
	mov	qword ptr [rbp - 8], rdi
	mov	byte ptr [rbp - 9], al
	mov	rdi, qword ptr [rbp - 8]
	call	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	add	rsp, 16
	pop	rbp
	ret
	.cfi_endproc

	.globl	__ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc
	.weak_definition	__ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc
	.p2align	4, 0x90
__ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc: ## @_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc
	.cfi_startproc
## BB#0:
	push	rbp
Lcfi14:
	.cfi_def_cfa_offset 16
Lcfi15:
	.cfi_offset rbp, -16
	mov	rbp, rsp
Lcfi16:
	.cfi_def_cfa_register rbp
	sub	rsp, 32
	mov	qword ptr [rbp - 8], rdi
	mov	qword ptr [rbp - 16], rsi
	mov	rdi, qword ptr [rbp - 8]
	mov	rsi, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 16]
	mov	qword ptr [rbp - 24], rdi ## 8-byte Spill
	mov	rdi, rax
	mov	qword ptr [rbp - 32], rsi ## 8-byte Spill
	call	__ZNSt3__111char_traitsIcE6lengthEPKc
	mov	rdi, qword ptr [rbp - 24] ## 8-byte Reload
	mov	rsi, qword ptr [rbp - 32] ## 8-byte Reload
	mov	rdx, rax
	call	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	add	rsp, 32
	pop	rbp
	ret
	.cfi_endproc

	.globl	__Z9parseLinePc
	.p2align	4, 0x90
__Z9parseLinePc:                        ## @_Z9parseLinePc
	.cfi_startproc
## BB#0:
	push	rbp
Lcfi17:
	.cfi_def_cfa_offset 16
Lcfi18:
	.cfi_offset rbp, -16
	mov	rbp, rsp
Lcfi19:
	.cfi_def_cfa_register rbp
	sub	rsp, 32
	mov	qword ptr [rbp - 8], rdi
	mov	rdi, qword ptr [rbp - 8]
	call	_strlen
	mov	ecx, eax
	mov	dword ptr [rbp - 12], ecx
	mov	rax, qword ptr [rbp - 8]
	mov	qword ptr [rbp - 24], rax
LBB4_1:                                 ## =>This Inner Loop Header: Depth=1
	mov	al, 1
	mov	rcx, qword ptr [rbp - 24]
	movsx	edx, byte ptr [rcx]
	cmp	edx, 48
	mov	byte ptr [rbp - 25], al ## 1-byte Spill
	jl	LBB4_3
## BB#2:                                ##   in Loop: Header=BB4_1 Depth=1
	mov	rax, qword ptr [rbp - 24]
	movsx	ecx, byte ptr [rax]
	cmp	ecx, 57
	setg	dl
	mov	byte ptr [rbp - 25], dl ## 1-byte Spill
LBB4_3:                                 ##   in Loop: Header=BB4_1 Depth=1
	mov	al, byte ptr [rbp - 25] ## 1-byte Reload
	test	al, 1
	jne	LBB4_4
	jmp	LBB4_5
LBB4_4:                                 ##   in Loop: Header=BB4_1 Depth=1
	mov	rax, qword ptr [rbp - 24]
	add	rax, 1
	mov	qword ptr [rbp - 24], rax
	jmp	LBB4_1
LBB4_5:
	mov	rax, qword ptr [rbp - 8]
	mov	ecx, dword ptr [rbp - 12]
	sub	ecx, 3
	movsxd	rdx, ecx
	mov	byte ptr [rax + rdx], 0
	mov	rdi, qword ptr [rbp - 24]
	call	_atoi
	mov	dword ptr [rbp - 12], eax
	mov	eax, dword ptr [rbp - 12]
	add	rsp, 32
	pop	rbp
	ret
	.cfi_endproc

	.globl	__Z8getValuev
	.p2align	4, 0x90
__Z8getValuev:                          ## @_Z8getValuev
	.cfi_startproc
## BB#0:
	push	rbp
Lcfi20:
	.cfi_def_cfa_offset 16
Lcfi21:
	.cfi_offset rbp, -16
	mov	rbp, rsp
Lcfi22:
	.cfi_def_cfa_register rbp
	sub	rsp, 176
	lea	rdi, [rip + L_.str.10]
	lea	rsi, [rip + L_.str.11]
	mov	rax, qword ptr [rip + ___stack_chk_guard@GOTPCREL]
	mov	rax, qword ptr [rax]
	mov	qword ptr [rbp - 8], rax
	call	_fopen
	mov	qword ptr [rbp - 152], rax
	mov	dword ptr [rbp - 156], -1
LBB5_1:                                 ## =>This Inner Loop Header: Depth=1
	mov	esi, 128
	lea	rdi, [rbp - 144]
	mov	rdx, qword ptr [rbp - 152]
	call	_fgets
	cmp	rax, 0
	je	LBB5_5
## BB#2:                                ##   in Loop: Header=BB5_1 Depth=1
	lea	rsi, [rip + L_.str.12]
	mov	eax, 6
	mov	edx, eax
	lea	rdi, [rbp - 144]
	call	_strncmp
	cmp	eax, 0
	jne	LBB5_4
## BB#3:
	lea	rdi, [rbp - 144]
	call	__Z9parseLinePc
	mov	dword ptr [rbp - 156], eax
	jmp	LBB5_5
LBB5_4:                                 ##   in Loop: Header=BB5_1 Depth=1
	jmp	LBB5_1
LBB5_5:
	mov	rdi, qword ptr [rbp - 152]
	call	_fclose
	mov	ecx, dword ptr [rbp - 156]
	mov	rdi, qword ptr [rip + ___stack_chk_guard@GOTPCREL]
	mov	rdi, qword ptr [rdi]
	mov	rdx, qword ptr [rbp - 8]
	cmp	rdi, rdx
	mov	dword ptr [rbp - 160], eax ## 4-byte Spill
	mov	dword ptr [rbp - 164], ecx ## 4-byte Spill
	jne	LBB5_7
## BB#6:
	mov	eax, dword ptr [rbp - 164] ## 4-byte Reload
	add	rsp, 176
	pop	rbp
	ret
LBB5_7:
	call	___stack_chk_fail
	.cfi_endproc

	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	push	rbp
Lcfi23:
	.cfi_def_cfa_offset 16
Lcfi24:
	.cfi_offset rbp, -16
	mov	rbp, rsp
Lcfi25:
	.cfi_def_cfa_register rbp
	sub	rsp, 32
	call	__Z4initv
	call	__Z8runTestsv
	lea	rdi, [rip + L_.str.13]
	mov	dword ptr [rbp - 8], eax ## 4-byte Spill
	mov	al, 0
	call	_printf
	lea	rdi, [rip + L_.str.14]
	mov	dword ptr [rbp - 12], eax ## 4-byte Spill
	mov	al, 0
	call	_printf
	mov	dword ptr [rbp - 16], eax ## 4-byte Spill
	call	__Z8getValuev
	lea	rdi, [rip + L_.str.15]
	mov	dword ptr [rbp - 4], eax
	mov	esi, dword ptr [rbp - 4]
	mov	al, 0
	call	_printf
	xor	esi, esi
	mov	dword ptr [rbp - 20], eax ## 4-byte Spill
	mov	eax, esi
	add	rsp, 32
	pop	rbp
	ret
	.cfi_endproc

	.globl	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	.weak_definition	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	.p2align	4, 0x90
__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m: ## @_ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
Lfunc_begin0:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception0
## BB#0:
	push	rbp
Lcfi26:
	.cfi_def_cfa_offset 16
Lcfi27:
	.cfi_offset rbp, -16
	mov	rbp, rsp
Lcfi28:
	.cfi_def_cfa_register rbp
	sub	rsp, 416
	mov	qword ptr [rbp - 200], rdi
	mov	qword ptr [rbp - 208], rsi
	mov	qword ptr [rbp - 216], rdx
	mov	rsi, qword ptr [rbp - 200]
Ltmp0:
	lea	rdi, [rbp - 232]
	call	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryC1ERS3_
Ltmp1:
	jmp	LBB7_1
LBB7_1:
	lea	rax, [rbp - 232]
	mov	qword ptr [rbp - 192], rax
	mov	rax, qword ptr [rbp - 192]
	mov	cl, byte ptr [rax]
	mov	byte ptr [rbp - 265], cl ## 1-byte Spill
## BB#2:
	mov	al, byte ptr [rbp - 265] ## 1-byte Reload
	test	al, 1
	jne	LBB7_3
	jmp	LBB7_26
LBB7_3:
	lea	rax, [rbp - 256]
	mov	rcx, qword ptr [rbp - 200]
	mov	qword ptr [rbp - 176], rax
	mov	qword ptr [rbp - 184], rcx
	mov	rax, qword ptr [rbp - 176]
	mov	rcx, qword ptr [rbp - 184]
	mov	qword ptr [rbp - 144], rax
	mov	qword ptr [rbp - 152], rcx
	mov	rax, qword ptr [rbp - 144]
	mov	rcx, qword ptr [rbp - 152]
	mov	rdx, qword ptr [rcx]
	mov	rdx, qword ptr [rdx - 24]
	add	rcx, rdx
	mov	qword ptr [rbp - 136], rcx
	mov	rcx, qword ptr [rbp - 136]
	mov	qword ptr [rbp - 128], rcx
	mov	rcx, qword ptr [rbp - 128]
	mov	rcx, qword ptr [rcx + 40]
	mov	qword ptr [rax], rcx
	mov	rsi, qword ptr [rbp - 208]
	mov	rax, qword ptr [rbp - 200]
	mov	rcx, qword ptr [rax]
	mov	rcx, qword ptr [rcx - 24]
	add	rax, rcx
	mov	qword ptr [rbp - 88], rax
	mov	rax, qword ptr [rbp - 88]
	mov	edi, dword ptr [rax + 8]
	mov	qword ptr [rbp - 280], rsi ## 8-byte Spill
	mov	dword ptr [rbp - 284], edi ## 4-byte Spill
## BB#4:
	mov	eax, dword ptr [rbp - 284] ## 4-byte Reload
	and	eax, 176
	cmp	eax, 32
	jne	LBB7_6
## BB#5:
	mov	rax, qword ptr [rbp - 208]
	add	rax, qword ptr [rbp - 216]
	mov	qword ptr [rbp - 296], rax ## 8-byte Spill
	jmp	LBB7_7
LBB7_6:
	mov	rax, qword ptr [rbp - 208]
	mov	qword ptr [rbp - 296], rax ## 8-byte Spill
LBB7_7:
	mov	rax, qword ptr [rbp - 296] ## 8-byte Reload
	mov	rcx, qword ptr [rbp - 208]
	add	rcx, qword ptr [rbp - 216]
	mov	rdx, qword ptr [rbp - 200]
	mov	rsi, qword ptr [rdx]
	mov	rsi, qword ptr [rsi - 24]
	add	rdx, rsi
	mov	rsi, qword ptr [rbp - 200]
	mov	rdi, qword ptr [rsi]
	mov	rdi, qword ptr [rdi - 24]
	add	rsi, rdi
	mov	qword ptr [rbp - 72], rsi
	mov	rsi, qword ptr [rbp - 72]
	mov	qword ptr [rbp - 304], rax ## 8-byte Spill
	mov	qword ptr [rbp - 312], rcx ## 8-byte Spill
	mov	qword ptr [rbp - 320], rdx ## 8-byte Spill
	mov	qword ptr [rbp - 328], rsi ## 8-byte Spill
	call	__ZNSt3__111char_traitsIcE3eofEv
	mov	rcx, qword ptr [rbp - 328] ## 8-byte Reload
	mov	esi, dword ptr [rcx + 144]
	mov	edi, eax
	call	__ZNSt3__111char_traitsIcE11eq_int_typeEii
	test	al, 1
	jne	LBB7_8
	jmp	LBB7_16
LBB7_8:
	mov	rax, qword ptr [rbp - 328] ## 8-byte Reload
	mov	qword ptr [rbp - 32], rax
	mov	byte ptr [rbp - 33], 32
	mov	rsi, qword ptr [rbp - 32]
Ltmp2:
	lea	rdi, [rbp - 48]
	call	__ZNKSt3__18ios_base6getlocEv
Ltmp3:
	jmp	LBB7_9
LBB7_9:
	lea	rax, [rbp - 48]
	mov	qword ptr [rbp - 24], rax
	mov	rdi, qword ptr [rbp - 24]
Ltmp4:
	mov	rsi, qword ptr [rip + __ZNSt3__15ctypeIcE2idE@GOTPCREL]
	call	__ZNKSt3__16locale9use_facetERNS0_2idE
Ltmp5:
	mov	qword ptr [rbp - 336], rax ## 8-byte Spill
	jmp	LBB7_10
LBB7_10:
	mov	al, byte ptr [rbp - 33]
	mov	rcx, qword ptr [rbp - 336] ## 8-byte Reload
	mov	qword ptr [rbp - 8], rcx
	mov	byte ptr [rbp - 9], al
	mov	rdx, qword ptr [rbp - 8]
	mov	rsi, qword ptr [rdx]
	mov	rsi, qword ptr [rsi + 56]
	movsx	edi, byte ptr [rbp - 9]
Ltmp6:
	mov	dword ptr [rbp - 340], edi ## 4-byte Spill
	mov	rdi, rdx
	mov	r8d, dword ptr [rbp - 340] ## 4-byte Reload
	mov	qword ptr [rbp - 352], rsi ## 8-byte Spill
	mov	esi, r8d
	mov	rdx, qword ptr [rbp - 352] ## 8-byte Reload
	call	rdx
Ltmp7:
	mov	byte ptr [rbp - 353], al ## 1-byte Spill
	jmp	LBB7_14
LBB7_11:
Ltmp8:
	mov	ecx, edx
	mov	qword ptr [rbp - 56], rax
	mov	dword ptr [rbp - 60], ecx
Ltmp9:
	lea	rdi, [rbp - 48]
	call	__ZNSt3__16localeD1Ev
Ltmp10:
	jmp	LBB7_12
LBB7_12:
	mov	rax, qword ptr [rbp - 56]
	mov	ecx, dword ptr [rbp - 60]
	mov	qword ptr [rbp - 368], rax ## 8-byte Spill
	mov	dword ptr [rbp - 372], ecx ## 4-byte Spill
	jmp	LBB7_24
LBB7_13:
Ltmp11:
	mov	ecx, edx
	mov	rdi, rax
	mov	dword ptr [rbp - 376], ecx ## 4-byte Spill
	call	___clang_call_terminate
LBB7_14:
Ltmp12:
	lea	rdi, [rbp - 48]
	call	__ZNSt3__16localeD1Ev
Ltmp13:
	jmp	LBB7_15
LBB7_15:
	mov	al, byte ptr [rbp - 353] ## 1-byte Reload
	movsx	ecx, al
	mov	rdx, qword ptr [rbp - 328] ## 8-byte Reload
	mov	dword ptr [rdx + 144], ecx
LBB7_16:
	mov	rax, qword ptr [rbp - 328] ## 8-byte Reload
	mov	ecx, dword ptr [rax + 144]
	mov	dl, cl
	mov	byte ptr [rbp - 377], dl ## 1-byte Spill
## BB#17:
	mov	rdi, qword ptr [rbp - 256]
Ltmp14:
	mov	al, byte ptr [rbp - 377] ## 1-byte Reload
	movsx	r9d, al
	mov	rsi, qword ptr [rbp - 280] ## 8-byte Reload
	mov	rdx, qword ptr [rbp - 304] ## 8-byte Reload
	mov	rcx, qword ptr [rbp - 312] ## 8-byte Reload
	mov	r8, qword ptr [rbp - 320] ## 8-byte Reload
	call	__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
Ltmp15:
	mov	qword ptr [rbp - 392], rax ## 8-byte Spill
	jmp	LBB7_18
LBB7_18:
	lea	rax, [rbp - 264]
	mov	rcx, qword ptr [rbp - 392] ## 8-byte Reload
	mov	qword ptr [rbp - 264], rcx
	mov	qword ptr [rbp - 80], rax
	mov	rax, qword ptr [rbp - 80]
	cmp	qword ptr [rax], 0
	jne	LBB7_25
## BB#19:
	mov	rax, qword ptr [rbp - 200]
	mov	rcx, qword ptr [rax]
	mov	rcx, qword ptr [rcx - 24]
	add	rax, rcx
	mov	qword ptr [rbp - 112], rax
	mov	dword ptr [rbp - 116], 5
	mov	rax, qword ptr [rbp - 112]
	mov	edx, dword ptr [rbp - 116]
	mov	qword ptr [rbp - 96], rax
	mov	dword ptr [rbp - 100], edx
	mov	rax, qword ptr [rbp - 96]
	mov	edx, dword ptr [rax + 32]
	mov	esi, dword ptr [rbp - 100]
	or	edx, esi
Ltmp16:
	mov	rdi, rax
	mov	esi, edx
	call	__ZNSt3__18ios_base5clearEj
Ltmp17:
	jmp	LBB7_20
LBB7_20:
	jmp	LBB7_21
LBB7_21:
	jmp	LBB7_25
LBB7_22:
Ltmp23:
	mov	ecx, edx
	mov	qword ptr [rbp - 240], rax
	mov	dword ptr [rbp - 244], ecx
	jmp	LBB7_29
LBB7_23:
Ltmp18:
	mov	ecx, edx
	mov	qword ptr [rbp - 368], rax ## 8-byte Spill
	mov	dword ptr [rbp - 372], ecx ## 4-byte Spill
	jmp	LBB7_24
LBB7_24:
	mov	eax, dword ptr [rbp - 372] ## 4-byte Reload
	mov	rcx, qword ptr [rbp - 368] ## 8-byte Reload
	mov	qword ptr [rbp - 240], rcx
	mov	dword ptr [rbp - 244], eax
Ltmp19:
	lea	rdi, [rbp - 232]
	call	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev
Ltmp20:
	jmp	LBB7_28
LBB7_25:
	jmp	LBB7_26
LBB7_26:
Ltmp21:
	lea	rdi, [rbp - 232]
	call	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev
Ltmp22:
	jmp	LBB7_27
LBB7_27:
	jmp	LBB7_31
LBB7_28:
	jmp	LBB7_29
LBB7_29:
	mov	rdi, qword ptr [rbp - 240]
	call	___cxa_begin_catch
	mov	rdi, qword ptr [rbp - 200]
	mov	rcx, qword ptr [rdi]
	mov	rcx, qword ptr [rcx - 24]
	add	rdi, rcx
Ltmp24:
	mov	qword ptr [rbp - 400], rax ## 8-byte Spill
	call	__ZNSt3__18ios_base33__set_badbit_and_consider_rethrowEv
Ltmp25:
	jmp	LBB7_30
LBB7_30:
	call	___cxa_end_catch
LBB7_31:
	mov	rax, qword ptr [rbp - 200]
	add	rsp, 416
	pop	rbp
	ret
LBB7_32:
Ltmp26:
	mov	ecx, edx
	mov	qword ptr [rbp - 240], rax
	mov	dword ptr [rbp - 244], ecx
Ltmp27:
	call	___cxa_end_catch
Ltmp28:
	jmp	LBB7_33
LBB7_33:
	jmp	LBB7_34
LBB7_34:
	mov	rdi, qword ptr [rbp - 240]
	call	__Unwind_Resume
LBB7_35:
Ltmp29:
	mov	ecx, edx
	mov	rdi, rax
	mov	dword ptr [rbp - 404], ecx ## 4-byte Spill
	call	___clang_call_terminate
Lfunc_end0:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2
GCC_except_table7:
Lexception0:
	.byte	255                     ## @LPStart Encoding = omit
	.byte	155                     ## @TType Encoding = indirect pcrel sdata4
	.asciz	"\253\201"              ## @TType base offset
	.byte	3                       ## Call site Encoding = udata4
	.ascii	"\234\001"              ## Call site table length
Lset0 = Ltmp0-Lfunc_begin0              ## >> Call Site 1 <<
	.long	Lset0
Lset1 = Ltmp1-Ltmp0                     ##   Call between Ltmp0 and Ltmp1
	.long	Lset1
Lset2 = Ltmp23-Lfunc_begin0             ##     jumps to Ltmp23
	.long	Lset2
	.byte	5                       ##   On action: 3
Lset3 = Ltmp2-Lfunc_begin0              ## >> Call Site 2 <<
	.long	Lset3
Lset4 = Ltmp3-Ltmp2                     ##   Call between Ltmp2 and Ltmp3
	.long	Lset4
Lset5 = Ltmp18-Lfunc_begin0             ##     jumps to Ltmp18
	.long	Lset5
	.byte	5                       ##   On action: 3
Lset6 = Ltmp4-Lfunc_begin0              ## >> Call Site 3 <<
	.long	Lset6
Lset7 = Ltmp7-Ltmp4                     ##   Call between Ltmp4 and Ltmp7
	.long	Lset7
Lset8 = Ltmp8-Lfunc_begin0              ##     jumps to Ltmp8
	.long	Lset8
	.byte	3                       ##   On action: 2
Lset9 = Ltmp9-Lfunc_begin0              ## >> Call Site 4 <<
	.long	Lset9
Lset10 = Ltmp10-Ltmp9                   ##   Call between Ltmp9 and Ltmp10
	.long	Lset10
Lset11 = Ltmp11-Lfunc_begin0            ##     jumps to Ltmp11
	.long	Lset11
	.byte	7                       ##   On action: 4
Lset12 = Ltmp12-Lfunc_begin0            ## >> Call Site 5 <<
	.long	Lset12
Lset13 = Ltmp17-Ltmp12                  ##   Call between Ltmp12 and Ltmp17
	.long	Lset13
Lset14 = Ltmp18-Lfunc_begin0            ##     jumps to Ltmp18
	.long	Lset14
	.byte	5                       ##   On action: 3
Lset15 = Ltmp19-Lfunc_begin0            ## >> Call Site 6 <<
	.long	Lset15
Lset16 = Ltmp20-Ltmp19                  ##   Call between Ltmp19 and Ltmp20
	.long	Lset16
Lset17 = Ltmp29-Lfunc_begin0            ##     jumps to Ltmp29
	.long	Lset17
	.byte	5                       ##   On action: 3
Lset18 = Ltmp21-Lfunc_begin0            ## >> Call Site 7 <<
	.long	Lset18
Lset19 = Ltmp22-Ltmp21                  ##   Call between Ltmp21 and Ltmp22
	.long	Lset19
Lset20 = Ltmp23-Lfunc_begin0            ##     jumps to Ltmp23
	.long	Lset20
	.byte	5                       ##   On action: 3
Lset21 = Ltmp22-Lfunc_begin0            ## >> Call Site 8 <<
	.long	Lset21
Lset22 = Ltmp24-Ltmp22                  ##   Call between Ltmp22 and Ltmp24
	.long	Lset22
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset23 = Ltmp24-Lfunc_begin0            ## >> Call Site 9 <<
	.long	Lset23
Lset24 = Ltmp25-Ltmp24                  ##   Call between Ltmp24 and Ltmp25
	.long	Lset24
Lset25 = Ltmp26-Lfunc_begin0            ##     jumps to Ltmp26
	.long	Lset25
	.byte	0                       ##   On action: cleanup
Lset26 = Ltmp25-Lfunc_begin0            ## >> Call Site 10 <<
	.long	Lset26
Lset27 = Ltmp27-Ltmp25                  ##   Call between Ltmp25 and Ltmp27
	.long	Lset27
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset28 = Ltmp27-Lfunc_begin0            ## >> Call Site 11 <<
	.long	Lset28
Lset29 = Ltmp28-Ltmp27                  ##   Call between Ltmp27 and Ltmp28
	.long	Lset29
Lset30 = Ltmp29-Lfunc_begin0            ##     jumps to Ltmp29
	.long	Lset30
	.byte	5                       ##   On action: 3
Lset31 = Ltmp28-Lfunc_begin0            ## >> Call Site 12 <<
	.long	Lset31
Lset32 = Lfunc_end0-Ltmp28              ##   Call between Ltmp28 and Lfunc_end0
	.long	Lset32
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
	.byte	0                       ## >> Action Record 1 <<
                                        ##   Cleanup
	.byte	0                       ##   No further actions
	.byte	1                       ## >> Action Record 2 <<
                                        ##   Catch TypeInfo 1
	.byte	125                     ##   Continue to action 1
	.byte	1                       ## >> Action Record 3 <<
                                        ##   Catch TypeInfo 1
	.byte	0                       ##   No further actions
	.byte	1                       ## >> Action Record 4 <<
                                        ##   Catch TypeInfo 1
	.byte	125                     ##   Continue to action 3
                                        ## >> Catch TypeInfos <<
	.long	0                       ## TypeInfo 1
	.p2align	2

	.section	__TEXT,__text,regular,pure_instructions
	.globl	__ZNSt3__111char_traitsIcE6lengthEPKc
	.weak_definition	__ZNSt3__111char_traitsIcE6lengthEPKc
	.p2align	4, 0x90
__ZNSt3__111char_traitsIcE6lengthEPKc:  ## @_ZNSt3__111char_traitsIcE6lengthEPKc
	.cfi_startproc
## BB#0:
	push	rbp
Lcfi29:
	.cfi_def_cfa_offset 16
Lcfi30:
	.cfi_offset rbp, -16
	mov	rbp, rsp
Lcfi31:
	.cfi_def_cfa_register rbp
	sub	rsp, 16
	mov	qword ptr [rbp - 8], rdi
	mov	rdi, qword ptr [rbp - 8]
	call	_strlen
	add	rsp, 16
	pop	rbp
	ret
	.cfi_endproc

	.private_extern	__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
	.globl	__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
	.weak_definition	__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
	.p2align	4, 0x90
__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_: ## @_ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
Lfunc_begin1:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception1
## BB#0:
	push	rbp
Lcfi32:
	.cfi_def_cfa_offset 16
Lcfi33:
	.cfi_offset rbp, -16
	mov	rbp, rsp
Lcfi34:
	.cfi_def_cfa_register rbp
	sub	rsp, 720
	mov	al, r9b
	lea	r10, [rbp - 552]
	lea	r11, [rbp - 488]
	mov	qword ptr [rbp - 504], rdi
	mov	qword ptr [rbp - 512], rsi
	mov	qword ptr [rbp - 520], rdx
	mov	qword ptr [rbp - 528], rcx
	mov	qword ptr [rbp - 536], r8
	mov	byte ptr [rbp - 537], al
	mov	rcx, qword ptr [rbp - 504]
	mov	qword ptr [rbp - 472], r11
	mov	qword ptr [rbp - 480], -1
	mov	rdx, qword ptr [rbp - 472]
	mov	rsi, qword ptr [rbp - 480]
	mov	qword ptr [rbp - 456], rdx
	mov	qword ptr [rbp - 464], rsi
	mov	rdx, qword ptr [rbp - 456]
	mov	qword ptr [rdx], 0
	mov	rdx, qword ptr [rbp - 488]
	mov	qword ptr [rbp - 552], rdx
	mov	qword ptr [rbp - 448], r10
	cmp	rcx, 0
	jne	LBB9_2
## BB#1:
	mov	rax, qword ptr [rbp - 504]
	mov	qword ptr [rbp - 496], rax
	jmp	LBB9_29
LBB9_2:
	mov	rax, qword ptr [rbp - 528]
	mov	rcx, qword ptr [rbp - 512]
	sub	rax, rcx
	mov	qword ptr [rbp - 560], rax
	mov	rax, qword ptr [rbp - 536]
	mov	qword ptr [rbp - 344], rax
	mov	rax, qword ptr [rbp - 344]
	mov	rax, qword ptr [rax + 24]
	mov	qword ptr [rbp - 568], rax
	mov	rax, qword ptr [rbp - 568]
	cmp	rax, qword ptr [rbp - 560]
	jle	LBB9_4
## BB#3:
	mov	rax, qword ptr [rbp - 560]
	mov	rcx, qword ptr [rbp - 568]
	sub	rcx, rax
	mov	qword ptr [rbp - 568], rcx
	jmp	LBB9_5
LBB9_4:
	mov	qword ptr [rbp - 568], 0
LBB9_5:
	mov	rax, qword ptr [rbp - 520]
	mov	rcx, qword ptr [rbp - 512]
	sub	rax, rcx
	mov	qword ptr [rbp - 576], rax
	cmp	qword ptr [rbp - 576], 0
	jle	LBB9_9
## BB#6:
	mov	rax, qword ptr [rbp - 504]
	mov	rcx, qword ptr [rbp - 512]
	mov	rdx, qword ptr [rbp - 576]
	mov	qword ptr [rbp - 248], rax
	mov	qword ptr [rbp - 256], rcx
	mov	qword ptr [rbp - 264], rdx
	mov	rax, qword ptr [rbp - 248]
	mov	rcx, qword ptr [rax]
	mov	rcx, qword ptr [rcx + 96]
	mov	rsi, qword ptr [rbp - 256]
	mov	rdx, qword ptr [rbp - 264]
	mov	rdi, rax
	call	rcx
	cmp	rax, qword ptr [rbp - 576]
	je	LBB9_8
## BB#7:
	lea	rax, [rbp - 584]
	lea	rcx, [rbp - 240]
	mov	qword ptr [rbp - 224], rcx
	mov	qword ptr [rbp - 232], -1
	mov	rcx, qword ptr [rbp - 224]
	mov	rdx, qword ptr [rbp - 232]
	mov	qword ptr [rbp - 208], rcx
	mov	qword ptr [rbp - 216], rdx
	mov	rcx, qword ptr [rbp - 208]
	mov	qword ptr [rcx], 0
	mov	rcx, qword ptr [rbp - 240]
	mov	qword ptr [rbp - 584], rcx
	mov	qword ptr [rbp - 8], rax
	mov	qword ptr [rbp - 504], 0
	mov	rax, qword ptr [rbp - 504]
	mov	qword ptr [rbp - 496], rax
	jmp	LBB9_29
LBB9_8:
	jmp	LBB9_9
LBB9_9:
	cmp	qword ptr [rbp - 568], 0
	jle	LBB9_24
## BB#10:
	xor	esi, esi
	mov	eax, 24
	mov	edx, eax
	lea	rcx, [rbp - 608]
	mov	rdi, qword ptr [rbp - 568]
	mov	r8b, byte ptr [rbp - 537]
	mov	qword ptr [rbp - 72], rcx
	mov	qword ptr [rbp - 80], rdi
	mov	byte ptr [rbp - 81], r8b
	mov	rcx, qword ptr [rbp - 72]
	mov	rdi, qword ptr [rbp - 80]
	mov	r8b, byte ptr [rbp - 81]
	mov	qword ptr [rbp - 48], rcx
	mov	qword ptr [rbp - 56], rdi
	mov	byte ptr [rbp - 57], r8b
	mov	rcx, qword ptr [rbp - 48]
	mov	qword ptr [rbp - 40], rcx
	mov	rdi, qword ptr [rbp - 40]
	mov	qword ptr [rbp - 32], rdi
	mov	rdi, qword ptr [rbp - 32]
	mov	qword ptr [rbp - 24], rdi
	mov	rdi, qword ptr [rbp - 24]
	mov	r9, rdi
	mov	qword ptr [rbp - 16], r9
	mov	qword ptr [rbp - 656], rcx ## 8-byte Spill
	call	_memset
	mov	rsi, qword ptr [rbp - 56]
	mov	rdi, qword ptr [rbp - 656] ## 8-byte Reload
	movsx	edx, byte ptr [rbp - 57]
	call	__ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6__initEmc
	lea	rcx, [rbp - 608]
	mov	rsi, qword ptr [rbp - 504]
	mov	qword ptr [rbp - 200], rcx
	mov	rcx, qword ptr [rbp - 200]
	mov	qword ptr [rbp - 192], rcx
	mov	rcx, qword ptr [rbp - 192]
	mov	qword ptr [rbp - 184], rcx
	mov	rdi, qword ptr [rbp - 184]
	mov	qword ptr [rbp - 176], rdi
	mov	rdi, qword ptr [rbp - 176]
	mov	qword ptr [rbp - 168], rdi
	mov	rdi, qword ptr [rbp - 168]
	movzx	eax, byte ptr [rdi]
	and	eax, 1
	cmp	eax, 0
	mov	qword ptr [rbp - 664], rsi ## 8-byte Spill
	mov	qword ptr [rbp - 672], rcx ## 8-byte Spill
	je	LBB9_12
## BB#11:
	mov	rax, qword ptr [rbp - 672] ## 8-byte Reload
	mov	qword ptr [rbp - 120], rax
	mov	rcx, qword ptr [rbp - 120]
	mov	qword ptr [rbp - 112], rcx
	mov	rcx, qword ptr [rbp - 112]
	mov	qword ptr [rbp - 104], rcx
	mov	rcx, qword ptr [rbp - 104]
	mov	rcx, qword ptr [rcx + 16]
	mov	qword ptr [rbp - 680], rcx ## 8-byte Spill
	jmp	LBB9_13
LBB9_12:
	mov	rax, qword ptr [rbp - 672] ## 8-byte Reload
	mov	qword ptr [rbp - 160], rax
	mov	rcx, qword ptr [rbp - 160]
	mov	qword ptr [rbp - 152], rcx
	mov	rcx, qword ptr [rbp - 152]
	mov	qword ptr [rbp - 144], rcx
	mov	rcx, qword ptr [rbp - 144]
	add	rcx, 1
	mov	qword ptr [rbp - 136], rcx
	mov	rcx, qword ptr [rbp - 136]
	mov	qword ptr [rbp - 128], rcx
	mov	rcx, qword ptr [rbp - 128]
	mov	qword ptr [rbp - 680], rcx ## 8-byte Spill
LBB9_13:
	mov	rax, qword ptr [rbp - 680] ## 8-byte Reload
	mov	qword ptr [rbp - 96], rax
	mov	rax, qword ptr [rbp - 96]
	mov	rcx, qword ptr [rbp - 568]
	mov	rdx, qword ptr [rbp - 664] ## 8-byte Reload
	mov	qword ptr [rbp - 272], rdx
	mov	qword ptr [rbp - 280], rax
	mov	qword ptr [rbp - 288], rcx
	mov	rax, qword ptr [rbp - 272]
	mov	rcx, qword ptr [rax]
	mov	rcx, qword ptr [rcx + 96]
	mov	rsi, qword ptr [rbp - 280]
	mov	rdx, qword ptr [rbp - 288]
Ltmp30:
	mov	rdi, rax
	call	rcx
Ltmp31:
	mov	qword ptr [rbp - 688], rax ## 8-byte Spill
	jmp	LBB9_14
LBB9_14:
	jmp	LBB9_15
LBB9_15:
	mov	rax, qword ptr [rbp - 688] ## 8-byte Reload
	cmp	rax, qword ptr [rbp - 568]
	je	LBB9_20
## BB#16:
	lea	rax, [rbp - 328]
	mov	qword ptr [rbp - 312], rax
	mov	qword ptr [rbp - 320], -1
	mov	rax, qword ptr [rbp - 312]
	mov	rcx, qword ptr [rbp - 320]
	mov	qword ptr [rbp - 296], rax
	mov	qword ptr [rbp - 304], rcx
	mov	rax, qword ptr [rbp - 296]
	mov	qword ptr [rax], 0
	mov	rax, qword ptr [rbp - 328]
	mov	qword ptr [rbp - 696], rax ## 8-byte Spill
## BB#17:
	lea	rax, [rbp - 632]
	mov	rcx, qword ptr [rbp - 696] ## 8-byte Reload
	mov	qword ptr [rbp - 632], rcx
	mov	qword ptr [rbp - 336], rax
## BB#18:
	mov	qword ptr [rbp - 504], 0
	mov	rax, qword ptr [rbp - 504]
	mov	qword ptr [rbp - 496], rax
	mov	dword ptr [rbp - 636], 1
	jmp	LBB9_21
LBB9_19:
Ltmp32:
	mov	ecx, edx
	mov	qword ptr [rbp - 616], rax
	mov	dword ptr [rbp - 620], ecx
Ltmp33:
	lea	rdi, [rbp - 608]
	call	__ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev
Ltmp34:
	jmp	LBB9_23
LBB9_20:
	mov	dword ptr [rbp - 636], 0
LBB9_21:
	lea	rdi, [rbp - 608]
	call	__ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev
	mov	eax, dword ptr [rbp - 636]
	test	eax, eax
	mov	dword ptr [rbp - 700], eax ## 4-byte Spill
	je	LBB9_22
	jmp	LBB9_33
LBB9_33:
	mov	eax, dword ptr [rbp - 700] ## 4-byte Reload
	sub	eax, 1
	mov	dword ptr [rbp - 704], eax ## 4-byte Spill
	je	LBB9_29
	jmp	LBB9_32
LBB9_22:
	jmp	LBB9_24
LBB9_23:
	jmp	LBB9_30
LBB9_24:
	mov	rax, qword ptr [rbp - 528]
	mov	rcx, qword ptr [rbp - 520]
	sub	rax, rcx
	mov	qword ptr [rbp - 576], rax
	cmp	qword ptr [rbp - 576], 0
	jle	LBB9_28
## BB#25:
	mov	rax, qword ptr [rbp - 504]
	mov	rcx, qword ptr [rbp - 520]
	mov	rdx, qword ptr [rbp - 576]
	mov	qword ptr [rbp - 352], rax
	mov	qword ptr [rbp - 360], rcx
	mov	qword ptr [rbp - 368], rdx
	mov	rax, qword ptr [rbp - 352]
	mov	rcx, qword ptr [rax]
	mov	rcx, qword ptr [rcx + 96]
	mov	rsi, qword ptr [rbp - 360]
	mov	rdx, qword ptr [rbp - 368]
	mov	rdi, rax
	call	rcx
	cmp	rax, qword ptr [rbp - 576]
	je	LBB9_27
## BB#26:
	lea	rax, [rbp - 648]
	lea	rcx, [rbp - 408]
	mov	qword ptr [rbp - 392], rcx
	mov	qword ptr [rbp - 400], -1
	mov	rcx, qword ptr [rbp - 392]
	mov	rdx, qword ptr [rbp - 400]
	mov	qword ptr [rbp - 376], rcx
	mov	qword ptr [rbp - 384], rdx
	mov	rcx, qword ptr [rbp - 376]
	mov	qword ptr [rcx], 0
	mov	rcx, qword ptr [rbp - 408]
	mov	qword ptr [rbp - 648], rcx
	mov	qword ptr [rbp - 416], rax
	mov	qword ptr [rbp - 504], 0
	mov	rax, qword ptr [rbp - 504]
	mov	qword ptr [rbp - 496], rax
	jmp	LBB9_29
LBB9_27:
	jmp	LBB9_28
LBB9_28:
	mov	rax, qword ptr [rbp - 536]
	mov	qword ptr [rbp - 424], rax
	mov	qword ptr [rbp - 432], 0
	mov	rax, qword ptr [rbp - 424]
	mov	rcx, qword ptr [rax + 24]
	mov	qword ptr [rbp - 440], rcx
	mov	rcx, qword ptr [rbp - 432]
	mov	qword ptr [rax + 24], rcx
	mov	rax, qword ptr [rbp - 504]
	mov	qword ptr [rbp - 496], rax
LBB9_29:
	mov	rax, qword ptr [rbp - 496]
	add	rsp, 720
	pop	rbp
	ret
LBB9_30:
	mov	rdi, qword ptr [rbp - 616]
	call	__Unwind_Resume
LBB9_31:
Ltmp35:
	mov	ecx, edx
	mov	rdi, rax
	mov	dword ptr [rbp - 708], ecx ## 4-byte Spill
	call	___clang_call_terminate
LBB9_32:
Lfunc_end1:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2
GCC_except_table9:
Lexception1:
	.byte	255                     ## @LPStart Encoding = omit
	.byte	155                     ## @TType Encoding = indirect pcrel sdata4
	.asciz	"\274"                  ## @TType base offset
	.byte	3                       ## Call site Encoding = udata4
	.byte	52                      ## Call site table length
Lset33 = Lfunc_begin1-Lfunc_begin1      ## >> Call Site 1 <<
	.long	Lset33
Lset34 = Ltmp30-Lfunc_begin1            ##   Call between Lfunc_begin1 and Ltmp30
	.long	Lset34
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset35 = Ltmp30-Lfunc_begin1            ## >> Call Site 2 <<
	.long	Lset35
Lset36 = Ltmp31-Ltmp30                  ##   Call between Ltmp30 and Ltmp31
	.long	Lset36
Lset37 = Ltmp32-Lfunc_begin1            ##     jumps to Ltmp32
	.long	Lset37
	.byte	0                       ##   On action: cleanup
Lset38 = Ltmp33-Lfunc_begin1            ## >> Call Site 3 <<
	.long	Lset38
Lset39 = Ltmp34-Ltmp33                  ##   Call between Ltmp33 and Ltmp34
	.long	Lset39
Lset40 = Ltmp35-Lfunc_begin1            ##     jumps to Ltmp35
	.long	Lset40
	.byte	1                       ##   On action: 1
Lset41 = Ltmp34-Lfunc_begin1            ## >> Call Site 4 <<
	.long	Lset41
Lset42 = Lfunc_end1-Ltmp34              ##   Call between Ltmp34 and Lfunc_end1
	.long	Lset42
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
	.byte	1                       ## >> Action Record 1 <<
                                        ##   Catch TypeInfo 1
	.byte	0                       ##   No further actions
                                        ## >> Catch TypeInfos <<
	.long	0                       ## TypeInfo 1
	.p2align	2

	.section	__TEXT,__text,regular,pure_instructions
	.private_extern	___clang_call_terminate
	.globl	___clang_call_terminate
	.weak_definition	___clang_call_terminate
	.p2align	4, 0x90
___clang_call_terminate:                ## @__clang_call_terminate
## BB#0:
	push	rax
	call	___cxa_begin_catch
	mov	qword ptr [rsp], rax    ## 8-byte Spill
	call	__ZSt9terminatev

	.globl	__ZNSt3__111char_traitsIcE11eq_int_typeEii
	.weak_definition	__ZNSt3__111char_traitsIcE11eq_int_typeEii
	.p2align	4, 0x90
__ZNSt3__111char_traitsIcE11eq_int_typeEii: ## @_ZNSt3__111char_traitsIcE11eq_int_typeEii
	.cfi_startproc
## BB#0:
	push	rbp
Lcfi35:
	.cfi_def_cfa_offset 16
Lcfi36:
	.cfi_offset rbp, -16
	mov	rbp, rsp
Lcfi37:
	.cfi_def_cfa_register rbp
	mov	dword ptr [rbp - 4], edi
	mov	dword ptr [rbp - 8], esi
	mov	esi, dword ptr [rbp - 4]
	cmp	esi, dword ptr [rbp - 8]
	sete	al
	and	al, 1
	movzx	eax, al
	pop	rbp
	ret
	.cfi_endproc

	.globl	__ZNSt3__111char_traitsIcE3eofEv
	.weak_definition	__ZNSt3__111char_traitsIcE3eofEv
	.p2align	4, 0x90
__ZNSt3__111char_traitsIcE3eofEv:       ## @_ZNSt3__111char_traitsIcE3eofEv
	.cfi_startproc
## BB#0:
	push	rbp
Lcfi38:
	.cfi_def_cfa_offset 16
Lcfi39:
	.cfi_offset rbp, -16
	mov	rbp, rsp
Lcfi40:
	.cfi_def_cfa_register rbp
	mov	eax, 4294967295
	pop	rbp
	ret
	.cfi_endproc

	.section	__DATA,__data
	.globl	_mem_fill_blocks        ## @mem_fill_blocks
	.p2align	2
_mem_fill_blocks:
	.long	26214400                ## 0x1900000

	.globl	_l1_cache_blocks        ## @l1_cache_blocks
	.p2align	2
_l1_cache_blocks:
	.long	2048                    ## 0x800

	.globl	_l2_cache_blocks        ## @l2_cache_blocks
	.p2align	2
_l2_cache_blocks:
	.long	16777216                ## 0x1000000

	.globl	_head                   ## @head
.zerofill __DATA,__common,_head,16,3
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	" --- Initialising --- \n"

L_.str.1:                               ## @.str.1
	.asciz	"Starting new list @ %p \n"

L_.str.2:                               ## @.str.2
	.asciz	" --- Block Numbers ---\n"

L_.str.3:                               ## @.str.3
	.asciz	"     L2 Cache Starts at cell: %d"

L_.str.4:                               ## @.str.4
	.asciz	"\n     DRAM Starts at cell: %d"

L_.str.5:                               ## @.str.5
	.asciz	"\n --- Initialised --- \n"

L_.str.6:                               ## @.str.6
	.asciz	" --- Testing --- \n"

L_.str.7:                               ## @.str.7
	.asciz	"First Read, Level "

L_.str.8:                               ## @.str.8
	.asciz	": "

L_.str.9:                               ## @.str.9
	.asciz	" --- Tested ---\n"

L_.str.10:                              ## @.str.10
	.asciz	"/proc/self/status"

L_.str.11:                              ## @.str.11
	.asciz	"r"

L_.str.12:                              ## @.str.12
	.asciz	"VmRSS:"

L_.str.13:                              ## @.str.13
	.asciz	" --- Finished ---\n"

L_.str.14:                              ## @.str.14
	.asciz	" --- Memory Usage --- \n"

L_.str.15:                              ## @.str.15
	.asciz	"    - Physical by Curr Proc: %dKB\n"


.subsections_via_symbols
