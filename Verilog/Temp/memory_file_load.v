module memory_file_load_tb();
    /* Input ports */
    reg [7:0] din;
    reg [15:0] addrin;
    reg read, write, clk;

    /* Output ports */
    wire [7:0] dout;

    /* Instantiate module */
    memory_file_load U1(
        din, addrin, read, write, clk, dout
    );

    /* Test module */
    initial begin
        /* Dumpfile */
        $dumpfile("test.vcd");
        $dumpvars(0, memory_file_load_tb);

        din = 16'h00;
        addrin = 16'h0000;
        read = 0;
        write = 0;
        clk = 0;
        #1;

        read = 1;
        #1;
        read = 0;
        #1;

        addrin = 16'h0001;
        read = 1;
        #1;
        read = 0;
        #1;

        addrin = 16'h0002;
        read = 1;
        #1;
        read = 0;
        #1;

        din = 16'h03;
        write = 1;
        #1;
        clk = 1;
        #1;
        clk = 0;
        din = 16'h00;
        #1;

        read = 1;
        #1;
        read = 0;
        #1;

        $finish;
    end



endmodule