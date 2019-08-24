module mptr_tb();

    /* Inputs */
    reg [15:0] din;
    reg read_abus, read_abusplus, read_dbus, write, writeu, clk, reset;
    reg [11:0] offsetin;
    /* Outputs */
    wire [15:0] abus_out;
    wire [15:0] dbus_out;

    /* Instantiate module */
    mptr U1(
        din, offsetin, read_abus, read_abusplus, read_dbus, write,
        writeu, clk, abus_out, dbus_out, reset
    );

    /* Test module */
    initial begin
        /* Dumpfile */
        $dumpfile("test.vcd");
        $dumpvars(0, mptr_tb);

        din = 16'h0000;
        offsetin = 12'h002;
        read_abus = 0;
        read_abusplus = 0;
        read_dbus = 0;
        writeu = 0;
        write = 0;
        reset = 1;
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

        read_abus = 1;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;
        read_abus = 0;
        #1;

        read_abus = 1;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;
        read_abus = 0;
        #1;

        offsetin = 12'h004;
        #1;
        read_abus = 1;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;
        read_abus = 0;
        #1;

        read_abus = 1;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;
        read_abus = 0;
        #1;

        din = 16'h0003;
        writeu = 1;
        offsetin = 12'h000;
        #1;
        clk = 1;
        #1;
        writeu = 0;
        clk = 0;
        #1;

        read_abus = 1;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;
        read_abus = 0;
        #1;
        read_abus = 1;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;
        read_abus = 0;
        #1;

        read_dbus = 1;
        #1;
        read_dbus = 0;
        #1;

        read_abusplus = 1;
        #1;
        read_abusplus = 0;
        #1;


        $finish;
        /* End of testing*/
    end

endmodule