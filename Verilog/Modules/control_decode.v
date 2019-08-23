/* Instruction Encoding Definitions */
`define OPCODE1         instruction[3:0]
`define E_TYPE_OPCODE2  instruction[7:4]
`define R_TYPE_OPCODE2  instruction[9:4]
`define R_TYPE_OPCODE3  instruction[15:10]
`define E_TYPE_REG1     instruction[7:4]
`define R_TYPE_REG1     instruction[9:4]
`define R_TYPE_REG2     instruction[15:10]
`define E_TYPE_IMM      instruction[15:8]
`define T_TYPE_IMM      instruction[15:4]
`define R_TYPE_IMM      instruction[15:10]
`define E_TYPE_OFFSET   instruction[15:8]
`define T_TYPE_OFFSET   instruction[15:4]
`define SIGN_BIT        instruction[15] 

/* Decode module */
module control_decode(reset, instruction, clk,
    pc_read, pc_readplusone, pc_readplusfour, pc_write, pc_offset, pc_inc,
    ir_write, ir_writeu,
    reg_file_read, reg_file_readu,
    reg_file_write, reg_file_writu, 
    reg_file_inc, reg_file_dec,
    reg_file_id,
    mem_read, mem_write,
    mptr_offset, mptr_read_abus, mptr_read_dbus, mptr_write, mptr_writeu,
    sp_read_abus, sp_read_dbus, sp_write, sp_inc, sp_dec,
    alu_opcode, alu_read, alu_write, flag, 
    dout
);

    /* Input ports */
    input [15:0] instruction;
    input reset, clk, flag;

    /* Output ports */
    output reg pc_read, pc_readplusone, pc_readplusfour, pc_write, pc_offset, pc_inc;
    output reg ir_write, ir_writeu;
    output reg reg_file_read, reg_file_readu;
    output reg reg_file_write, reg_file_writu; 
    output reg reg_file_inc, reg_file_dec;
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

    /* Task for clearing control lines */
    task clear_control_lines;
    begin
        {pc_read, pc_readplusone, pc_readplusfour, pc_write, pc_offset, pc_inc} <= 6'b000000;
        {ir_write, ir_writeu} <= 2'b00;
        {reg_file_read, reg_file_readu} <= 2'b00;
        {reg_file_write, reg_file_writu} <= 2'b00;
        {reg_file_inc, reg_file_dec} <= 2'b00;
        reg_file_id <= 5'b00000;
        {mem_read, mem_write} <= 2'b00;
        mptr_offset <= 12'h000;
        {mptr_read_abus, mptr_read_dbus, mptr_write, mptr_writeu} <= 4'b0000;
        {sp_read_abus, sp_read_dbus, sp_write, sp_inc, sp_dec} <= 5'b00000;
        alu_opcode <= 4'b0000;
        {alu_read, alu_write} <= 2'b00;
        dout <= 16'hzzzz;
    end
    endtask

    /* At rising edge of clock */
    always @ (negedge clk, posedge reset)
    begin
        /* Asynchronous reset */
        if(reset) begin
            phase <= 3'b000;
            clear_control_lines();
        end
        
        /* Fetch cycle */
        else if(phase == 3'b000) begin
            clear_control_lines();
            pc_read <= 1;
            mem_read <= 1;
            ir_write <=1;
            phase <= phase + 3'b001;
        end
        else if(phase == 3'b001) begin
            clear_control_lines();
            pc_readplusone <= 1;
            mem_read <= 1;
            ir_writeu <= 1;
            phase <= phase + 3'b001;
        end

        /* Decode cycle */
        else begin
            case(`OPCODE1)
                /* LDR Instruction */
                4'b0000: begin
                    clear_control_lines();
                    reg_file_write <= 1;
                    reg_file_id <= `E_TYPE_REG1;
                    dout <= {{8{`SIGN_BIT}}, `E_TYPE_IMM};
                    pc_inc <= 1;
                    phase <= 3'b000;
                end

            endcase
        end


    end



endmodule