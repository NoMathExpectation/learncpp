cc = g++
target = calculator
require = main.cpp bignum.cpp calculator.cpp

$(target): $(require)
	@$(cc) main.cpp -o $@ -lgmp -lmpfr

.PHONY: clean
clean:
	@rm -f $(target)

.PHONY: run
run:
	@./$(target)

.PHONY: debug
debug: $(require)
	@$(cc) -g main.cpp -o $(target) -lgmp -lmpfr
