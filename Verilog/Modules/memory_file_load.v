module memory_file_load(din, addrin, read, write, clk, dout);
    /* Input ports */
    input [7:0] din;
    input [15:0] addrin;
    input read, write, clk;

    /* Output ports */
    output [15:0] dout;

    /* Memory */
    reg [7:0] data[65536:0];

    /* If read is high, dout[15:0] will be data[15:0][id] */
    assign dout = (read)? {8'h00, data[addrin]} : 16'hzzzz;

    /* Load program from program file */
    initial begin
        $readmemh("prog.hex", data);
    end
    
    /* If write is high */
    always @ (posedge clk)
    begin
        if(write)
            data[addrin] <= din;
    end
endmodule