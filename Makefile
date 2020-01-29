.PHONY : help clean
help :
	@echo "clean"
	@echo "      Remove auto-generated files."
	@echo "build"
	@echo "     Build SRP16 development toolchain."
	@echo "install"
	@echo "     Install SRP16 development toolchain. Execute 'make build' first."

clean:
	make -C Verilog/ clean
	make -C Assembler/ clean
	rm -f  */*.hex

build:
	make -C Assembler/ build

install:
	make -C Assembler/ install