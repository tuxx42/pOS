# Declare constants used for creating a multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

	# Load the Global Descriptor Table pointer register.
	subl $6, %esp
	movw gdt_size_minus_one, %cx
	movw %cx, 0(%esp)
	movl $gdt, %ecx
	movl %ecx, 2(%esp)
	lgdt 0(%esp)
	addl $6, %esp

	# Switch cs to the kernel code segment (0x08).
	push %ebx
	push %eax
	push $0x08
	push $0x1f
	retf

	# Switch ds, es, fs, gs, ss to the kernel data segment (0x10).
	movw $0x10, %cx
	movw %cx, %ds
	movw %cx, %es
	movw %cx, %fs
	movw %cx, %gs
	movw %cx, %ss

	# go to protected mode
	cli		# disable interrupts
	movl %cr0, %eax	# copy cr0
        orl %eax, 1	# enable protected mode bit
        movl %eax, %cr0	# restore cr0

	# Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
.Lhang:
	hlt
	jmp .Lhang
.size _start, . - _start
