cc = g++
target = main

$(target): $(target).cpp bignum.cpp
	@$(cc) $(target).cpp -o $@ -lgmp -lmpfr

.PHONY: clean
clean:
	@rm -f $(target)
