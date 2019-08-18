module register(din, read, write, writeu, clk, dout);
    /* Input ports */
    input [15:0] din;
    input read, write, writeu, clk;

    /* Output ports */
    output [15:0] dout;

    /* Internal variables */
    reg [15:0] data;
    
    /* If read is high, dout[15:0] will be data[15:0] */
    assign dout = (read)? data : 16'hzzzz;

    /* When there is a positive edge on the clock */
    always @ (posedge clk) 
    begin
        /* Write to register if write is high */
        if(write)
            data <= din;
        else if(writeu)
            data[15:8] <= din[7:0];
    end

endmodule