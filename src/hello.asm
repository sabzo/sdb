section .data           ; Data segment
msg     db  "Hello!", 0xa  ; "Hello", "newline"

section .txt            ; Text Segment
global _start           ; Default Entry point for ELF linking


_start:
; SYSCALL write(1, msg, 7)
mov eax, 4              ; Write syscall 4 
mov ebx, 1              ; Write to 1 aka stdout
mov ecx, msg            ; Put address of string into EBX
mov edx, 7              ; Put num of bytes to write into EDX

int 0x80                ; Call Kernel to make syscall 

; SYSCALL exit(0)
mov eax, 1              ; Exit is SYSCALL 1
mov ebx, 0              ; Exit with 0 for success
int 0x80                ; Call Kernel to make syscall
