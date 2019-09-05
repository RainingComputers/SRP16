.PHONY : help
help :
	@echo "clean"
	@echo "      Remove auto-generated files."
	@echo "run_icarus ncycles=no_cycles image=path vcdfile=path [dumpaddr=addr]"
	@echo "           [dumpsize=no_bytes]"
	@echo "      Start processor simulator testbench and view timing graphs."

compile_icarus SRP16sim.vvp:
	iverilog -o SRP16sim.vvp Modules/pc.v Modules/ir.v Modules/register_file.v \
		Modules/memory_file_load.v Modules/mptr.v Modules/sp.v Modules/alu.v \
		Modules/control_decode.v Modules/register.v Modules/SRP16_core.v \
		Testbenches/Icarus/processor.v Testbenches/Icarus/core_test.v

run_icarus: SRP16sim.vvp
	@[ "${ncycles}" ] || ( echo "USAGE-ERROR: Command line argument 'ncycles' is not specified"; exit 1 )
	@[ "${image}" ] || ( echo "USAGE-ERROR: Command line argument 'image' is not specified"; exit 1 )
	@[ "${vcdfile}" ] || ( echo "USAGE-ERROR: Command line argument 'vcdfile' is not specified"; exit 1 )

	./SRP16sim.vvp +ncycles=$(ncycles) +image=$(image) +dumpaddr=$(dumpaddr) +dumpsize=$(dumpsize) +vcdfile=$(vcdfile)
	gtkwave $(vcdfile)

clean:
	rm -f *.vcd
	rm -f *.vvp
	rm -f *.o