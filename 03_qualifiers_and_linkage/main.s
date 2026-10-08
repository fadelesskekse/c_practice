	.file	"main.c"
	.text
	.p2align 4
	.globl	test_normal
	.type	test_normal, @function
test_normal:
.LFB0:
	.cfi_startproc
	endbr64
	movl	$3, normal_value(%rip)
	ret
	.cfi_endproc
.LFE0:
	.size	test_normal, .-test_normal
	.p2align 4
	.globl	test_volatile
	.type	test_volatile, @function
test_volatile:
.LFB1:
	.cfi_startproc
	endbr64
	movl	$1, volatile_value(%rip)
	movl	$2, volatile_value(%rip)
	movl	$3, volatile_value(%rip)
	ret
	.cfi_endproc
.LFE1:
	.size	test_volatile, .-test_volatile
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	endbr64
	movl	$1, volatile_value(%rip)
	xorl	%eax, %eax
	movl	$2, volatile_value(%rip)
	movl	$3, normal_value(%rip)
	movl	$3, volatile_value(%rip)
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.globl	volatile_value
	.bss
	.align 4
	.type	volatile_value, @object
	.size	volatile_value, 4
volatile_value:
	.zero	4
	.globl	normal_value
	.align 4
	.type	normal_value, @object
	.size	normal_value, 4
normal_value:
	.zero	4
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04.3) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
