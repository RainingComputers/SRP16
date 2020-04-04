    lda 0x00
loop:
    addi 0x01
    cei 0x0a
    notf
    sjmpf loop