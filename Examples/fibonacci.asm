	lda 1					
	ldr r0, 0		;Load initial values		
	ldr r1, 1				
loop:						
	add r0					
	mov r0, r1			
	mov r1, a		;Add to accumulator		
	sjmp loop		;Loop