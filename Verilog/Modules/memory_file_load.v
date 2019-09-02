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

    /* String to hold file name */
    reg [4096:0] img;

    /* Load program from program file */
    initial begin  
        /* Get memory/program image file path from command line arguments */
        if (! $value$plusargs("image=%s", img)) begin
           $display("USAGE-ERROR: Specify program/memory image file using +image");
           $finish;
        end
        $readmemh(img, data);
    end
    
    /* If write is high */
    always @ (posedge clk)
    begin
        if(write)
            data[addrin] <= din;
    end
endmodule