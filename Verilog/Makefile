.PHONY : help
help :
	@echo "-clean"
	@echo "      Remove auto-generated files."
	@echo "-sim_core_tb ncycles=no_cycles image=path [dumpaddr=addr] [dumpsize=no_bytes]"
	@echo "      Start processor simulator testbench and view timing graphs."

sim_core_tb:
	@[ "${ncycles}" ] || ( echo "USAGE-ERROR: Command line argument 'ncycles' is not specified"; exit 1 )
	@[ "${image}" ] || ( echo "USAGE-ERROR: Command line argument 'image' is not specified"; exit 1 )
	rm -f test.vcd
	iverilog -o SRP16sim.vvp Modules/pc.v Modules/ir.v Modules/register_file.v \
		Modules/memory_file_load.v Modules/mptr.v Modules/sp.v Modules/alu.v \
		Modules/control_decode.v Modules/register.v Modules/SRP16_core.v \
		Testbenches/Icarus/processor.v Testbenches/Icarus/core_test.v
	./SRP16sim.vvp +ncycles=$(ncycles) +image=$(image) +dumpaddr=$(dumpaddr) +dumpsize=$(dumpsize)
	gtkwave dump.vcd

clean:
	rm -f *.vcd
	rm -f *.vvp
	rm -f *.o