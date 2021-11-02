section .text
    [bits 32]
    [extern main]
    jmp _start
    _start:
        call main
        jmp _start