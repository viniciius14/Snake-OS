[bits 16]
[org 0x7c00]
[global _start]

KERNEL_LOCATION equ 0x1000

_start:
    mov [BOOT_DISK], dl

    xor ax, ax
    mov es, ax
    mov ds, ax
    mov bp, 0x8000
    mov sp, bp

    mov bx, KERNEL_LOCATION
    mov dh, 40      ; sectors to read

    mov ah, 0x02
    mov al, dh      ; read 40 sectors at 512 bytes a sector = 20480 bytes to use
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02
    mov dl, [BOOT_DISK]
    int 0x13

    ; Switches to text mode and as a result clears the screen
    ; mov ah, 0x0
    ; mov al, 0x3
    ; int 0x10

    ; Switches to graphics mode 0x13 -> Resolution: 320 x 200 | Adapter: EGA | Colors: 16 bit
    mov ah, 0x0
    mov al, 0x13
    int 0x10

    CODE_SEG equ code_descriptor - GDT_Start
    DATA_SEG equ data_descriptor - GDT_Start

    cli                     ; disable all interrupts

    in al, 0x92             ; Enable A20 gate
    or al, 0x02
    out 0x92, al

    lgdt [GDT_Descriptor]   ; load GDT

    mov eax, cr0
    or eax, 1
    mov cr0, eax            ; 32 bit protected mode

    jmp CODE_SEG:start_protected_mode   ; far jump (to another segment)

    jmp $

    BOOT_DISK: db 0

[bits 32]
start_protected_mode:
    mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000		; 32 bit stack base pointer
	mov esp, ebp

    jmp KERNEL_LOCATION

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