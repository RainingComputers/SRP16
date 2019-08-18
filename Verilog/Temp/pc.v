module pc_tb();

    /* Inputs */
    reg [15:0] din;
    reg read, readplusone, readplusfour, write, clk;
    reg offset, inc;
    reg reset;
    /* Outputs */
    wire [15:0] abus_out;
    wire [15:0] dbus_out;

    /* Instantiate module */
    pc U1(
        din, read, readplusone, readplusfour, write, offset, inc, clk, 
        abus_out, dbus_out, reset
    );

    /* Test module */
    initial begin
        /* Dumpfile */
        $dumpfile("test.vcd");
        $dumpvars(0, pc_tb);

        offset = 0;
        readplusone = 0;
        readplusfour = 0;
        inc = 0;
        din = 16'h0000;
        read = 0;
        reset = 1;
        write = 0;
        clk = 0;
        #1;

        reset = 0;
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
        
        din = 16'h0301;
        offset = 1;
        #1;
        clk = 1;
        #1;
        clk = 0;
        offset = 0;
        din = 16'h0000;
        #1;

        read = 1;
        #1;
        read = 0;
        #1;

        readplusone = 1;
        #1;
        readplusone = 0;
        #1;

        readplusfour = 1;
        #1;
        readplusfour = 0;
        #1;

        $finish;
        /* End of testing*/
    end

endmodule