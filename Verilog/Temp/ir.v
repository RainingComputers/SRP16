module ir_tb();

    /* Inputs */
    reg [15:0] din;
    reg write, writeu, clk;
    /* Outputs */
    wire [15:0] dout;

    /* Instantiate module */
    ir U1(
        din, write, writeu, clk, dout
    );

    /* Test module */
    initial begin
        /* Dumpfile */
        $dumpfile("test.vcd");
        $dumpvars(0, ir_tb);

        din = 16'h0000;
        write = 1;
        clk = 0;
        #1;

        clk = 1;
        #1;
        write = 0;
        #1;
        clk = 0;
        #1;

        din = 16'h0f0f;
        write = 1;
        #1;
        clk = 1;
        #1;
        din = 16'h0000;
        write = 0;
        clk = 0;
        #1;

        din = 16'h0003;
        writeu = 1;
        #1;
        clk = 1;
        #1;
        clk = 0;
        writeu = 0;
        #1;

        $finish;
        /* End of testing*/
    end
endmodule