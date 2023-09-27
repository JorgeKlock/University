	.file	"SumaVectores_local.c"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Faltan n\272 componentes del vector"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"Tama\361o Vectores:%u (%u B)\n"
	.section	.rodata.str1.8
	.align 8
.LC3:
	.string	"/ V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n"
	.align 8
.LC4:
	.string	"Tiempo:%11.9f\t / Tama\361o Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) / / V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n"
	.align 8
.LC6:
	.string	"Tiempo:%11.9f\t / Tama\361o Vectores:%u\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB41:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$88, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%fs:40, %rax
	movq	%rax, -56(%rbp)
	xorl	%eax, %eax
	cmpl	$1, %edi
	jle	.L23
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol@PLT
	leaq	.LC1(%rip), %rsi
	movq	%rax, %r12
	movl	%eax, %edx
	movl	$4, %ecx
	xorl	%eax, %eax
	movl	$1, %edi
	call	__printf_chk@PLT
	movl	%r12d, %eax
	leaq	22(,%rax,8), %rdx
	shrq	$4, %rdx
	salq	$4, %rdx
	subq	%rdx, %rsp
	leaq	7(%rsp), %r13
	subq	%rdx, %rsp
	leaq	7(%rsp), %r14
	subq	%rdx, %rsp
	leaq	7(%rsp), %rdx
	shrq	$3, %r13
	shrq	$3, %r14
	movq	%r13, -112(%rbp)
	leaq	0(,%r13,8), %rbx
	shrq	$3, %rdx
	testl	%r12d, %r12d
	movq	%r14, -120(%rbp)
	leaq	0(,%r14,8), %r15
	movq	%rdx, -128(%rbp)
	leaq	0(,%rdx,8), %r13
	je	.L3
	pxor	%xmm1, %xmm1
	leal	-1(%r12), %edx
	movsd	.LC2(%rip), %xmm3
	movq	%rdx, %r14
	addq	$1, %rdx
	cvtsi2sdq	%rax, %xmm1
	xorl	%eax, %eax
	mulsd	%xmm3, %xmm1
	.p2align 4,,10
	.p2align 3
.L6:
	pxor	%xmm0, %xmm0
	movapd	%xmm1, %xmm2
	movapd	%xmm1, %xmm7
	cvtsi2sd	%eax, %xmm0
	mulsd	%xmm3, %xmm0
	addsd	%xmm0, %xmm2
	subsd	%xmm0, %xmm7
	movsd	%xmm2, (%rbx,%rax,8)
	movsd	%xmm7, (%r15,%rax,8)
	addq	$1, %rax
	cmpq	%rax, %rdx
	jne	.L6
	leaq	-96(%rbp), %rsi
	xorl	%edi, %edi
	movq	%rdx, -104(%rbp)
	call	clock_gettime@PLT
	movq	-104(%rbp), %rdx
	xorl	%eax, %eax
	salq	$3, %rdx
	.p2align 4,,10
	.p2align 3
.L7:
	movsd	(%rbx,%rax), %xmm0
	addsd	(%r15,%rax), %xmm0
	movsd	%xmm0, 0(%r13,%rax)
	addq	$8, %rax
	cmpq	%rdx, %rax
	jne	.L7
	leaq	-80(%rbp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	movq	-72(%rbp), %rax
	subq	-88(%rbp), %rax
	pxor	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rax, %xmm0
	movq	-80(%rbp), %rax
	subq	-96(%rbp), %rax
	cmpl	$9, %r12d
	cvtsi2sdq	%rax, %xmm1
	divsd	.LC5(%rip), %xmm0
	addsd	%xmm1, %xmm0
	jbe	.L24
	movl	%r14d, %eax
	leaq	.LC4(%rip), %rsi
	movl	%r14d, %r9d
	movsd	0(%r13,%rax,8), %xmm6
	movl	%r14d, %r8d
	movsd	(%r15,%rax,8), %xmm5
	movl	%r14d, %ecx
	movsd	(%rbx,%rax,8), %xmm4
	movq	-128(%rbp), %rax
	movl	%r12d, %edx
	movl	$1, %edi
	movsd	0(,%rax,8), %xmm3
	movq	-120(%rbp), %rax
	movsd	0(,%rax,8), %xmm2
	movq	-112(%rbp), %rax
	movsd	0(,%rax,8), %xmm1
	movl	$7, %eax
	call	__printf_chk@PLT
.L9:
	xorl	%eax, %eax
	movq	-56(%rbp), %rcx
	xorq	%fs:40, %rcx
	jne	.L25
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L24:
	.cfi_restore_state
	leaq	.LC6(%rip), %rsi
	movl	%r12d, %edx
	movl	$1, %edi
	movl	%r14d, %r12d
	movl	$1, %eax
	xorl	%r14d, %r14d
	call	__printf_chk@PLT
	leaq	1(%r12), %rax
	leaq	.LC3(%rip), %r12
	movq	%rax, -104(%rbp)
	.p2align 4,,10
	.p2align 3
.L10:
	movsd	0(%r13,%r14,8), %xmm2
	movl	%r14d, %r8d
	movl	%r14d, %ecx
	movsd	(%r15,%r14,8), %xmm1
	movl	%r14d, %edx
	movsd	(%rbx,%r14,8), %xmm0
	movq	%r12, %rsi
	movl	$1, %edi
	movl	$3, %eax
	addq	$1, %r14
	call	__printf_chk@PLT
	cmpq	%r14, -104(%rbp)
	jne	.L10
	jmp	.L9
.L3:
	leaq	-96(%rbp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	leaq	-80(%rbp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	movq	-72(%rbp), %rax
	subq	-88(%rbp), %rax
	leaq	.LC6(%rip), %rsi
	pxor	%xmm0, %xmm0
	xorl	%edx, %edx
	pxor	%xmm1, %xmm1
	movl	$1, %edi
	cvtsi2sdq	%rax, %xmm0
	movq	-80(%rbp), %rax
	subq	-96(%rbp), %rax
	cvtsi2sdq	%rax, %xmm1
	movl	$1, %eax
	divsd	.LC5(%rip), %xmm0
	addsd	%xmm1, %xmm0
	call	__printf_chk@PLT
	jmp	.L9
.L25:
	call	__stack_chk_fail@PLT
.L23:
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
	orl	$-1, %edi
	call	exit@PLT
	.cfi_endproc
.LFE41:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC2:
	.long	2576980378
	.long	1069128089
	.align 8
.LC5:
	.long	0
	.long	1104006501
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
