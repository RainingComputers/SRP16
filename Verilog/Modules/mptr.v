module mptr(din, offsetin, read_abus, read_abusplus,
     read_dbus, write, writeu, clk, abus_out, dbus_out, reset
);
    /* Input ports */
    input [15:0] din;
    input [11:0] offsetin;
    input read_abus, read_abusplus;
    input read_dbus, write, writeu, clk, reset;

    /* Output ports */
    output [15:0] abus_out;
    output [15:0] dbus_out;

    /* Internal variables */
    reg [15:0] data;
    reg [11:0] offset;
    
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
            offset <= 16'h0000;
        end
        /* Write to register if write is high */
        else if(write) begin
            data <= din;
            offset <= 12'h000;
        end
        /* Write to upper 4 bits of the registr if writeu is high*/
        else if(writeu) begin
            data[15:12] <= din[3:0];
            offset <= 12'h000;
        end
        /* Store the new given offset */
        else if(read_abus)
            offset <= offsetin;
    end

    /* When there is a positive edge on the read_abus line */
    always @ (posedge read_abus)
    begin
        /* Add previosly stored offset */
        data <= data + {{5{offset[11]}}, offset[10:0]};
    end

endmodule