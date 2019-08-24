module alu_tb();

    /* Inputs */
    reg [4:0] opcode;
    reg [15:0] operand;
    reg read, write, writeu, clk;
    /* Outputs */
    wire [15:0] accout;
    wire flag;

    /* Instantiate module */
    alu U1(
        opcode, operand, read, write, writeu, clk, accout, flag
    );

    /* Test module */
    initial begin
        /* Dumpfile */
        $dumpfile("test.vcd");
        $dumpvars(0, alu_tb);

        opcode = 0;
        operand = 0;
        read = 0;
        write = 1;
        #1;

        clk = 1;
        #1;
        clk = 0;
        #1;

        operand = 16'h7000;

        clk = 1;
        #1;
        clk = 0;
        #1;

        write = 0;
        operand = 16'h8000;
        opcode = 5'b01011;

        clk = 1;
        #1;
        clk = 0;
        #1;

        operand = 16'h0000;
        opcode = 16'h0000;
        read = 1;
        #1;

        read = 0;

        $finish;
        /* End of testing*/
    end

endmodule