[bits 16]
[org 0x7c00]

CODE_SEG equ code_descriptor - GDT_Start
DATA_SEG equ data_descriptor - GDT_Start

cli                     ; disable all interrupts
lgdt [GDT_Descriptor]   ; load GDT

mov eax, cr0
or eax, 1
mov cr0, eax            ; 32 bit protected mode

jmp CODE_SEG:start_protected_mode   ; far jump (to another segment)

[bits 32]
start_protected_mode:

mov al, 'A'
mov ah, 0x0f
mov [0xb8000], ax

jmp $


GDT_Start:
    null_descriptor:
        dd  0
        dd  0
    code_descriptor:
        dw 0xffff
        dw 0            ; 16 bits +
        db 0            ; 8 bits = 24
        db 0b10011010   ; type flags
        db 0b11001111   ; other flags
        db 0            ; last 8 bits of base
    data_descriptor:
        dw 0xffff
        dw 0
        db 0
        db 0b10010010
        db 0b11001111
        db 0
GDT_End:

GDT_Descriptor:
    dw GDT_End - GDT_Start - 1  ; size
    dd GDT_Start                ; start


times 510-($-$$) db 0
db 0x55, 0xaa