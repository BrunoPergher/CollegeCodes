; Bruno Pergher -> For contador usando ind, jmp, jle 
section .data  ; constantes 

    pergunta db "Digite um número entre 0 e 9" , 10
    tamPerg equ $-pergunta
    
section .bss  ; variaveis

    n1 resb 2
    n2 resb 2
    r  resb 2


section .text  ;
    global _start

_start: ;
    ; somente uma pergunta pra não duplicar a pergunta na saida
    mov rax, 1   
    mov rdi, 1   
    mov rsi, pergunta 
    mov rdx, tamPerg
    syscall

    ; salva n1
    mov rax, 0
    mov rdi, 0
    mov rsi, n1
    mov rdx, 2
    syscall
    
    ; salva n2
    mov rax, 0
    mov rdi, 0
    mov rsi, n2
    mov rdx, 2
    syscall

;   jle se for menor ou igual 
FOR:
    mov cl, [n1]
    mov dl, [n2]  
    cmp cl, dl  
    jle CONDICAO
    jmp encerra

CONDICAO: ; valida a condição do for
    mov rax, 1   
    mov rdi, 1   
    mov rsi, n1 
    mov rdx, 2
    syscall

    mov cl, [n1]
    inc cl ; inc +1 no cl -> cl é o N1
    mov [n1], cl  ;    dec 1
    
    jmp FOR

encerra:
    mov rax, 60
    mov rdi, 0
    syscall
    ret
    
    
    
    