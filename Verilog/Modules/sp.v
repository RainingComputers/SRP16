module sp(din, read_dbus, read_abus, write, inc, dec, clk,
    abus_out, dbus_out, reset
);
    /* Input ports */
    input [15:0] din;
    input read_dbus, read_abus, write, inc, dec, clk, reset;

    /* Output ports */
    output [15:0] abus_out;
    output [15:0] dbus_out;

    /* Internal variables */
    reg [15:0] data;
    
    /* If read_abus is high, abus_out[15:0] will be data[15:0] */
    assign abus_out = (read_abus)? data : 16'hzzzz;

    /* If read_dbus is high, dbus_out[15:0] will be data[15:0] */
    assign dbus_out = (read_dbus)? data : 16'hzzzz;

    /* When there is a positive edge on the clock */
    always @ (posedge clk, posedge reset) 
    begin
        /* Asynchronous reset*/
        if(reset) begin
            data <= 16'h0000;
        end
        /* Write to register if write is high */
        else if(write) begin
            data <= din;
        end
        /* inc for pop, read and inc */
        else if(inc) begin
            data <= data + 16'h0001;
        end
        /* dec for push, dec and write */
        else if(dec) begin
            data <= data - 16'h0001;
        end
    end

endmodule