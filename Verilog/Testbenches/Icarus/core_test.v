module sim_core_tb();
    /* Processor pins */
    reg clk;
    reg reset;

    /* Instantiate processor */
    SRP16_processor CPU(clk, reset);

    /* Variables */
    integer i;
    integer n_cycles;
    integer dump_start;
    integer dump_size;

    /* Begin testing */
    initial begin

        /* Get number of cycles from command line arguments */
        if (! $value$plusargs("ncycles=%d", n_cycles)) begin
           $display("USAGE-ERROR: Specify number of cycles to simulate using +ncycles");
           $finish;
        end

        /* Get starting of the dump address from command line arguments */
        if(! $value$plusargs("dumpaddr=%h", dump_start)) begin
            dump_start = 0;
        end

        /* Get size of the dump from command line arguments */
        if(! $value$plusargs("dumpsize=%d", dump_size)) begin
            dump_size = 0;
        end

        /* Dumpfile */
        $dumpfile("dump.vcd");
        $dumpvars(0, sim_core_tb);

        /* Dump registers */
        for (i = 0; i < 32; i = i+1)
            $dumpvars(0, sim_core_tb.CPU.CORE.REG_FILE.R[i]);

        /* Dump memory */
        for (i = dump_start; i < dump_start+dump_size; i = i+1)
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