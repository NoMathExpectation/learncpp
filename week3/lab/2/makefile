cc = g++
target = main

%.o: %.cpp
	@$(cc) -c $<

$(target): main.o fac.o
	@$(cc) $^ -o $@

.PHONY: clean
clean:
	@rm -f *.o $(target)