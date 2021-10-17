module SRP16_processor(clk, reset);
    /* Input Ports */
    input clk;
    input reset;

    /* Processor Busses */
    wire [15:0] data_bus;
    wire [15:0] address_bus;
    wire [5:0] reg_id;

    /* Memory control lines */
    wire mem_read, mem_write;

    /* Register control lines */
    wire reg_read, reg_write;
    
    /* CPU Core */
    SRP16_core CORE(
        clk, reset, address_bus, data_bus,
        mem_read, mem_write, reg_id, reg_read,
        reg_write
    );

    /* Memory */
    memory_file_load MEMORY(
        data_bus[7:0], address_bus, mem_read, mem_write,
        clk, data_bus
    );

endmodule