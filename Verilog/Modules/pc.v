module pc(din, read, readplusone, readplusfour, write, offset, inc, clk, 
    abus_out, dbus_out, reset
);
    /* Input ports */
    input [15:0] din;
    input read, readplusone, readplusfour, write, offset, inc, clk;
    input reset;

    /* Output ports */
    output [15:0] abus_out;
    output [15:0] dbus_out;

    /* Internal variables */
    reg [15:0] data;
    
    /* If read is high, abus_out[15:0] will be data[15:0] */
    assign abus_out = (read)? data : 16'hzzzz;

    /* If read is high, abus_out[15:0] will be data[15:0]+1 */
    assign abus_out = (readplusone)? data+16'h0001 : 16'hzzzz;

    /* If readplus is high, dbus_out[15:0] will be data[15:0]+4 */
    assign dbus_out = (readplusfour)? data+16'h0004 : 16'hzzzz;

    /* When there is a positive edge on the clock */
    always @ (posedge clk, posedge reset) 
    begin
        /* Asynchronous reset*/
        if(reset)
            data <= 16'h0000;
        /* Write to register if write is high */
        else if(write)
            data <= din;
        /* Add offset to register if offset is high */
        else if(offset)
            data <= data + din;
        /* Increament register of inc is high */
        else if(inc)
            data <= data + 16'h0002;
    end

endmodule