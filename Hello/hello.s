.section .rodata
.globl hello
hello:
  .string "Hello ASM!"

.text
.global main
main:
  push    %rbp
  mov     %rsp, %rbp

  mov     $hello, %edi
  call    puts

  mov     $0, %eax
  leave
  ret
