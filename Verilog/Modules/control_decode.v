module control_decode(instruction, clk,
    pc_read, pc_readplusone, pc_readplusfour, pc_write, pc_offset, pc_inc,
    ir_write, ir_writeu,
    reg_file_read, reg_file_write, reg_file_writu, reg_file_inc, reg_file_dec,
    reg_file_id,
    mem_read, mem_write,
    mptr_offset, mptr_read_abus, mptr_read_dbus, mptr_write, mptr_writeu,
    sp_read_abus, sp_read_dbus, sp_write, sp_inc, sp_dec,
    alu_opcode, alu_read, alu_write, flag, 
    dout
);

    /* Input ports */
    input [15:0] instruction;
    input clk, flag;

    /* Output ports */
    output reg pc_read, pc_readplusone, pc_readplusfour, pc_write, pc_offset, pc_inc;
    output reg ir_write, ir_writeu;
    output reg reg_file_read, reg_file_write, reg_file_writu, reg_file_inc, reg_file_dec;
    output reg [5:0] reg_file_id;
    output reg mem_read, mem_write;
    output reg [11:0] mptr_offset;
    output reg mptr_read_abus, mptr_read_dbus, mptr_write, mptr_writeu;
    output reg sp_read_abus, sp_read_dbus, sp_write, sp_inc, sp_dec;
    output reg [4:0] alu_opcode;
    output reg alu_read, alu_write;
    output reg [15:0] dout;

    /* Internal variables */
    reg [3:0] phase;

endmodule