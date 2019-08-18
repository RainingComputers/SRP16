module sp_tb();

    /* Inputs */
    reg [15:0] din;
    reg read_abus, read_dbus, write, inc, dec, clk;
    reg reset;

    /* Outputs */
    wire [15:0] abus_out;
    wire [15:0] dbus_out;   

    /* Instantiate module */
    sp U1(
        din, read_abus, read_dbus, write, inc, dec, clk,
        abus_out, dbus_out
    );

    /* Test module */
    initial begin
        /* Dumpfile */
        $dumpfile("test.vcd");
        $dumpvars(0, sp_tb);
    
        din = 16'h0000;
        read_abus = 0;
        read_dbus = 0;
        write = 1;
        inc = 0;
        dec = 0;
        #1;
        clk = 1;
        #1;
        write = 0;
        clk = 0;
        #1;

        inc = 1;
        #1;
        clk = 1;
        #1;
        clk = 0;
        inc = 0;
        #1;

        din = 16'h0303;
        write = 1;
        #1;
        clk = 1;
        #1;
        clk = 0;
        din = 16'h0000;
        write =0;

        dec = 1;
        #1;
        clk = 1;
        #1;
        dec = 0;
        clk = 0;

        #1;
        read_abus = 1;
        #1;
        read_abus = 0;
        #1;

        read_dbus = 1;
        #1;
        read_dbus = 0;
        #1;





        $finish;
    end

endmodule