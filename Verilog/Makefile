.PHONY : help
help :
	@echo "test file=FILENAME 	: Test verilog file/module."
	@echo "clean       		: Remove auto-generated files."
	@echo "test_sim_core		: Compile SRP16_processor.v for simulator."
	@echo "sim_core_tb 			: Start processor simulator testbench"

test:
	iverilog -o test.o Modules/$(file) Temp/$(file)
	./test.o
	gtkwave test.vcd

test_sim_core:
	iverilog -o test.o Modules/SRP16_processor.v Modules/pc.v Modules/ir.v Modules/register_file.v Modules/memory_file_load.v Modules/mptr.v Modules/sp.v Modules/alu.v Modules/control_decode.v

sim_core_tb:
	iverilog -o test.o Modules/SRP16_processor.v Modules/pc.v Modules/ir.v Modules/register_file.v Modules/memory_file_load.v Modules/mptr.v Modules/sp.v Modules/alu.v Modules/control_decode.v Modules/register.v Temp/core_test.v
	./test.o
	gtkwave test.vcd

clean:
	rm -f *.vcd
	rm -f *.o