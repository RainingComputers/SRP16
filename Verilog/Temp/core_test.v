module sim_core_tb();
    /* Processor pins */
    reg clk;
    reg reset;

    /* Instantiate processor */
    SRP16_processor CPU(clk, reset);

    /* Variables */
    integer i = 0;
    integer n_cycles = 100;

    /* Begin testing */
    initial begin
        /* Dumpfile */
        $dumpfile("test.vcd");
        $dumpvars(0, sim_core_tb);

        /* Dump registers */
        for (i = 0; i < 32; i = i+1)
            $dumpvars(0, sim_core_tb.CPU.REG_FILE.R[i]);

        /* Dump memory */
        for (i = 0; i < 3000; i = i+1)
            $dumpvars(0, sim_core_tb.CPU.MEMORY.data[i]);

        /* Reset processor */
        clk <= 1;
        reset <= 1; 
        #1;
        reset <= 0;
        #1;

        /* Begin clock cycle */
        for(i = 1; i <= n_cycles; i=i+1) begin
           clk <= 0;
           #1;
           clk = 1;
           #1; 
        end
    end


endmodule