	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	leaq	L_.str(%rip), %rax
	movl	$2, %ecx
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rax, %rdi
	movl	%ecx, %esi
	movb	$0, %al
	callq	_open
	cmpl	$0, %eax
	jge	LBB0_2
## BB#1:
	callq	___error
	movl	(%rax), %edi
	callq	_strerror
	leaq	L_.str.1(%rip), %rdi
	movq	%rax, %rsi
	movb	$0, %al
	callq	_err_sys
LBB0_2:
	leaq	L_.str(%rip), %rdi
	callq	_unlink
	cmpl	$0, %eax
	jge	LBB0_4
## BB#3:
	callq	___error
	movl	(%rax), %edi
	callq	_strerror
	leaq	L_.str.2(%rip), %rdi
	movq	%rax, %rsi
	movb	$0, %al
	callq	_err_sys
LBB0_4:
	leaq	L_.str.3(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$15, %edi
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	callq	_sleep
	leaq	L_.str.4(%rip), %rdi
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	xorl	%ecx, %ecx
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"tempfile"

L_.str.1:                               ## @.str.1
	.asciz	"open: %s"

L_.str.2:                               ## @.str.2
	.asciz	"unlink: %s"

L_.str.3:                               ## @.str.3
	.asciz	"file unlinked\n"

L_.str.4:                               ## @.str.4
	.asciz	"done\n"


.subsections_via_symbols
