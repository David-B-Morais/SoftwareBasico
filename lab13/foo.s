/*

int foo (int x) {
  return x+1;
}

*/

.text
.globl foo

foo:
    incl %edi
    movl %edi, %eax
    ret
