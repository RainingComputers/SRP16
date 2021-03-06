## SRP16
SRP16 is free and open ISA for 16-bit CPUs and Microcontrollers. 

## Project Status
### Specification
+ SRP16 ISA Specifaction [[.pdf]](Documentation/SRP16%20ISA%20Specification.pdf)
+ SRP16 Assembler Guide [[.pdf]](Documentation/SRP16%20Assembler%20Guide.pdf)
+ SRP16 ISA Simulator Manual [[.pdf]](Documentation/ISA%20Simulator%20Manual.pdf)
+ .dhex File Specification [[.pdf]](Documentation/dhex%20Specification.pdf)

### Roadmap
- [x] ISA Specification
- [x] Reference Implementation in Icarus Verilog
- [ ] Reference Implementation in Lattice iCEstick
- [x] Assembler
- [x] ISA Simulator
- [ ] I/O, Interrupts and Timers

## ISA Quick Reference
### Registers:
+ General Purpose Registers R0-R15 (Accessible by Load-Store Instructions)
+ General Purpose Registers R16-R31 (Not Accessible by Load-Store Instructions)
+ Accumulator Register (R60)
+ Memory Pointer Register or MPTR (R61)
+ Stack Pointer or SP (R62)
+ Program Counter or PC (R63)
+ POP, PUSH, INC, DEC instructions can only access General Purpose Registers R0-R31

### Instructions:
| Instruction                       | Operation											|
| --------------------------------- | ------------------------------------------------- |
| LDR Rx, 8-bit-signed-immediate    | Rx ⟵ immediate									|
| LDRU Rx, 8-bit-unsigned-immediate | Rx[15:8] ⟵ immediate								|
| LD@MPTR Rx, 8-bit-signed-offset   | Rx ⟵ memory[MPTR]	<br> MPTR ⟵ MPTR+offset			|
| ST@MPTR Rx, 8-bit-signed-offset   | memory[MPTR] ⟵ Rx	<br> MPTR ⟵ MPTR+offset			|
| LDB@MPTR Rx, 8-bit-signed-offset  | Rx[7:0] ⟵ memory[MPTR] <br> MPTR ⟵ MPTR+offset	|
| STB@MPTR Rx, 8-bit-signed-offset  | memory[MPTR] ⟵ Rx[7:0] <br> MPTR ⟵ MPTR+offset	|
| LDA 12-bit-signed-immediate       | A ⟵ immediate										|
| LDAU 6-bit-unsigned-immediate     | A[15:12] ⟵ immediate[3:0]							|
| LDMPTR 12-bit-unsigned-immediate  | MPTR ⟵ immediate									|
| LDMPTRU 12-bit-signed-immediate   | MPTR[15:12] ⟵ immediate[3:0]						|
| MOV Rx, Ry                        | Rx ⟵ Ry											|
| MOV Rx, PC                        | Rx ⟵ PC+4											|
| JMP Ry or MOV PC, Ry              | PC ⟵ Ry											|
| SJMP 12-bit-signed-offset         | PC ⟵ PC+offset									|
| SJMPF 12-bit-signed-offset        | if(flag): PC ⟵ PC+offset							|
| NOTF                              | flag ⟵ !flag										|
| POP Rx                            | Rx ⟵ memory[SP] <br> SP ⟵ SP+1					|
| PUSH Rx                           | SP ⟵ SP-1	<br> memory[SP] ⟵ Rx					|
| INC Rx                            | Rx ⟵ Rx+1											|
| DEC Rx                            | Rx ⟵ Rx-1											|
| ADDI 8-bit-signed-immediate       | A ⟵ A+immediate									|
| ADCI 8-bit-signed-immediate       | A ⟵ A+immediate+carry								|
| SBBI 8-bit-signed-immediate       | A ⟵ A-immediate-carry								|
| ANDI 8-bit-signed-immediate       | A ⟵ A&immediate									|
| ORI 8-bit-signed-immediate        | A ⟵ A|immediate									|
| XORI 8-bit-signed-immediate       | A ⟵ A^immediate									|
| SLAI 6-bit-unsigned-immediate     | A ⟵ A<<<immediate									|
| SRAI 6-bit-unsigned-immediate     | A ⟵ A>>>immediate									|
| SLLI 6-bit-unsigned-immediate     | A ⟵ A<<immediate									|
| SRLI 6-bit-unsigned-immediate     | A ⟵ A>>immediate									|
| ADD Rx                            | A ⟵ A+Rx											|
| SUB Rx                            | A ⟵ A-Rx											|
| ADC Rx                            | A ⟵ A+Rx+carry									|
| SBB Rx                            | A ⟵ A-Rx-carry									|
| AND Rx                            | A ⟵ A&Rx											|			
| OR Rx                             | A ⟵ A|Rx											|			
| XOR Rx                            | A ⟵ A^Rx											|			
| SLA Rx                            | A ⟵ A<<<Rx										|			
| SRA Rx                            | A ⟵ A>>>Rx										|			
| SLL Rx                            | A ⟵ A<<Rx											|
| SRL Rx                            | A ⟵ A>>Rx											|
| CLI 8-bit-signed-immediate        | if(A<immediate): flag ⟵ 1 <br> else: flag ⟵ 0		|
| CGI 8-bit-signed-immediate        | if(A>immediate): flag ⟵ 1 <br> else: flag ⟵ 0		|
| CEI 8-bit-signed-immediate        | if(A==immediate): flag ⟵ 1 <br> else: flag ⟵ 0	|
| CL Rx                             | if(A<Rx): flag ⟵ 1 <br> else: flag ⟵ 0			|
| CG Rx                             | if(A>Rx): flag ⟵ 1 <br> else: flag ⟵ 0			|
| CE Rx                             | if(A==Rx): flag ⟵ 1 <br> else: flag ⟵ 0			|

## Installing toolchain
+ Clone repo, `cd` into it
```
git clone https://github.com/RainingComputers/SRP16.git
cd SRP16
```
+ Install readline library
```
apt-get install libreadline-dev
```
+ Compile and build executable,
```
make build
```
+ Install, requires root privilege
```
make install
```

## Getting started
Let's write a simple program to generate fibonacci numbers, and save it as `test.asm`
```
	lda 1					
	ldr r0, 0		;Load initial values		
	ldr r1, 1				
loop:						
	add r0					
	mov r0, r1			
	mov r1, a		;Add to accumulator		
	sjmp loop		;Loop
```
Now to assemble the program, 
```
srp16asm test.asm -s test.dhex
```
Now, to start the simulator,
```
srp16sim test.dhex
```
You will see a prompt,
```
(pc@0x0000) █  
```
Let's set a break point at end of the loop,
```
(pc@0x0000) bp "test.asm" 8
```
Now use `run` command to run it, and `a` to view contents of the accumulator,
```
(pc@0x0000) run
(pc@0x000c) a
a = 0x0001
(pc@0x000c) run
(pc@0x000c) a
a = 0x0002
(pc@0x000c) run
(pc@0x000c) a
a = 0x0003
(pc@0x000c) run
(pc@0x000c) a
a = 0x0005
```

## License
+ MIT License. See: https://github.com/RainingComputers/SRP16/blob/master/LICENSE.md
