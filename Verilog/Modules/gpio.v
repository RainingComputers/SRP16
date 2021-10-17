module gpio(din, read, write, id, clk, dout, 
    gpio_pin1);
    /* Input ports */
    input [15:0] din;
    input [5:0] id;
    input read, write, clk;

    /* Output ports */
    output [15:0] dout;
    output gpio_pin1;

    /* Array of registers */
    reg [7:0] R[4:0];

    /* If read is high, dout[15:0] will be R[15:0][id] */
    assign dout = (read && id[5])? {8'h00, R[id[4:0]]} : 16'hzzzz;

    /* Assign GPIO pins */
    assign gpio_pin1 = R[0][0];

    /* When there is a positive edge on the clock */
    always @ (posedge clk) 
    begin
        /* Write to register if write is high */
        if(write && id[5])
            R[id[4:0]] <= din[7:0];
    end    

endmodule