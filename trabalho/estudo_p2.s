/*

function            
v0 = p0 * p0        
ret v0              
end                 

*/

f0:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movl %edi, -24(%rbp)
    movl -24(%rbp), %eax
    imull -24(%rbp), %eax
    movl %eax, -4(%rbp)
    movl -4(%rbp), %eax
    leave
    ret

/*

function
zret p0 $0
v0 = p0 - $1
v1 = call 0 p0
v0 = call 1 v0
v0 = v0 + v1
ret v0
end

*/

f1:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movl %edi, -24(%rbp)
    movl -24(%rbp), %eax

    cmpl $0, %eax
    jne continua

    movl $0, %eax
    leave
    ret

continua:
    movl -24(%rbp), %eax
    subl $1, %eax
    movl %eax, -4(%rbp)

    movl -24(%rbp), %edi
    call f0
    movl %eax, -8(%rbp)

    movl -4(%rbp), %edi
    call f1
    movl %eax, -4(%rbp)

    movl -4(%rbp), %eax
    addl -8(%rbp), %eax
    movl %eax, -4(%rbp)
    movl -4(%rbp), %eax

    leave
    ret 