module SRP16_processor(clk, reset);
    /* Input Ports */
    input clk;
    input reset;

    /* Processor Busses */
    wire [15:0] data_bus;
    wire [15:0] address_bus;

    /* Memory control lines */
    wire mem_read, mem_write;
    
    /* CPU Core */
    SRP16_core CORE(
        clk, reset, address_bus, data_bus,
        mem_read, mem_write
    );

    /* Memory */
    memory_file_load MEMORY(
        data_bus, address_bus, mem_read, mem_write,
        clk, data_bus
    );

endmodule