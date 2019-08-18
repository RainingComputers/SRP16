# SRP16
SRP16 is free and open ISA for 16-bit CPUs and Microcontrollers. 

# Project Status
### Specification
SRP16 ISA Specifaction [.pdf](https://github.com/RainingComputers/SRP16/raw/master/Documentation/SRP16%20ISA%20Specification.pdf)

### Roadmap
- [x] ISA Specification
- [ ] Reference Implementation in Verilog
- [ ] Assembler
- [ ] ISA Simulator using [Verilator](https://www.veripool.org/wiki/verilator)
- [ ] Interrupts and Timers
- [ ] Pipelined Implementation

# ISA Quick Reference
### Architecture:

<div style="text-align:center">
    <img src="https://raw.githubusercontent.com/RainingComputers/SRP16/master/Documentation/SRP16%20Architecture.png"/>
</div>


### Registers:
+ General Purpose Registers R0-R15 (Accessible by Load-Store Instructions)
+ General Purpose Registers R16-R31 (Not Accessible by Load-Store Instructions)
+ Accumulator Register (R60)
+ Memory Pointer Register or MPTR (R61)
+ Stack Pointer or SP (R62)
+ Program Counter or PC (R63)

### Instructions:
<table align="center">
	<colgroup><col width="316">
	<col width="309">
	</colgroup><tbody><tr valign="top">
		<td style="border-top: 1px solid #999999; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0.1cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3"><b>Instruction</b></font></font></p>
		</td>
		<td style="border: 1px solid #999999; padding: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3"><b>Operation</b></font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">LDR
			Rx, 8-bit-signed-immediate</font></font></p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">Rx
			⟵ immediate</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">LDRU
			Rx, 8-bit-unsigned-immediate</font></font></p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">Rx[15:8]
			⟵ immediate</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">LD@MPTR
			Rx, 8-bit-signed-offset</font></font></p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">Rx
			⟵ memory[MPTR]</font></font></p>
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">MPTR
			⟵ MPTR+offset</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western"><font style="font-size: 12pt" size="3">ST@MPTR
			Rx, 8-bit-signed-offset</font></p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">memory[MPTR]
			⟵ Rx</font></font></p>
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">MPTR
			⟵ MPTR+offset</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">LDB@MPTR Rx, 8-bit-signed-offset</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">Rx[7:0]
			⟵ memory[MPTR]</font></font></p>
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">MPTR
			⟵ MPTR+offset</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">STB@MPTR Rx, 8-bit-signed-offset</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">memory[MPTR]
			⟵ Rx[7:0]</font></font></p>
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">MPTR
			⟵ MPTR+offset</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">LDA 12-bit-signed-immediate</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ immediate</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">LDAU 6-bit-unsigned-immediate</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A[15:12]
			⟵ immediate[3:0]</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">LDMPTR 12-bit-unsigned-immediate</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">MPTR
			⟵ immediate</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">LDMPTRU 12-bit-signed-immediate</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">MPTR[15:12]
			⟵ immediate[3:0]</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">MOV Rx, Ry</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">Rx
			⟵ Ry</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">MOV Rx, PC</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">Rx
			⟵ PC+4</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">JMP Ry or MOV PC, Ry</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">PC
			⟵ Ry</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">SJMP 12-bit-signed-offset</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">PC
			⟵ PC+offset</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">SJMPF 12-bit-signed-offset</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">if(flag):
			PC ⟵ PC+offset</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">NOTF</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">flag
			⟵ !flag</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">POP Rx</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">Rx
			⟵ memory[SP]</font></font></p>
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">SP
			⟵ SP+1</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">PUSH Rx</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">SP
			⟵ SP-1</font></font></p>
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">memory[SP]
			⟵ Rx</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">PUSH PC</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">SP
			⟵ SP-1</font></font></p>
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">memory[SP]
			⟵ PC+4</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">INC Rx</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">Rx
			⟵ Rx+1</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">DEC Rx</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">Rx
			⟵ Rx-1</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">ADDI 8-bit-signed-immediate</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A+immediate</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">ADCI 8-bit-signed-immediate</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A+immediate+carry</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">SBBI 8-bit-signed-immediate</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A-immediate-carry</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">ANDI 8-bit-signed-immediate</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A&amp;immediate</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">ORI 8-bit-signed-immediate</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A|immediate</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">XORI 8-bit-signed-immediate</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A^immediate</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">SLAI 6-bit-unsigned-immediate</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A&lt;&lt;&lt;immediate </font></font>
			</p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">SRAI 6-bit-unsigned-immediate</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A&gt;&gt;&gt;immediate</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">SLLI 6-bit-unsigned-immediate</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A&lt;&lt;immediate</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">SRLI 6-bit-unsigned-immediate</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A&gt;&gt;immediate</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">ADD Rx</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A+Rx</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">SUB Rx</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A-Rx</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">ADC Rx</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A+Rx+carry</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">SBB Rx</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A-Rx-carry</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">AND Rx</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A&amp;Rx</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">OR Rx</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A|Rx</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">XOR Rx</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A^Rx</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">SLA Rx</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A&lt;&lt;&lt;Rx</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">SRA Rx</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A&gt;&gt;&gt;Rx</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">SLL Rx</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A&lt;&lt;Rx</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">SRL Rx</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">A
			⟵ A&gt;&gt;Rx</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">CLI 8-bit-signed-immediate</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">if(A&lt;immediate):
			flag ⟵ 1</font></font></p>
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">else:
			flag ⟵ 0</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">CGI 8-bit-signed-immediate</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">if(A&gt;immediate):
			flag ⟵ 1</font></font></p>
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">else:
			flag ⟵ 0</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">CEI 8-bit-signed-immediate</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">if(A==immediate):
			flag ⟵ 1</font></font></p>
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">else:
			flag ⟵ 0</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">CL Rx</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">if(A&lt;Rx):
			flag ⟵ 1</font></font></p>
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">else:
			flag ⟵ 0</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">CG Rx</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">if(A&gt;Rx):
			flag ⟵ 1</font></font></p>
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">else:
			flag ⟵ 0</font></font></p>
		</td>
	</tr>
	<tr valign="top">
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: none; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0cm" width="316">
			<p class="western">CE Rx</p>
		</td>
		<td style="border-top: none; border-bottom: 1px solid #999999; border-left: 1px solid #999999; border-right: 1px solid #999999; padding-top: 0cm; padding-bottom: 0.1cm; padding-left: 0.1cm; padding-right: 0.1cm" width="309">
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">if(A==Rx):
			flag ⟵ 1</font></font></p>
			<p class="western"><font face="Noto Mono"><font style="font-size: 12pt" size="3">else:
			flag ⟵ 0</font></font></p>
		</td>
	</tr>
</tbody></table>

# License
+ MIT License. See: https://github.com/RainingComputers/SRP16/blob/master/LICENSE.md