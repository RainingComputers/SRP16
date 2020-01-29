    sjmp prog
data:
    .hex 0200  ;The number two
    .hex 0300  ;The number three 
prog:
    ldmptr data
    ldb@mptr r0, 0x02
    mov a, r0
    ldb@mptr r0, 0x02
    add r0
hlt:
    sjmp hlt