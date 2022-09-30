cc = g++
target = main

%.o: %.cpp
	@$(cc) -c $<

$(target): main.o fib.o
	@$(cc) $^ -o $@

.PHONY: clean
clean:
	@rm -f *.o $(target)