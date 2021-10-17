module memory_with_program(din, addrin, read, write, clk, dout);
    /* Input ports */
    input [7:0] din;
    input [15:0] addrin;
    input read, write, clk;

    /* Output ports */
    output [15:0] dout;

    /* If read is high, dout[15:0] will be data[15:0][id] */
    assign dout = (read)? {8'h00, ram_out} : 16'hzzzz;

    /* Internal */
    wire [7:0] ram_out;

    //initial $readmemh("Testbenches/IceStick/prog.hex", data);     
    
    /* Instantiate block ram */
    RAM_512_8 ram(clk, write, addrin[9:0], din, read, ram_out);
endmodule