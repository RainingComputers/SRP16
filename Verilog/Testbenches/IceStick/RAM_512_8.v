module RAM_512_8(input clk, wen, input [8:0] addr, input [7:0] wdata, input ren, output reg [7:0] rdata);
    reg [7:0] mem [0:511];
    initial mem[0] = 255;
    always @(posedge clk) begin
        if (wen) mem[addr] <= wdata;
    end

    always @(posedge ren) begin
        rdata <= mem[addr];
    end
endmodule