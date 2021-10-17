module SRP16_processor(CLK_IN, J2_1, RLED1);
    /* Input Ports */
    input CLK_IN;
    input J2_1;
    output RLED1;

    /* Processor Busses */
    wire [15:0] data_bus;
    wire [15:0] address_bus;
    wire [5:0] reg_id;

    /* Memory control lines */
    wire mem_read, mem_write, reset;

    /* Register control lines */
    wire reg_read, reg_write;
    
    /* Reset pin, active low */
    assign reset = ~J2_1;

    /* CPU Core */
    SRP16_core CORE(
        CLK_IN, reset, address_bus, data_bus,
        mem_read, mem_write, reg_id, reg_read,
        reg_write
    );

    /* GPIO */
    gpio GPIO(
        data_bus, reg_read, reg_write, reg_id,
        CLK_IN, data_bus, RLED1
    );

    /* Memory */
    memory_with_program MEMORY(
        data_bus[7:0], address_bus, mem_read, mem_write,
        CLK_IN, data_bus
    );

endmodule