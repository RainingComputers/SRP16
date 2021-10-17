module mptr(din, offsetin, read_abus, read_abusplus,
     read_dbus, write, writeu, offset, clk, abus_out, dbus_out, reset
);
    /* Input ports */
    input [15:0] din;
    input [11:0] offsetin;
    input read_abus, read_abusplus;
    input read_dbus, write, writeu, offset, clk, reset;

    /* Output ports */
    output [15:0] abus_out;
    output [15:0] dbus_out;

    /* Internal variables */
    reg [15:0] data;
    
    /* If read_abus is high, abus_out[15:0] will be data[15:0] */
    assign abus_out = (read_abus)? data : 16'hzzzz;

    /* If read_abusplus is high, abus_out[15:0] will be data[15:0]+1 */
    assign abus_out = (read_abusplus)? data+16'h0001 : 16'hzzzz;

    /* If read_abus is high, abus_out[15:0] will be data[15:0] */
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
        /* Write to upper 4 bits of the registr if writeu is high*/
        else if(writeu) begin
            data[15:12] <= din[3:0];
        end
        /* Store the new given offset */
        else if(offset) begin
            data <= data + {{5{offsetin[11]}}, offsetin[10:0]};
        end
    end

endmodule