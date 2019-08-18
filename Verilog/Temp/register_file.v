module register_file_tb();

    /* Inputs */
    reg [15:0] din;
    reg read, write, writeu, inc, dec, clk;
    reg [5:0] id;

    /* Outputs */
    wire [15:0] dout;

    /* Instantiate module */
    register_file U1(
        din, read, write, writeu, inc, dec, id, clk, dout
    );

    /* Loop variable */
    //integer Rx;

    /* Test module */
    initial begin
        /* Dumpfile */
        $dumpfile("test.vcd");
        $dumpvars(0, register_file_tb);
        //for (Rx=0; Rx<32; Rx=Rx+1)
        //    $dumpvars(0, register_file_tb.U1.R[Rx]);

        din = 16'h0000;
        read = 0;
        write = 1;
        inc = 0;
        dec = 0;
        writeu = 0;
        clk = 0;
        id = 5'b00001;
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

        id = 5'b00000;
        read = 1;
        #1;
        read = 0;
        #1;

        id = 5'b00001;
        read = 1;
        #1;
        read = 0;
        #1;

        id = 5'b00000;
        din = 16'h1F0F;
        write = 1;
        #1;
        clk = 1;
        #1;
        clk = 0;
        din = 16'h0000;
        write = 0;
        #1;

        read = 1;
        #1;
        read = 0;
        #1;

        writeu = 1;
        din = 16'h00F3;
        #1;
        clk = 1;
        #1;
        clk = 0;
        writeu = 0;
        din = 16'h0000;
        #1;

        read = 1;
        #1;
        read = 0;
        #1;

        inc = 1;
        #1;
        clk = 1;
        #1;
        clk = 0;
        inc = 0;
        #1;

        read = 1;
        #1;
        read = 0;
        #1;

        dec = 1;
        #1;
        clk = 1;
        #1;
        clk = 0;
        dec = 0;
        #1

        read = 1;
        #1;
        read = 0;
        #1;

        $finish;
        /* End of testing*/
    end

endmodule