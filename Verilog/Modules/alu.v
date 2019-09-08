/* ALU opcodes */
`define NOP  5'b00000
`define ADD  5'b00001
`define SUB  5'b00010
`define SLA  5'b00011
`define SRA  5'b00100
`define SLL  5'b00101
`define SRL  5'b00110
`define AND  5'b00111
`define OR   5'b01000
`define XOR  5'b01001
`define CL   5'b01010
`define CG   5'b01011
`define CE   5'b01100
`define ADC  5'b01101
`define SBB  5'b01110
`define NOTF 5'b10000

module alu(opcode, operand, read, write, writeu, clk, accout, flag);
    /* Input ports */
    input [4:0] opcode;
    input [15:0] operand;
    input read, write, writeu, clk;

    /* Output ports */
    output [15:0] accout;
    output reg flag;

    /* Internal variables */
    reg [16:0] accumulator_reg;
    reg [15:0] comp_reg;
    wire [15:0] accumulator;
    wire carry;
    
    /* Assignments */
    assign accumulator = accumulator_reg[15:0];
    assign carry = accumulator_reg[16];

    /* If read is high, accout[15:0] will be accumulator[15:0] */
    assign accout = (read)? accumulator_reg[15:0] : 16'hzzzz;

    /* When there is a positive edge on the clock */
    always @ (posedge clk)
    begin
       
        /* Write to accumulator if write is high */
        if(write) begin
            accumulator_reg[15:0] <= operand;
        end 

        /* Write to upper 4 bits if writeu is high */
        if(writeu) begin
            accumulator_reg[15:12] <= operand[3:0];
        end

        /* Check for opcode and perform arithmatic or logic operation */
        case(opcode)
            /* Add */
            `ADD: accumulator_reg <= accumulator + operand;
            
            /* Add with carry */
            `ADC: accumulator_reg <= accumulator + operand + carry;
            
            /* Substract */
            `SUB: accumulator_reg <= accumulator - operand;

            /* Substract with borrow */
            `SBB: accumulator_reg <= accumulator - operand - carry;

            /* Shift left arithmatic */
            `SLA: accumulator_reg <= $signed(accumulator) <<< operand;

            /* Shift right arithmatic */
            `SRA: accumulator_reg <= $signed(accumulator) >>> operand;

            /* Shift left logical */
            `SLL: accumulator_reg <= accumulator << operand;

            /* Shift right logical */
            `SRL: accumulator_reg <= accumulator >> operand;
            
            /* Bitwise AND */
            `AND: accumulator_reg <= accumulator & operand;
            

            /* Bitwise OR */
            `OR : accumulator_reg <= accumulator | operand;

            /* Bitwise XOR */
            `XOR: accumulator_reg <= accumulator ^ operand;

            /* Compare less than */
            `CL: begin
                comp_reg = accumulator - operand;
                flag <= comp_reg[15]; 
            end     
            
            /* Compare grater than */
            `CG: begin
                comp_reg = accumulator - operand;
                if(comp_reg[15] == 1'b0 && comp_reg != 16'h0000)
                    flag <= 1;
                else
                    flag <= 0; 
            end
            
            /* Compare equal to */
            `CE: begin
                comp_reg = accumulator - operand;
                if(comp_reg == 16'h0000)
                    flag <= 1;
                else
                    flag <= 0;
            end

            /* Invert flag */
            `NOTF: begin
                flag <= ~flag; 
            end
        endcase
    end


endmodule