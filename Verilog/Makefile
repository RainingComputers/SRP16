.PHONY : help compile_icarus
help :
	@echo "clean"
	@echo "      Remove auto-generated files."
	@echo "run_icarus ncycles=no_cycles image=path vcdfile=path [dumpaddr=addr]"
	@echo "           [dumpsize=no_bytes]"
	@echo "      Start processor simulator testbench and view timing graphs."
	@echo "synthesize_icestick"
	@echo "      Synthesize foe Lattice icestick iCE40HX1K"

compile_icarus SRP16sim.vvp:
	iverilog -o SRP16sim.vvp Modules/pc.v Modules/ir.v Modules/register_file.v \
		Modules/memory_file_load.v Modules/mptr.v Modules/sp.v Modules/alu.v \
		Modules/control_decode.v Modules/register.v Modules/SRP16_core.v \
		Modules/gpio.v \
		Testbenches/Icarus/processor.v Testbenches/Icarus/core_test.v

run_icarus: SRP16sim.vvp
	@[ "${ncycles}" ] || ( echo "USAGE-ERROR: Command line argument 'ncycles' is not specified"; exit 1 )
	@[ "${image}" ] || ( echo "USAGE-ERROR: Command line argument 'image' is not specified"; exit 1 )
	@[ "${vcdfile}" ] || ( echo "USAGE-ERROR: Command line argument 'vcdfile' is not specified"; exit 1 )

	./SRP16sim.vvp +ncycles=$(ncycles) +image=$(image) +dumpaddr=$(dumpaddr) +dumpsize=$(dumpsize) +vcdfile=$(vcdfile)
	gtkwave $(vcdfile)

synthesize_icestick processor.bin:
	yosys -p 'synth_ice40 -top SRP16_processor -blif processor.blif' \
		Modules/pc.v Modules/ir.v Modules/register_file.v \
		Modules/mptr.v Modules/sp.v Modules/alu.v \
		Modules/control_decode.v Modules/register.v Modules/SRP16_core.v \
		Modules/gpio.v Testbenches/IceStick/RAM_512_8.v \
		Testbenches/IceStick/mem.v Testbenches/IceStick/processor.v

	arachne-pnr -d 1k -o processor.asc -p Testbenches/IceStick/icestick.pcf processor.blif

clean:
	rm -f *.vcd
	rm -f *.vvp
	rm -f *.o
	rm -f *.blif