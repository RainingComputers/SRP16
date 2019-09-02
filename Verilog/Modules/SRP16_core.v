module SRP16_core(
    clk, reset, address_bus, data_bus, 
    mem_read, mem_write
);
    /* Input Ports */
    input clk;
    input reset;

    /* Processor Busses */
    output wire [15:0] address_bus;
    inout wire [15:0] data_bus;

    /* Memory Control Lines */
    output wire mem_read, mem_write;

    /* Control Lines */
    wire pc_read, pc_readplusone, pc_readplusfour, pc_write, pc_offset, pc_inc;
    wire ir_write, ir_writeu;
    wire reg_file_read, reg_file_readu;
    wire reg_file_write, reg_file_writeu; 
    wire reg_file_inc, reg_file_dec;
    wire [5:0] reg_file_id;
    wire [11:0] mptr_offset;
    wire mptr_read_abus, mptr_read_abusplus; 
    wire mptr_read_dbus, mptr_write, mptr_writeu;
    wire sp_read_dbus, sp_write, sp_pop, sp_push;
    wire [4:0] alu_opcode;
    wire alu_read, alu_write, alu_writeu, flag;
    wire temp_reg_read, temp_reg_write;

    /* ALU Flag Output */
    wire alu_flag;

    /* Instruction register output */
    wire [15:0] instruction;
    
    /* Processor Modules */
    pc PC(
        data_bus, pc_read, pc_readplusone, pc_readplusfour, pc_write, pc_offset,
        pc_inc, clk, address_bus, data_bus, reset
    );
    
    ir IR(
        data_bus, ir_write, ir_writeu, clk, instruction
    );

    register_file REG_FILE(
        data_bus, reg_file_read, reg_file_readu,
        reg_file_write, reg_file_writeu,
        reg_file_inc, reg_file_dec,
        reg_file_id, clk, data_bus
    );

    register TEMP_REG(
        data_bus, temp_reg_read, temp_reg_write, clk, data_bus
    );

    mptr MPTR(
        data_bus, mptr_offset, mptr_read_abus, mptr_read_abusplus, 
        mptr_read_dbus, mptr_write, mptr_writeu,
        clk, address_bus, data_bus, reset
    );

    sp SP(
        data_bus, sp_read_dbus, sp_write, sp_pop,
        sp_push, clk, address_bus, data_bus, reset
    );

    alu ALU(
        alu_opcode, data_bus, alu_read, alu_write, alu_writeu, 
        clk, data_bus, flag
    );

    /* Control Module */
    control_decode CONTROL(
        reset, instruction, clk,
        pc_read, pc_readplusone, pc_readplusfour, pc_write, pc_offset, pc_inc,
        ir_write, ir_writeu,
        reg_file_read, reg_file_readu,
        reg_file_write, reg_file_writeu, 
        reg_file_inc, reg_file_dec,
        reg_file_id,
        mem_read, mem_write,
        mptr_offset, mptr_read_abus, mptr_read_abusplus,
        mptr_read_dbus, mptr_write, mptr_writeu,
        sp_read_dbus, sp_write, sp_pop, sp_push,
        alu_opcode, alu_read, alu_write, alu_writeu, flag,
        temp_reg_read, temp_reg_write,
        data_bus
    );


endmodule