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

        opcode = 5'h00;
        operand = 16'h0000;
        write = 0;
        writeu = 0;
        read = 0;
        #1;

        clk = 1;
        #1;
        clk = 0;

        opcode = 5'h00;
        operand = 16'hfffe;//
        write = 1;
        read = 0;

        #1;

        clk = 1;
        #1;
        clk = 0;

        write = 0;
        operand = 16'h0005;//
        opcode = 5'b00010;
        #1;

        clk = 1;
        #1;
        clk = 0;
        
        operand = 16'h0000;
        opcode = 5'h00;
        read = 1;

        clk = 1;
        #1;
        clk = 0;

        read = 0;
        #1;     

        opcode = 5'h00;
        operand = 16'hffff;//
        write = 1;
        read = 0;

        #1;

        clk = 1;
        #1;
        clk = 0;

        write = 0;
        operand = 16'h0000;//
        opcode = 5'b01110;
        #1;

        clk = 1;
        #1;
        clk = 0;
        
        operand = 16'h0000;
        opcode = 5'h00;
        read = 1;

        clk = 1;
        #1;
        clk = 0;

        read = 0;
        #1;     

        $finish;
        /* End of testing*/
    end

endmodule