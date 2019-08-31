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
    mptr_offset, mptr_read_abus, mptr_read_abusplus,
    mptr_read_dbus, mptr_write, mptr_writeu,
    sp_read_abus, sp_read_dbus, sp_write, sp_inc, sp_dec,
    alu_opcode, alu_read, alu_write, alu_writeu, flag, 
    temp_reg_read, temp_reg_write,
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
    output reg mptr_read_abus, mptr_read_abusplus; 
    output reg mptr_read_dbus, mptr_write, mptr_writeu;
    output reg sp_read_abus, sp_read_dbus, sp_write, sp_inc, sp_dec;
    output reg [4:0] alu_opcode;
    output reg alu_read, alu_write, alu_writeu;
    output reg temp_reg_read, temp_reg_write;
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
        {mptr_read_abus, mptr_read_abusplus} <= 2'b00;
        {mptr_read_dbus, mptr_write, mptr_writeu} <= 3'b000;
        {sp_read_abus, sp_read_dbus, sp_write, sp_inc, sp_dec} <= 5'b00000;
        alu_opcode <= 4'b0000;
        {alu_read, alu_write, alu_writeu} <= 3'b000;
        {temp_reg_read, temp_reg_write} <= 2'b00;
        dout <= 16'hzzzz;
    end
    endtask

    /* At rising edge of clock */
    always @ (negedge clk, posedge reset)
    begin
        /* Clear control lines */
        clear_control_lines();

        /* Asynchronous reset */
        if(reset) begin
            phase <= 3'b000;
        end
        
        /* Fetch cycle */
        else if(phase == 3'b000) begin
            pc_read <= 1;
            mem_read <= 1;
            ir_write <=1;
            phase <= phase + 3'b001;
        end
        else if(phase == 3'b001) begin
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
                    reg_file_write <= 1;
                    reg_file_id <= `E_TYPE_REG1;
                    dout <= {{8{`SIGN_BIT}}, `E_TYPE_IMM};
                    pc_inc <= 1;
                    phase <= 3'b000;
                end
                /* LDRU Instruction */
                4'b0001: begin
                    reg_file_writu <= 1;
                    reg_file_id <= `E_TYPE_REG1;
                    dout <= {8'h00, `E_TYPE_IMM};
                    pc_inc <= 1;
                    phase <= 3'b000;
                end

                /* LD@MPTR Instruction */
                4'b0010: begin
                    if(phase == 3'b010) begin
                        mptr_read_abus <= 1;
                        mem_read <= 1;
                        reg_file_write <= 1;
                        reg_file_id <= `E_TYPE_REG1;
                        phase <= phase + 3'b001;            
                    end
                    else if(phase == 3'b011) begin
                        mptr_read_abusplus <= 1;
                        mem_read <= 1;
                        mptr_offset <= `E_TYPE_OFFSET;
                        reg_file_writu <= 1;
                        reg_file_id <= `E_TYPE_REG1;
                        pc_inc <= 1;
                        phase <= 3'b000;
                    end
                end

                /* ST@MPTR Instruction */
                4'b0011: begin
                    if(phase == 3'b010) begin
                        mptr_read_abus <= 1;
                        mem_write <= 1;
                        reg_file_read <= 1;
                        reg_file_id <= `E_TYPE_REG1;
                        phase <= phase + 3'b001;
                    end
                    else if(phase == 3'b011) begin
                        mptr_read_abusplus <= 1;
                        mem_write <= 1;
                        mptr_offset <= `E_TYPE_OFFSET;
                        reg_file_readu <= 1;
                        reg_file_id <= `E_TYPE_REG1;
                        pc_inc <= 1;
                        phase <= 3'b000;
                    end
                end                

                /* LDB@MPTR Instruction */
                4'b0100: begin
                    mptr_read_abus <= 1;
                    mem_read <= 1;
                    mptr_offset <= `E_TYPE_OFFSET;
                    reg_file_write <= 1;
                    reg_file_id <= `E_TYPE_REG1;
                    pc_inc <= 1;
                    phase <= 3'b000;
                end

                /* STB@MPTR Instruction */
                4'b0101: begin
                    mptr_read_abus <= 1;
                    mem_write <= 1;
                    mptr_offset <= `E_TYPE_OFFSET;
                    reg_file_read <= 1;
                    reg_file_id <= `E_TYPE_REG1;
                    pc_inc <= 1;
                    phase <= 3'b000;
                end

                /* LDA Instruction */
                4'b0110: begin
                    alu_write <= 1;
                    dout <= {{4{`SIGN_BIT}}, `T_TYPE_IMM};
                    pc_inc <= 1;
                    phase <= 3'b000;
                end
                
                /* LDMPTR Instruction */
                4'b0111: begin
                    mptr_write <= 1;
                    dout <= {4'h0, `T_TYPE_IMM};
                    pc_inc <= 1;
                    phase <= 3'b000;
                end

                /* LDMPTRU Instruction */
                4'b1000: begin
                    mptr_writeu <= 1;
                    dout <= {4'h0, `T_TYPE_IMM};
                    pc_inc <= 1;
                    phase <= 3'b000;
                end

                /* MOV Instruction */
                4'b1001: begin
                    if(phase == 3'b010) begin
                        /* If register transfer between two general purpose registers */
                        if(`R_TYPE_REG1 <= 6'b011111 && `R_TYPE_REG2 <= 6'b011111) begin
                            /* Setup read signal */
                            reg_file_id <= `R_TYPE_REG2;
                            reg_file_read <= 1;
                            /* Setup write signal */
                            temp_reg_write <= 1;
                            /* Increment phase */
                            phase <= phase + 3'b001;
                        end
                        /* If register transfer is not between two general purpose registers */
                        else begin
                            /* Setup read signal */
                            case(`R_TYPE_REG2) 
                                6'b111100: alu_read <= 1;
                                6'b111101: mptr_read_dbus <= 1;
                                6'b111110: sp_read_dbus <= 1;
                                6'b111111: pc_readplusfour <= 1;
                                default: begin
                                    reg_file_id <= `R_TYPE_REG2;
                                    reg_file_read <= 1;
                                end
                            endcase
                            /* Setup write signal */
                            case(`R_TYPE_REG1)
                                6'b111100: alu_write <= 1;
                                6'b111101: mptr_write <= 1;
                                6'b111110: sp_write <= 1;
                                6'b111111: pc_write <= 1;
                                default: begin
                                    reg_file_id <= `R_TYPE_REG1;
                                    reg_file_write <= 1;
                                end                            
                            endcase
                            /* Don't Increment PC if JMP Ry or MOV Rx, PC instruction */
                            if(`R_TYPE_REG1 != 6'b111111 && `R_TYPE_REG2 != 6'b111111)
                                pc_inc <= 1;
                            /* Set appropritate phase */
                            if(`R_TYPE_REG2 == 6'b111111) phase <= phase + 3'b001;                       
                            else phase <= 3'b000;
                        end
                    end
                    else if(phase === 3'b011) begin
                        /* If register transfer between two general purpose registers */
                        if(`R_TYPE_REG1 <= 6'b011111 && `R_TYPE_REG2 <= 6'b011111) begin
                            /* Setup read signal */
                            temp_reg_read <= 1;
                            /* Setup write signal */
                            reg_file_id <= `R_TYPE_REG1;
                            reg_file_write <= 1;
                        end
                        /* Reset phase and increment PC*/
                        pc_inc <= 1;
                        phase <= 3'b000;
                    end
                end

                /* SJMP Instruction */
                4'b1010: begin
                    pc_offset <= 1;
                    dout <= {{4{`SIGN_BIT}}, `T_TYPE_OFFSET};
                    phase <= 3'b000;
                end

                /* SJMPF Instruction */
                4'b1011: begin
                    if(flag) begin
                        pc_offset <= 1;
                        dout <= {{4{`SIGN_BIT}}, `T_TYPE_OFFSET};
                    end
                    else pc_inc <= 1;
                    phase <= 3'b000;
                end

                /* R-type Opcode1=1100 Instructions */
                4'b1100: begin
                    case(`R_TYPE_OPCODE2)
                        /* LDAU Instruction */
                        6'b111011: begin
                            alu_writeu <= 1;
                            dout <= {{10{1'b0}}, `R_TYPE_IMM};
                            pc_inc <= 1;
                            phase <= 3'b000;
                        end
                    
                    endcase
                end

            endcase
        end


    end



endmodule