global  say_hello
section .text
say_hello:  mov     rax, 1
            mov     rdi, 1
            mov     rsi, msg
            mov     rdx, 6
            syscall
            ret

section .data
msg:        db      'hello', 10
