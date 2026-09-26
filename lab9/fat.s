.text
.globl fat

fat:
  pushq %rbp
  movq %rsp, %rbp
  subq $16, %rsp

  cmpl $0, %edi
  jne L1

  movl $1, %eax
  jmp L2

L1:
  movl %edi, -4(%rbp)
  subl $1, %edi
  call fat
  imull -4(%rbp), %eax

L2:
  leave
  ret