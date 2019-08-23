module register_file(din, read, readu, write, writeu, inc, dec, id, clk, dout);
    /* Input ports */
    input [15:0] din;
    input [5:0] id;
    input read, readu, write, writeu, inc, dec, clk;

    /* Output ports */
    output [15:0] dout;

    /* Array of registers */
    reg [15:0] R[31:0];

    /* If read is high, dout[15:0] will be R[15:0][id] */
    assign dout = (read)? R[id] : 16'hzzzz;

    /* If readu is high, dout[15:0] will be only upper 8 bits */
    assign dout = (readu)? {8'h00, R[id][15:8]} : 16'hzzzz;

    /* When there is a positive edge on the clock */
    always @ (posedge clk) 
    begin
        /* Write to register if write is high */
        if(write)
            R[id] <= din;
        else if(writeu)
            R[id][15:8] <= din[7:0];
        else if(inc)
            R[id] <= R[id] + 16'h0001;
        else if(dec)
            R[id] <= R[id] - 16'h0001;
    end    

endmodule