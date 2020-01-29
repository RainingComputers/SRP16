    sjmp prog
data:
    .string "Hello world" 	;Hello world string
    .byte 0x00			    ;Null character
    .equ "str_len", 11 		;Length of string
prog:    
    ldmptr data 			;Load location of string
    lda 0x00			    ;Loop counter
loop:
    ldb@mptr r0, 0x01		;Load r0 with character and offset
    addi 1
    cei str_len
    notf
    sjmpf loop			    ;Loop till a==str_len
hlt: 
    sjmp hlt			    ;stop