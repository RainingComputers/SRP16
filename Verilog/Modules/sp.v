module sp(din, read_abus, read_dbus, write, inc, dec, clk,
    abus_out, dbus_out
);
    /* Input ports */
    input [15:0] din;
    input read_abus, read_dbus, write, inc, dec, clk;

    /* Output ports */
    output [15:0] abus_out;
    output [15:0] dbus_out;

    /* Internal variables */
    reg [15:0] data;
    
    /* If read_abus is high, abus_out[15:0] will be data[15:0] */
    assign abus_out = (read_abus)? data : 16'hzzzz;

    /* If read_abus is high, abus_out[15:0] will be data[15:0] */
    assign dbus_out = (read_dbus)? data : 16'hzzzz;

    /* When there is a positive edge on the clock */
    always @ (posedge clk) 
    begin
        /* Write to register if write is high */
        if(write)
            data <= din;
        /* Increament register if inc is high */
        else if(inc)
            data <= data + 16'h0002;
        /* Decreament the register if dec is high */
        else if(dec)
            data <= data - 16'h0002;
    end

endmodule