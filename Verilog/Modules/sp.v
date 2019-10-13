module sp(din, read_dbus, write, pop, push, clk,
    abus_out, dbus_out, reset
);
    /* Input ports */
    input [15:0] din;
    input read_dbus, write, pop, push, clk, reset;

    /* Output ports */
    output [15:0] abus_out;
    output [15:0] dbus_out;

    /* Internal variables */
    reg [15:0] data;
    reg push_flag;
    reg pop_flag;
    
    /* If pop is high, abus_out[15:0] will be data[15:0] */
    assign abus_out = (pop)? data : 16'hzzzz;

    /* If push, abus_out[15:0] will be data[15:0]-16'h0001 */
    assign abus_out = (push)? data - 16'h0001 :  16'hzzzz;

    /* If read_dbus is high, dbus_out[15:0] will be data[15:0] */
    assign dbus_out = (read_dbus)? data : 16'hzzzz;

    /* When there is a positive edge on the clock */
    always @ (posedge clk, posedge reset) 
    begin
        /* Asynchronous reset*/
        if(reset) begin
            data <= 16'h0000;
            push_flag <= 1'b0;
            pop_flag <= 1'b0;
        end
        /* Write to register if write is high */
        else if(write) begin
            data <= din;
            push_flag <= 1'b0;
            pop_flag <= 1'b0;
        end
        /* Set push flag and clear pop flag if push is high */
        else if(push) begin
            push_flag <= 1'b1;
            pop_flag <= 1'b0;
        end
        /* Set pop flag and clear push flag if pop is high */
        else if(pop) begin
            push_flag <= 1'b0;
            pop_flag <= 1'b1;
        end
    end

    /* Increment or Decrement register based on the flags */
    always @ (posedge pop, posedge push)
    begin
        if(pop_flag) data <= data + 16'h0001;
        if(push_flag) data <= data - 16'h0001;
    end

endmodule